/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <EventManager.h>
#include <GameEvents.h>
#include <Game.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Camera.h>
#include <Box.h>
#include <PhysicalWorld.h>
#include <KeypadManager.h>
#include <Captain.h>
#include <CaptainIdle.h>
#include <CaptainMoving.h>
#include <CaptainKneel.h>
#include <CaptainReload.h>
#include <CaptainDead.h>
#include <CustomCameraMovementManager.h>
#include <CustomCameraEffectManager.h>
#include <EventManager.h>
#include <SoundManager.h>
#include <PlatformerLevelState.h>
#include <MovingOneWayEntity.h>
#include <ProjectileEjector.h>
#include <Dust.h>
#include <RumblePakEffects.h>
#include <debugConfig.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern double fabs (double);

extern EntitySpec CAPTAIN_HEAD_PE;
extern EntitySpec LAND_DUST_EN;
extern EntitySpec JUMP_DUST_EN;
extern Sound SHOOT_SND;
extern Sound JUMP_SND;
extern Sound RELOAD_SND;
extern Sound HIT_SND;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// Only one instance
static Captain captain = NULL;

// there can only be one captain instantiated
static Captain Captain::getInstance()
{
	return captain;
}

static void Captain::setInstance(Captain instance)
{
	ASSERT(!captain, "Captain::setInstance: already instantiated");

	captain = instance;
}

void Captain::constructor(CaptainSpec* captainSpec, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor((ActorSpec*)captainSpec, internalId, name);

	this->dontStreamOut = true;

	// construct the captain's state machine
	this->stateMachine = new StateMachine(this);

	// init class variables
	this->energy = CAPTAIN_INITIAL_ENERGY;
	this->invincible = false;
	this->jumps = 0;
	this->gums = CAPTAIN_MAX_GUMS;
	this->ducks = 0;
	this->keepAddingForce = false;
	this->headEntity = NULL;
	this->jumpDustEntity = NULL;
	this->landDustEntity = NULL;

	Captain::setInstance(this);

	Object::addEventListener(PlatformerLevelState::getInstance(), Object::safeCast(this), (EventListener)Captain::onUserInput, kEventUserInput);

	this->inputDirection = Entity::getDirection(this);
}

void Captain::destructor()
{
	ASSERT(captain, "Captain::destructor: already deleted");
	ASSERT(captain == this, "Captain::destructor: more than one instance");

	// remove event listeners
	Object::removeEventListener(PlatformerLevelState::getInstance(), Object::safeCast(this), (EventListener)Captain::onUserInput, kEventUserInput);
	Object::removeEventListener(this->headEntity, Object::safeCast(this), (EventListener)Captain::onProjectileEjected, kEventProjectileEjected);

	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kCaptainCheckVelocity);
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kEntityFlash);

	// free the instance pointers
	captain = NULL;

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void Captain::ready(bool recursive)
{
	Entity::activeCollisionChecks(this, true);

	// call base
	Base::ready(this, recursive);

	// override with progress from progress manager
	ProgressManager progressManager = ProgressManager::getInstance();
	if(progressManager)
	{
		this->energy = ProgressManager::getCaptainCurrentEnergy(progressManager);
		this->gums = ProgressManager::getCaptainCurrentGums(progressManager);
	}

	// initialize me as idle
	StateMachine::swapState(this->stateMachine, State::safeCast(CaptainIdle::getInstance()));

	// add projectile ejector
	Captain::addProjectileEjectorEntity(this);

	// add dust entities
	Captain::addDustEntity(this);

	Object::fireEvent(EventManager::getInstance(), kEventCaptainSpawned);
}

void Captain::addProjectileEjectorEntity()
{
	Vector3D position = {__PIXELS_TO_METERS(CAPTAIN_HEAD_X_OFFSET), __PIXELS_TO_METERS(CAPTAIN_HEAD_Y_OFFSET), 0};
	this->headEntity = Entity::addChildEntity(this, &CAPTAIN_HEAD_PE, -1, NULL, &position, NULL);

	Object::addEventListener(this->headEntity, Object::safeCast(this), (EventListener)Captain::onProjectileEjected, kEventProjectileEjected);
}

void Captain::addDustEntity()
{
	Vector3D positionJumpDustEntity = {0, __PIXELS_TO_METERS(20), 0};
	this->jumpDustEntity = Entity::addChildEntity(this, &JUMP_DUST_EN, -1, NULL, &positionJumpDustEntity, NULL);

	Vector3D positionLandDustEntity = {0, __PIXELS_TO_METERS(22), 0};
	this->landDustEntity = Entity::addChildEntity(this, &LAND_DUST_EN, -1, NULL, &positionLandDustEntity, NULL);
}

void Captain::startShooting()
{
	if(this->gums > 0)
	{
		// shoot gum
		ProjectileEjector::setActive(this->headEntity, true);
		RumblePakManager::startEffect(&RumbleEffectSpit);

		// play shooting sound
		SoundManager::playSound(
			SoundManager::getInstance(),
			&SHOOT_SND,
			kPlayAll,
			(const Vector3D*)&this->transformation.globalPosition,
			kSoundWrapperPlaybackNormal,
			NULL,
			NULL
		);
	}
}

void Captain::stopShooting()
{
	ProjectileEjector::setActive(this->headEntity, false);
}

void Captain::kneel()
{
	// stop movement
	Actor::stopMovement(this, __X_AXIS);

	// switch to kneel state
	StateMachine::swapState(this->stateMachine, State::safeCast(CaptainKneel::getInstance()));
}

void Captain::standUp()
{
	// switch to idle state
	StateMachine::swapState(this->stateMachine, State::safeCast(CaptainIdle::getInstance()));
}

// make him jump
void Captain::jump(bool checkIfYMovement)
{
	if(this->body)
	{
		// determine the maximum number of possible jumps before reaching ground again
		s8 allowedNumberOfJumps = 1;

		// check if more jumps are allowed
		if(this->jumps < allowedNumberOfJumps)
		{
			// switch to moving state
			StateMachine::swapState(this->stateMachine, State::safeCast(CaptainMoving::getInstance()));

			// init a force to add to the captain's momentum
			Force force = {0, 0, 0};

			fix10_6 yBouncingPlaneNormal = Body::getLastNormalDirection(this->body).y;

			yBouncingPlaneNormal = yBouncingPlaneNormal ? yBouncingPlaneNormal : -__1I_FIX10_6;

			// is this the first jump from ground or a double jump from mid-air?
			if(this->jumps == 0)
			{
				// don't allow a first jump from mid-air without bandana
				if(checkIfYMovement && 0 < yBouncingPlaneNormal && (allowedNumberOfJumps == 1))
				{
					return;
				}

				// set first jump performed
				this->jumps = 1;

				// we're leaving ground with this jump
				//Captain::startedMovingOnAxis(this, __Y_AXIS);

				// add more force when running, normal force otherwise
				force.y = __FIX10_6_MULT(__ABS(yBouncingPlaneNormal), CAPTAIN_NORMAL_JUMP_INPUT_FORCE);

				// add the force to actually make the captain jump
				Actor::addForce(this, &force, true);
			}
			else
			{
				// hack to avoid the processing of kMessageBodyStopped message triggered by the call to Actor::stopMovement
				this->jumps = -1;

				// stop movement to gain full momentum of the jump force that will be added
				Actor::stopMovement(this, __Y_AXIS);

				// set second jump performed
				this->jumps = 2;

				// add the force to actually make the captain jump
				Actor::addForce(this, &force, true);
			}

			// play jump animation
			AnimatedEntity::playAnimation(this, "Jump");
			Dust::showAnimation(this->jumpDustEntity);

			// rumble effect
			RumblePakManager::startEffect(&RumbleEffectJump);

			// play jump sound
			SoundManager::playSound(
				SoundManager::getInstance(),
				&JUMP_SND,
				kPlayAll,
				(const Vector3D*)&this->transformation.globalPosition,
				kSoundWrapperPlaybackNormal,
				NULL,
				NULL
			);
		}
	}
}

// keep movement
void Captain::applyForce(u16 axis, bool enableAddingForce)
{
	if(enableAddingForce)
	{
		this->keepAddingForce = true;
	}

	if(!this->keepAddingForce)
	{
		return;
	}

	fix10_6 maxVelocity = CAPTAIN_MAX_VELOCITY_X;

	Velocity velocity = Body::getVelocity(this->body);

	Direction direction = Entity::getDirection(Entity::safeCast(this));

	if( direction.x != this->inputDirection.x ||
		((__X_AXIS & axis) && maxVelocity > __ABS(velocity.x)) ||
		((__Z_AXIS & axis) && maxVelocity > __ABS(velocity.z)) ||
		Actor::hasChangedDirection(this, __X_AXIS) ||
		Actor::hasChangedDirection(this, __Z_AXIS))
	{
		fix10_6 inputForce = !Body::getNormal(this->body).y ? CAPTAIN_X_INPUT_FORCE_WHILE_JUMPING : CAPTAIN_INPUT_FORCE;
		fix10_6 xForce = (__X_AXIS & axis) ? __RIGHT == this->inputDirection.x ? inputForce : -inputForce : 0;
		fix10_6 zForce = 0; //(__Z_AXIS & axis) ? __FAR == this->inputDirection.z ? inputForce : -inputForce : 0;
		Force force =
		{
			xForce,
			0,
			zForce
		};

		Actor::addForce(this, &force, true);
	}
	else
	{
		if(__UNIFORM_MOVEMENT != Body::getMovementType(this->body).x || (__ABS(velocity.x) > maxVelocity && !(__Y_AXIS & Body::getMovementOnAllAxis(this->body))))
		{
			Velocity newVelocity =
			{
				(__X_AXIS & axis) ? ((int)maxVelocity * this->inputDirection.x) : 0,
				0,
				(__Z_AXIS & axis) ? ((int)maxVelocity * this->inputDirection.z) : 0,
			};

			Body::moveUniformly(this->body, newVelocity);
		}
	}
}

// start movement
void Captain::stopAddingForce()
{
	Velocity velocity = Body::getVelocity(this->body);

	this->keepAddingForce = false;

	// no input
//	this->inputDirection.x = 0;
//	this->inputDirection.y = 0;
//	this->inputDirection.z = 0;

	// begin to decelerate
	u16 axisOfDeacceleration = 0;
	axisOfDeacceleration |= velocity.x? __X_AXIS: 0;
	axisOfDeacceleration |= velocity.z? __Z_AXIS: 0;

	if(axisOfDeacceleration)
	{
		fix10_6 inputForce = CAPTAIN_FORCE_FOR_STOPPING;
		fix10_6 xForce = __RIGHT == this->inputDirection.x ? inputForce : -inputForce;
		fix10_6 zForce = 0; //(__Z_AXIS & axis) ? __FAR == this->inputDirection.z ? inputForce : -inputForce : 0;
		Force force =
		{
			xForce,
			0,
			zForce
		};

		Actor::addForce(this, &force, true);
	}
	else
	{
		Captain::stopMovementOnAxis(this, __X_AXIS | __Z_AXIS);
	}
}

// started moving over axis
void Captain::startedMovingOnAxis(u16 axis)
{
	if(__Y_AXIS & axis)
	{
		Captain::capVelocity(this, true);
	}

	// start movement
	if(State::safeCast(CaptainMoving::getInstance()) != StateMachine::getCurrentState(this->stateMachine))
	{
		if(__X_AXIS & axis)
		{
			this->keepAddingForce = true;
			AnimatedEntity::playAnimation(this, "Walk");
		}

		StateMachine::swapState(this->stateMachine, State::safeCast(CaptainMoving::getInstance()));
	}
	else
	{
		if(__X_AXIS & axis)
		{
			this->keepAddingForce = true;
		}
	}
}

// stop moving over axis
bool Captain::stopMovementOnAxis(u16 axis)
{
	// if being hit do nothing
	if(!Body::isActive(this->body))
	{
		return false;
	}

	bool movementState = Body::getMovementOnAllAxis(this->body);

	if((__X_AXIS & axis) && !(__Y_AXIS & movementState))
	{
		AnimatedEntity::playAnimation(this, "Idle");
	}

	// if there is something below
	if(0 > Body::getNormal(this->body).y)
	{
		if(__Y_AXIS & axis)
		{
			Dust::showAnimation(this->landDustEntity);

			MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kCaptainCheckVelocity);

			this->jumps = 0;

			if(Body::getVelocity(this->body).x)
			{
				if(this->inputDirection.x)
				{
					AnimatedEntity::playAnimation(this, "Walk");
				}
			}
		}

		if(__Z_AXIS & axis)
		{
			this->keepAddingForce = false;
			this->jumps = 0;
			StateMachine::swapState(this->stateMachine, State::safeCast(CaptainIdle::getInstance()));
			return true;
		}

		if(!movementState && State::safeCast(CaptainIdle::getInstance()) != StateMachine::getCurrentState(this->stateMachine))
		{
			this->keepAddingForce = false;
			this->jumps = 0;
			StateMachine::swapState(this->stateMachine, State::safeCast(CaptainIdle::getInstance()));
			return true;
		}
		else
		{
			// make sure that hitting the floor doesn't slow me down because of the friction
			// TODO: this breaks jumping from walking
			/*
			if(__UNIFORM_MOVEMENT == Body::getMovementType(this->body).x)
			{
				fix10_6 maxVelocity = CAPTAIN_MAX_VELOCITY_X;

				Velocity newVelocity =
				{
					(int)maxVelocity * this->inputDirection.x,
					0,
					0,
				};

				Body::moveUniformly(this->body, newVelocity);
			}
			*/

			AnimatedEntity::playAnimation(this, "Walk");
		}
	}
	else
	{
		AnimatedEntity::playAnimation(this, "Fall");
	}

	return false;
}

// check direction
void Captain::checkDirection(u32 pressedKey, char* animation)
{
	bool movementState = Body::getMovementOnAllAxis(this->body);
	//Direction direction = Entity::getDirection(this);

	if(K_LR & pressedKey)
	{
		this->inputDirection.x = __RIGHT;
	}
	else if(K_LL & pressedKey)
	{
		this->inputDirection.x = __LEFT;
	}
	else if(K_LU & pressedKey)
	{
		this->inputDirection.y = __UP;
	}
	else if(K_LD & pressedKey)
	{
		this->inputDirection.y = __DOWN;
	}

	if(animation && !(__Y_AXIS & movementState))
	{
		AnimatedEntity::playAnimation(this, animation);
	}
}

void Captain::takeDamageFrom(int energyToReduce)
{
	if(!Captain::isInvincible(this))
	{
		// start short screen shake
		Camera::startEffect(Camera::getInstance(), kShake, 200);

		// play hit sound
		SoundManager::playSound(
			SoundManager::getInstance(),
			&HIT_SND,
			kPlayAll,
			(const Vector3D*)&this->transformation.globalPosition,
			kSoundWrapperPlaybackNormal,
			NULL,
			NULL
		);

		// reduce energy
		this->energy -= energyToReduce;

		if(this->energy >= 0)
		{
			Captain::setInvincible(this, true);

			// stop all movement
			Actor::stopAllMovement(this);
			Game::disableKeypad(Game::getInstance());
			GameState::pausePhysics(Game::getCurrentState(Game::getInstance()), true);

			// play animation
			AnimatedEntity::playAnimation(this, "Hit");

			// inform others to update ui etc
			Object::fireEvent(EventManager::getInstance(), kEventHitTaken);

			RumblePakManager::startEffect(&RumbleEffectTakeStrongDamage);
		}
		else
		{
			Captain::die(this);

			RumblePakManager::startEffect(&RumbleEffectDieStrong);			
		}
	}
}

void Captain::startFlashing()
{
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kEntityFlash);
	MessageDispatcher::dispatchMessage(0, Object::safeCast(this), Object::safeCast(this), kEntityFlash, NULL);
}

void Captain::stopFlashing()
{
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kEntityFlash);
 	Captain::resetPalette(this);
}

// flash after being hit
void Captain::flash()
{
	// only flash as long as captain is invincible
	if(Captain::isInvincible(this))
	{
		// toggle between original and flash palette
		Captain::toggleFlashPalette(this);

		// next flash state change after CAPTAIN_FLASH_INTERVAL milliseconds
		MessageDispatcher::dispatchMessage(CAPTAIN_FLASH_INTERVAL, Object::safeCast(this), Object::safeCast(this), kEntityFlash, NULL);
	}
	else
	{
		// set palette back to original
		Captain::resetPalette(this);
	}
}

void Captain::toggleFlashPalette()
{
	Captain::toggleEntityFlashPalette(this, Entity::safeCast(this));
	Captain::toggleEntityFlashPalette(this, this->headEntity);
}

void Captain::toggleEntityFlashPalette(Entity entity)
{
	// get all of the captain's sprites and loop through them
	VirtualList sprites = Entity::getSprites(entity);
	VirtualNode node = VirtualList::begin(sprites);
	for(; node; node = VirtualNode::getNext(node))
	{
		// get sprite's texture
		Sprite sprite = Sprite::safeCast(VirtualNode::getData(node));
		Texture texture = Sprite::getTexture(sprite);

		// get original palette
		TextureSpec* textureSpec = Texture::getSpec(texture);

		// set new palette
		if(Texture::getPalette(texture) == textureSpec->palette)
		{
			Texture::setPalette(texture, CAPTAIN_FLASH_PALETTE);
		}
		else
		{
			Texture::setPalette(texture, textureSpec->palette);
		}

		// rewrite sprite to bgmap to apply changed palette
		Sprite::rewrite(sprite);
	}
}

void Captain::resetPalette()
{
	Captain::resetEntityPalette(this, Entity::safeCast(this));
	Captain::resetEntityPalette(this, this->headEntity);
}

void Captain::resetEntityPalette(Entity entity)
{
	// get all of captain's sprites and loop through them
	VirtualList sprites = Entity::getSprites(entity);
	VirtualNode node = VirtualList::begin(sprites);
	for(; node; node = VirtualNode::getNext(node))
	{
		// get sprite's texture
		Sprite sprite = Sprite::safeCast(VirtualNode::getData(node));
		Texture texture = Sprite::getTexture(sprite);

		// get original palette and set it
		TextureSpec* textureSpec = Texture::getSpec(texture);
		Texture::setPalette(texture, textureSpec->palette);

		// rewrite sprite to bgmap to apply changed palette
		Sprite::rewrite(sprite);
	}
}

// die captain
void Captain::die()
{
	// go to dead state
	StateMachine::swapState(this->stateMachine, State::safeCast(CaptainDead::getInstance()));
}

void Captain::onProjectileEjected(Object eventFirer __attribute__ ((unused)))
{
	if(this->gums > 0)
	{
		this->gums--;
		Object::fireEvent(EventManager::getInstance(), kEventCaptainShot);
	}

	// don't allow holding key for continuous shooting
	Captain::stopShooting(this);
}

// process user input
void Captain::onUserInput(Object eventFirer __attribute__ ((unused)))
{
	UserInput userInput = PlatformerLevelState::getUserInput(PlatformerLevelState::getInstance(), false);

	CaptainState currentState = CaptainState::safeCast(StateMachine::getCurrentState(this->stateMachine));

	if(userInput.pressedKey)
	{
		CaptainState::onKeyPressed(currentState, this, &userInput);
	}

	if(userInput.releasedKey)
	{
		CaptainState::onKeyReleased(currentState, this, &userInput);
	}

	if(userInput.holdKey)
	{
		CaptainState::onKeyHold(currentState, this, &userInput);
	}
}

// get energy
s8 Captain::getEnergy()
{
	return this->energy;
}

// get number of gums
u8 Captain::getGums()
{
	return this->gums;
}

// get number of ducks
u8 Captain::getDucks()
{
	return this->ducks;
}

// set invincibility
void Captain::setInvincible(bool invincible)
{
	this->invincible = invincible;
}

// get invincibility
bool Captain::isInvincible()
{
	return this->invincible;
}

fix10_6 Captain::getFrictionOnCollision(SpatialObject collidingObject, const Vector3D* collidingObjectNormal)
{
	// ignore friction on y axis
	if(collidingObjectNormal->x && !collidingObjectNormal->y)
	{
		return 0;
	}

	return Base::getFrictionOnCollision(this, collidingObject, collidingObjectNormal);
}

// process collisions
bool Captain::enterCollision(const CollisionInformation* collisionInformation)
{
	Shape collidingShape = collisionInformation->collidingShape;
	SpatialObject collidingObject = Shape::getOwner(collidingShape);

	switch(SpatialObject::getInGameType(collidingObject))
	{
		// speed things up by breaking early
		case kShape:

			break;

		case kFloor:

			RumblePakManager::startEffect(&RumbleEffectLand);
			break;

		case kItemDuck:

			this->ducks++;

			// inform item
			MessageDispatcher::dispatchMessage(0, Object::safeCast(this), Object::safeCast(collidingObject), kItemTaken, NULL);

			// inform gui
			Object::fireEvent(EventManager::getInstance(), kEventDuckCollected);

			return true;
			break;

		case kLift:

			// inform lift
			MessageDispatcher::dispatchMessage(0, Object::safeCast(this), Object::safeCast(collidingObject), kLiftActivate, NULL);

			// inform gui
			Object::fireEvent(EventManager::getInstance(), kEventLiftActivated);

			// stop and hide captain
			Entity::hide(this);
			Actor::stopAllMovement(this);

			// disable user input
			Game::disableKeypad(Game::getInstance());

			return true;
			break;

		case kStageExitPoint:

			// inform exit point
			Object::fireEvent(EventManager::getInstance(), kEventExitPointReached);

			// disable user input
			Game::disableKeypad(Game::getInstance());

			return true;
			break;

		case kEnemy:
		case kEnemyProjectile:

			Captain::takeDamageFrom(this, 1);
			return true;
			break;

		case kMessage:

			MessageDispatcher::dispatchMessage(0, Object::safeCast(this), Object::safeCast(collidingObject), kGameEnterCollision, NULL);
			return true;
			break;

		case kMovingPlatform:
		case kTopShape:
			{
				if((0 > Body::getVelocity(this->body).y) || Captain::isBelow(this, collisionInformation->shape, collisionInformation))
				{
					// don't further process collision
					return false;
				}
			}
			break;

		case kKillShape:
			{
				Captain::die(this);
				return false;
				break;
			}
			break;
	}

	return Base::enterCollision(this, collisionInformation) && (__ABS(collisionInformation->solutionVector.direction.y) > __ABS(collisionInformation->solutionVector.direction.x));
}

// process collisions
bool Captain::updateCollision(const CollisionInformation* collisionInformation)
{
	Shape collidingShape = collisionInformation->collidingShape;
	SpatialObject collidingObject = Shape::getOwner(collidingShape);

	switch(SpatialObject::getInGameType(collidingObject))
	{
		case kEnemy:

			Captain::takeDamageFrom(this, 1);
			return false;
			break;
	}

	return false;
}

void Captain::capVelocity(bool discardPreviousMessages)
{
	if(discardPreviousMessages)
	{
		MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kCaptainCheckVelocity);
	}

	if(Body::isActive(this->body))
	{
		Velocity velocity = Body::getVelocity(this->body);

		if(velocity.y)
		{
			if(CAPTAIN_MAX_VELOCITY_Y < velocity.y && __UNIFORM_MOVEMENT != Body::getMovementType(this->body).y)
			{
				velocity.x = 0;
				velocity.y = CAPTAIN_MAX_VELOCITY_Y;
				velocity.z = 0;

				//Body::moveUniformly(this->body, velocity);
			}
			else if(0 < velocity.y)
			{
				MessageDispatcher::dispatchMessage(CAPTAIN_CHECK_Y_VELOCITY, Object::safeCast(this), Object::safeCast(this), kCaptainCheckVelocity, NULL);
			}
		}
		else
		{
			MessageDispatcher::dispatchMessage(1, Object::safeCast(this), Object::safeCast(this), kCaptainCheckVelocity, NULL);
		}
	}
}

bool Captain::handleMessage(Telegram telegram)
{
	// handle messages that any state would handle here
	switch(Telegram::getMessage(telegram))
	{
		case kCaptainCheckVelocity:

			Captain::capVelocity(this, false);
			return true;
			break;

		case kCaptainStopInvincibility:

			Captain::setInvincible(this, false);
			return true;
			break;

		case kEntityFlash:

			Captain::flash(this);
			return true;
			break;

		case kMessageBodyStopped:

			if(-1 == this->jumps)
			{
				return true;
			}
			break;
	}

	return Base::handleMessage(this, telegram);
}

// process message
bool Captain::handlePropagatedMessage(int message)
{
	switch(message)
	{
		case kLevelSetUp:

			break;

		case kLevelStarted:
			{
				Vector3DFlag positionFlag = {true, true, true};
				CustomCameraMovementManager::setPositionFlag(CustomCameraMovementManager::getInstance(), positionFlag);
			}
			break;

	}

	return false;
}

void Captain::suspend()
{
	Base::suspend(this);
}

void Captain::resume()
{
	Base::resume(this);

	Camera::focus(Camera::getInstance(), false);

	Vector3DFlag positionFlag = {true, true, true};
	CustomCameraMovementManager::setPositionFlag(CustomCameraMovementManager::getInstance(), positionFlag);
}

bool Captain::isBelow(Shape shape, const CollisionInformation* collisionInformation)
{
	RightBox shapeRightBox = Shape::getSurroundingRightBox(shape);
	RightBox collidingShapeRightBox = Shape::getSurroundingRightBox(collisionInformation->collidingShape);

	fix10_6 captainBottomPosition = shapeRightBox.y1 - ((shapeRightBox.y1 - shapeRightBox.y0) >> 1) - (Body::getLastDisplacement(this->body).y << 1) / 2;

	return captainBottomPosition > collidingShapeRightBox.y0 || __ABS(collisionInformation->solutionVector.direction.y) < __ABS(collisionInformation->solutionVector.direction.x);
}

void Captain::update(u32 elapsedTime)
{
	Base::update(this, elapsedTime);

	Captain::updateHeadYPosition(this);
}

void Captain::setDirection(Direction direction)
{
	Base::setDirection(this, direction);
	Captain::updateHeadXPosition(this);
}

void Captain::updateHeadXPosition()
{
	Vector3D position = *Container::getLocalPosition(this->headEntity);
	Entity::setLocalPosition(this->headEntity, &position);
}

void Captain::updateHeadYPosition()
{
	s8 offsetX = 0;
	s8 offsetY = 0;

	s16 actualFrame = AnimatedEntity::getActualFrame(this);
	AnimationController animationController = Sprite::getAnimationController(VirtualNode::getData(VirtualList::begin(Entity::getSprites(this))));

	if(AnimationController::isPlayingFunction(animationController, "Idle"))
	{
		switch(actualFrame)
		{
			case 0:
			case 1:
			case 4:
			case 5: offsetY = -1; break;
			case 2:
			case 3: offsetY = -2; break;
			case 6: offsetY = 1; break;
			case 7: offsetY = 0; break;
		}
	}
	else if(AnimationController::isPlayingFunction(animationController, "Walk"))
	{
		offsetY = (actualFrame == 0 || actualFrame == 5 || actualFrame == 6 || actualFrame == 11) ? 0 : 1;
	}
	else if(AnimationController::isPlayingFunction(animationController, "Jump") || AnimationController::isPlayingFunction(animationController, "Fall"))
	{
		offsetY = -3;
	}
	else if(AnimationController::isPlayingFunction(animationController, "KneelDown"))
	{
		offsetX = 1;
		switch(actualFrame)
		{
			case 5: offsetY = 9; break;
			case 4: offsetY = 10; break;
			case 3: offsetY = 9; break;
			case 2: offsetY = 5; break;
			case 1: offsetY = 3; break;
			case 0: offsetY = 2; break;
		}
	}

	Vector3D position = *Container::getLocalPosition(this->headEntity);
	position.x = (this->inputDirection.x == __RIGHT) ? __PIXELS_TO_METERS(offsetX + CAPTAIN_HEAD_X_OFFSET) : __PIXELS_TO_METERS(-(offsetX + CAPTAIN_HEAD_X_OFFSET));
	position.y = __PIXELS_TO_METERS(offsetY + CAPTAIN_HEAD_Y_OFFSET);
	Entity::setLocalPosition(this->headEntity, &position);
}

/*
void Captain::updateSprite(Direction direction)
{
	CharSet charSet = Texture::getCharSet(Sprite::getTexture(Sprite::safeCast(VirtualList::front(this->sprites))), true);
	CharSet charSetBlack = Texture::getCharSet(Sprite::getTexture(Sprite::safeCast(VirtualList::back(this->sprites))), true);

	CharSetSpec* charSetSpec = NULL;
	CharSetSpec* charSetBlackSpec = NULL;

	switch(direction.x)
	{
		case __LEFT:

			charSetSpec = &CAPTAIN_LEFT_CH;
			charSetBlackSpec = &CAPTAIN_LEFT_BLACK_CH;
			break;

		default:
		case __RIGHT:

			charSetSpec = &CAPTAIN_RIGHT_CH;
			charSetBlackSpec = &CAPTAIN_RIGHT_BLACK_CH;
			break;
	}

	CharSet::setCharSetSpec(charSet, charSetSpec);
	CharSet::setCharSetSpec(charSetBlack, charSetBlackSpec);
	CharSet::rewrite(charSet);
	CharSet::rewrite(charSetBlack);
}
*/

void Captain::syncRotationWithBody()
{
	fix10_6 xLastDisplacement = Body::getLastDisplacement(this->body).x;

	Direction direction = Entity::getDirection(this);

	if(0 < xLastDisplacement)
	{
		direction.x = __RIGHT;
		Entity::setDirection(this, direction);
	}
	else if(0 > xLastDisplacement)
	{
		direction.x = __LEFT;
		Entity::setDirection(this, direction);
	}
}

void Captain::exitCollision(Shape shape, Shape shapeNotCollidingAnymore, bool isShapeImpenetrable)
{
	SpatialObject collidingObject = Shape::getOwner(shapeNotCollidingAnymore);

	switch(SpatialObject::getInGameType(collidingObject))
	{
		case kMessage:

			MessageDispatcher::dispatchMessage(0, Object::safeCast(this), Object::safeCast(collidingObject), kGameExitCollision, NULL);
			break;
	}

	Base::exitCollision(this, shape, shapeNotCollidingAnymore, isShapeImpenetrable);
}

u16 Captain::getAxisForShapeSyncWithDirection()
{
	return __X_AXIS;
}

void Captain::onHitAnimationComplete(Object eventFirer __attribute__ ((unused)))
{
	// reset invincible a bit later
	MessageDispatcher::dispatchMessage(CAPTAIN_FLASH_DURATION, Object::safeCast(this), Object::safeCast(this), kCaptainStopInvincibility, NULL);

	// start flashing of captain
	Captain::startFlashing(this);

	// give control back to player
	Game::enableKeypad(Game::getInstance());

	// resume physics
	GameState::pausePhysics(Game::getCurrentState(Game::getInstance()), false);
	GameState::pauseAnimations(Game::getCurrentState(Game::getInstance()), false);

	StateMachine::swapState(this->stateMachine, State::safeCast(CaptainIdle::getInstance()));
}

void Captain::toggleShapes(bool kneeling)
{
	VirtualList shapes = Entity::getShapes(this);
	Shape shapeStanding = Shape::safeCast(VirtualList::front(shapes));
	Shape shapeKneeling = Shape::safeCast(VirtualList::back(shapes));
	Shape::enable(shapeStanding, !kneeling);
	Shape::enable(shapeKneeling, kneeling);
}

void Captain::reload()
{
	if(this->gums < CAPTAIN_MAX_GUMS)
	{
		RumblePakManager::startEffect(&RumbleEffectReload);
		
		// switch to reload state
		StateMachine::swapState(this->stateMachine, State::safeCast(CaptainReload::getInstance()));

		SoundManager::playSound(
			SoundManager::getInstance(),
			&RELOAD_SND,
			kPlayAll,
			(const Vector3D*)&this->transformation.globalPosition,
			kSoundWrapperPlaybackNormal,
			NULL,
			NULL
		);
	}
}

void Captain::onReloadAnimationComplete(Object eventFirer __attribute__ ((unused)))
{
	this->gums = CAPTAIN_MAX_GUMS;

	Object::fireEvent(EventManager::getInstance(), kEventGumsReloaded);

	StateMachine::swapState(this->stateMachine, State::safeCast(CaptainIdle::getInstance()));
}