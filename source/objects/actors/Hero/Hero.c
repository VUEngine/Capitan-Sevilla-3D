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

#include <GameEvents.h>
#include <Game.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Camera.h>
#include <Box.h>
#include <PhysicalWorld.h>
#include <KeypadManager.h>
#include <Hero.h>
#include <HeroIdle.h>
#include <HeroMoving.h>
#include <HeroKneel.h>
#include <HeroDead.h>
#include <CustomCameraMovementManager.h>
#include <CustomCameraEffectManager.h>
#include <EventManager.h>
#include <SoundManager.h>
#include <PlatformerLevelState.h>
#include <MovingOneWayEntity.h>
#include <ProjectileEjector.h>
#include <debugConfig.h>

//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern double fabs (double);

extern const u16 COLLECT_SND[];
extern const u16 FIRE_SND[];
extern const u16 JUMP_SND[];
extern CharSetDefinition HERO_LEFT_CH;
extern CharSetDefinition HERO_LEFT_BLACK_CH;
extern CharSetDefinition HERO_RIGHT_CH;
extern CharSetDefinition HERO_RIGHT_BLACK_CH;
extern EntityDefinition SAUSAGE_EJECTOR_PE;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// Only one instance
static Hero hero = NULL;

// there can only be one hero instantiated
static Hero Hero::getInstance()
{
	return hero;
}

static void Hero::setInstance(Hero instance)
{
	ASSERT(!hero, "Hero::setInstance: already instantiated");

	hero = instance;
}

// class's constructor
void Hero::constructor(HeroDefinition* heroDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor((ActorDefinition*)heroDefinition, id, internalId, name);

	// construct the hero's state machine
	this->stateMachine = new StateMachine(this);

	// init class variables
	this->energy = HERO_INITIAL_ENERGY;
	this->invincible = false;
	this->jumps = 0;
	this->sausages = HERO_INITIAL_SAUSAGES;
	this->keepAddingForce = false;
	this->sausageEjectorEntity = NULL;

	Hero::setInstance(this);

	Object::addEventListener(Object::safeCast(PlatformerLevelState::getInstance()), Object::safeCast(this), (EventListener)Hero::onUserInput, kEventUserInput);

	this->inputDirection = Entity::getDirection(Entity::safeCast(this));
}

// class's destructor
void Hero::destructor()
{

	ASSERT(hero, "Hero::destructor: already deleted");
	ASSERT(hero == this, "Hero::destructor: more than one instance");

	// remove event listeners
	Object::removeEventListener(Object::safeCast(PlatformerLevelState::getInstance()), Object::safeCast(this), (EventListener)Hero::onUserInput, kEventUserInput);

	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kHeroCheckVelocity);
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kHeroFlash);

	// free the instance pointers
	hero = NULL;

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void Hero::ready(bool recursive)
{


	Entity::informShapesThatStartedMoving(Entity::safeCast(this));

	// call base
	Base::ready(this, recursive);

	// override with progress from progress manager
	ProgressManager progressManager = ProgressManager::getInstance();
	if(progressManager)
	{
		//this->energy = ProgressManager::getHeroCurrentEnergy(progressManager);
		//this->sausages = ProgressManager::getHeroCurrentSausages(progressManager);
	}

	// initialize me as idle
	StateMachine::swapState(this->stateMachine, State::safeCast(HeroIdle::getInstance()));

	// add sausage ejector
	Hero::addSausageEjectorEntity(this);
}

void Hero::addSausageEjectorEntity()
{


	Vector3D position = {__PIXELS_TO_METERS(16), __PIXELS_TO_METERS(-6), 0};
	this->sausageEjectorEntity = Entity::addChildEntity(Entity::safeCast(this), &SAUSAGE_EJECTOR_PE, -1, NULL, &position, (void*)3);
}

void Hero::shoot(bool active)
{
	ProjectileEjector::setActive(this->sausageEjectorEntity, active);
}

void Hero::kneel()
{
	// stop movement
	Actor::stopMovement(Actor::safeCast(this), __X_AXIS);

	// switch to kneel state
	StateMachine::swapState(this->stateMachine, State::safeCast( HeroKneel::getInstance()));
}

// make him jump
void Hero::jump(bool checkIfYMovement)
{


	if(this->body)
	{
		// determine the maximum number of possible jumps before reaching ground again
		s8 allowedNumberOfJumps = 1;

		// check if more jumps are allowed
		if(this->jumps < allowedNumberOfJumps)
		{
			// init a force to add to the hero's momentum
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
				//Hero::startedMovingOnAxis(this, __Y_AXIS);

				// add more force when running, normal force otherwise
				force.y = __FIX10_6_MULT(__ABS(yBouncingPlaneNormal), HERO_NORMAL_JUMP_INPUT_FORCE);

				// add the force to actually make the hero jump
				Actor::addForce(Actor::safeCast(this), &force);
			}
			else
			{
				// hack to avoid the processing of kBodyStopped message triggered by the call to Actor::stopMovement
				this->jumps = -1;

				// stop movement to gain full momentum of the jump force that will be added
				Actor::stopMovement(Actor::safeCast(this), __Y_AXIS);

				// set second jump performed
				this->jumps = 2;

				// add the force to actually make the hero jump
				Actor::addForce(Actor::safeCast(this), &force);
			}

			// play jump animation
			AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this), "Jump");

			// play jump sound
			SoundManager::playFxSound(SoundManager::getInstance(), JUMP_SND, this->transformation.globalPosition);
		}
	}
}

// keep movement
void Hero::addForce(u16 axis, bool enableAddingForce)
{


	if(enableAddingForce)
	{
		this->keepAddingForce = true;
	}

	if(!this->keepAddingForce)
	{
		return;
	}

	fix10_6 maxVelocity = HERO_MAX_VELOCITY_X;

	Velocity velocity = Body::getVelocity(this->body);

	Direction direction = Entity::getDirection(Entity::safeCast(this));

	if(direction.x != this->inputDirection.x ||
		((__X_AXIS & axis) && maxVelocity > __ABS(velocity.x)) ||
		((__Z_AXIS & axis) && maxVelocity > __ABS(velocity.z)) ||
		Actor::hasChangedDirection(Actor::safeCast(this), __X_AXIS) ||
		Actor::hasChangedDirection(Actor::safeCast(this), __Z_AXIS))
	{
		fix10_6 inputForce = !Body::getNormal(this->body).y ? HERO_X_INPUT_FORCE_WHILE_JUMPING : HERO_INPUT_FORCE;
		fix10_6 xForce = (__X_AXIS & axis) ? __RIGHT == this->inputDirection.x ? inputForce : -inputForce : 0;
		fix10_6 zForce = 0; //(__Z_AXIS & axis) ? __FAR == this->inputDirection.z ? inputForce : -inputForce : 0;
		Force force =
		{
			xForce,
			0,
			zForce
		};

		Actor::addForce(Actor::safeCast(this), &force);
	}
	else
	{
		if(__UNIFORM_MOVEMENT != Body::getMovementType(this->body).x || (__ABS(velocity.x) > maxVelocity && !(__Y_AXIS & Body::getMovementOnAllAxes(this->body))))
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
void Hero::stopAddingForce()
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
		fix10_6 inputForce = HERO_FORCE_FOR_STOPPING;
		fix10_6 xForce = __RIGHT == this->inputDirection.x ? inputForce : -inputForce;
		fix10_6 zForce = 0; //(__Z_AXIS & axis) ? __FAR == this->inputDirection.z ? inputForce : -inputForce : 0;
		Force force =
		{
			xForce,
			0,
			zForce
		};

		Actor::addForce(Actor::safeCast(this), &force);
	}
	else
	{
		Hero::stopMovementOnAxis(this, __X_AXIS | __Z_AXIS);
	}
}

// started moving over axis
void Hero::startedMovingOnAxis(u16 axis)
{
	if(__Y_AXIS & axis)
	{
		Hero::capVelocity(this, true);
	}

	// start movement
	if(State::safeCast(HeroMoving::getInstance()) != StateMachine::getCurrentState(this->stateMachine))
	{
		if(__X_AXIS & axis)
		{
			this->keepAddingForce = true;
			AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this), "Walk");
		}

		StateMachine::swapState(this->stateMachine, State::safeCast( HeroMoving::getInstance()));
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
bool Hero::stopMovementOnAxis(u16 axis)
{


	// if being hit do nothing
	if(!Body::isActive(this->body))
	{
		return false;
	}

	bool movementState = Body::getMovementOnAllAxes(this->body);

	if((__X_AXIS & axis) && !(__Y_AXIS & movementState))
	{
		AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this), "Idle");
	}

	// if there is something below
	if(0 > Body::getNormal(this->body).y)
	{
		if(__Y_AXIS & axis)
		{
			MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kHeroCheckVelocity);

			this->jumps = 0;

			if(Body::getVelocity(this->body).x)
			{
				if(this->inputDirection.x)
				{
					AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this), "Walk");
				}
			}
		}

		if((__Z_AXIS & axis) || (!movementState && State::safeCast(HeroIdle::getInstance()) != StateMachine::getCurrentState(this->stateMachine)))
		{
			this->keepAddingForce = false;
			this->jumps = 0;
			StateMachine::swapState(this->stateMachine, State::safeCast(HeroIdle::getInstance()));
			return true;
		}
		else
		{
			AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this), "Walk");
		}
	}
	else
	{
		AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this), "Fall");
	}

	return false;
}

// check direction
void Hero::checkDirection(u32 pressedKey, char* animation)
{


	bool movementState = Body::getMovementOnAllAxes(this->body);
	//Direction direction = Entity::getDirection(Entity::safeCast(this));

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
		this->inputDirection.z = __FAR;
	}
	else if(K_LD & pressedKey)
	{
		this->inputDirection.z = __NEAR;
	}

	if(animation && !(__Y_AXIS & movementState))
	{
		AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this), animation);
	}
}

void Hero::takeHitFrom(SpatialObject collidingObject, int energyToReduce, bool pause, bool invincibleWins)
{
	if(!Hero::isInvincible(this) || !invincibleWins)
	{
		// start short screen shake
		Camera::startEffect(Camera::getInstance(), kShake, 200);

		// play hit sound
		SoundManager::playFxSound(SoundManager::getInstance(), FIRE_SND, this->transformation.globalPosition);

		if(invincibleWins && (this->energy - energyToReduce >= 0))
		{
			Hero::setInvincible(this, true);

			// reset invincible a bit later
			MessageDispatcher::dispatchMessage(HERO_FLASH_DURATION, Object::safeCast(this), Object::safeCast(this), kHeroStopInvincibility, NULL);

			// start flashing of hero
			MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kHeroFlash);
			MessageDispatcher::dispatchMessage(0, Object::safeCast(this), Object::safeCast(this), kHeroFlash, NULL);

			// reduce energy
			this->energy -= energyToReduce;

			if(pause)
			{
				Actor::stopAllMovement(Actor::safeCast(this));
				Game::disableKeypad(Game::getInstance());
				GameState::pausePhysics(Game::getCurrentState(Game::getInstance()), true);
				//GameState::pauseAnimations(Game::getCurrentState(Game::getInstance()), true);
				MessageDispatcher::dispatchMessage(500, Object::safeCast(this), Object::safeCast(this), kHeroResumePhysics, collidingObject);
			}

			// play animation
			AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this), "Hit");

			// inform others to update ui etc
			Object::fireEvent(Object::safeCast(EventManager::getInstance()), kEventHitTaken);
		}
		else
		{
			Hero::die(this);
		}
	}
}

// flash after being hit
void Hero::flash()
{


	// only flash as long as hero is invincible
	if(Hero::isInvincible(this))
	{
		// toggle between original and flash palette
		Hero::toggleFlashPalette(this);

		// next flash state change after HERO_FLASH_INTERVAL milliseconds
		MessageDispatcher::dispatchMessage(HERO_FLASH_INTERVAL, Object::safeCast(this), Object::safeCast(this), kHeroFlash, NULL);
	}
	else
	{
		// set palette back to original
		Hero::resetPalette(this);
	}
}

void Hero::toggleFlashPalette()
{
	// get all of the hero's sprites and loop through them
	VirtualList sprites = Entity::getSprites(Entity::safeCast(this));
	VirtualNode node = VirtualList::begin(sprites);
	for(; node; node = VirtualNode::getNext(node))
	{
		// get sprite's texture
		Sprite sprite = Sprite::safeCast(VirtualNode::getData(node));
		Texture texture = Sprite::getTexture(sprite);

		// get original palette
		TextureDefinition* textureDefinition = Texture::getDefinition(texture);

		// set new palette
		if(Texture::getPalette(texture) == textureDefinition->palette)
		{
			Texture::setPalette(texture, HERO_FLASH_PALETTE);
		}
		else
		{
			Texture::setPalette(texture, textureDefinition->palette);
		}

		// rewrite sprite to bgmap to apply changed palette
		Sprite::rewrite(sprite);
	}
}

void Hero::resetPalette()
{
	// get all of hero's sprites and loop through them
	VirtualList sprites = Entity::getSprites(Entity::safeCast(this));
	VirtualNode node = VirtualList::begin(sprites);
	for(; node; node = VirtualNode::getNext(node))
	{
		// get sprite's texture
		Sprite sprite = Sprite::safeCast(VirtualNode::getData(node));
		Texture texture = Sprite::getTexture(sprite);

		// get original palette and set it
		TextureDefinition* textureDefinition = Texture::getDefinition(texture);
		Texture::setPalette(texture, textureDefinition->palette);

		// rewrite sprite to bgmap to apply changed palette
		Sprite::rewrite(sprite);
	}
}

// die hero
void Hero::die()
{
	// unregister the shape for collision detection
	Entity::activateShapes(Entity::safeCast(this), false);

	// show animation
	AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this), "Dead");

	// set flashing palette back to original
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kHeroFlash);
	Hero::resetPalette(this);

	Actor::stopAllMovement(Actor::safeCast(this));
	Game::disableKeypad(Game::getInstance());
	Hero::setInvincible(this, true);

	// go to dead state
	StateMachine::swapState(this->stateMachine, State::safeCast(HeroDead::getInstance()));

	// announce my dead
	Object::fireEvent(Object::safeCast(EventManager::getInstance()), kEventHeroDied);
}

// process user input
void Hero::onUserInput(Object eventFirer __attribute__ ((unused)))
{
	UserInput userInput = PlatformerLevelState::getUserInput(PlatformerLevelState::getInstance());

	HeroState currentState = HeroState::safeCast(StateMachine::getCurrentState(this->stateMachine));

	if(userInput.pressedKey)
	{
		HeroState::onKeyPressed(currentState, this, &userInput);
	}

	if(userInput.releasedKey)
	{
		HeroState::onKeyReleased(currentState, this, &userInput);
	}

	if(userInput.holdKey)
	{
		HeroState::onKeyHold(currentState, this, &userInput);
	}
}

// get energy
u8 Hero::getEnergy()
{
	return this->energy;
}

// get number of sausages
u8 Hero::getSausages()
{
	return this->sausages;
}

// set invincibility
void Hero::setInvincible(bool invincible)
{
	this->invincible = invincible;
}

// get invincibility
bool Hero::isInvincible()
{
	return this->invincible;
}

fix10_6 Hero::getFrictionOnCollision(SpatialObject collidingObject, const Vector3D* collidingObjectNormal)
{
	// ignore friction on y axis
	if(collidingObjectNormal->x && !collidingObjectNormal->y)
	{
		return 0;
	}

	return Base::getFrictionOnCollision(Actor::safeCast(this), collidingObject, collidingObjectNormal);
}

// process collisions
bool Hero::enterCollision(const CollisionInformation* collisionInformation)
{

	ASSERT(collisionInformation->collidingShape, "Hero::enterCollision: null collidingObjects");

	Shape collidingShape = collisionInformation->collidingShape;
	SpatialObject collidingObject = Shape::getOwner(collidingShape);

	switch(SpatialObject::getInGameType(collidingObject))
	{
		// speed things up by breaking early
		case kShape:
			break;

		case kEnemy:
		case kEnemyProjectile:

			Hero::takeHitFrom(this, collidingObject, 1, true, true);
			return false;
			break;

		case kMovingPlatform:
		case kTopShape:
			{
				if((0 > Body::getVelocity(this->body).y) || Hero::isBelow(this, collisionInformation->shape, collisionInformation))
				{
					// don't further process collision
					return false;
				}
			}
			break;
	}

	return Base::enterCollision(Actor::safeCast(this), collisionInformation) && (__ABS(collisionInformation->solutionVector.direction.y) > __ABS(collisionInformation->solutionVector.direction.x));
}

// process collisions
bool Hero::updateCollision(const CollisionInformation* collisionInformation)
{

	ASSERT(collisionInformation->collidingShape, "Hero::updateCollision: null collidingObjects");

	Shape collidingShape = collisionInformation->collidingShape;
	SpatialObject collidingObject = Shape::getOwner(collidingShape);

	switch(SpatialObject::getInGameType(collidingObject))
	{
		case kEnemy:

			Hero::takeHitFrom(this, collidingObject, 1, true, true);
			return false;
			break;
	}

	return false;
}

void Hero::capVelocity(bool discardPreviousMessages)
{


	if(discardPreviousMessages)
	{
		MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kHeroCheckVelocity);
	}

	if(Body::isActive(this->body))
	{
		Velocity velocity = Body::getVelocity(this->body);

		if(velocity.y)
		{
			if(HERO_MAX_VELOCITY_Y < velocity.y && __UNIFORM_MOVEMENT != Body::getMovementType(this->body).y)
			{
				velocity.x = 0;
				velocity.y = HERO_MAX_VELOCITY_Y;
				velocity.z = 0;

				//Body::moveUniformly(this->body, velocity);
			}
			else if(0 < velocity.y)
			{
				MessageDispatcher::dispatchMessage(HERO_CHECK_Y_VELOCITY, Object::safeCast(this), Object::safeCast(this), kHeroCheckVelocity, NULL);
			}
		}
		else
		{
			MessageDispatcher::dispatchMessage(1, Object::safeCast(this), Object::safeCast(this), kHeroCheckVelocity, NULL);
		}
	}
}

bool Hero::handleMessage(Telegram telegram)
{


	// handle messages that any state would handle here
	switch(Telegram::getMessage(telegram))
	{
		case kHeroCheckVelocity:

			Hero::capVelocity(this, false);
			return true;
			break;

		case kHeroStopInvincibility:

			Hero::setInvincible(this, false);
			return true;
			break;

		case kHeroFlash:

			Hero::flash(this);
			return true;
			break;

		case kHeroResumePhysics:

			Game::enableKeypad(Game::getInstance());
			GameState::pausePhysics(Game::getCurrentState(Game::getInstance()), false);
			GameState::pauseAnimations(Game::getCurrentState(Game::getInstance()), false);

			Velocity velocity = Body::getVelocity(this->body);

			if(!velocity.y)
			{
				if(velocity.x)
				{
					AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this), "Walk");
				}
				else
				{
					AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this), "Idle");
				}
			}
			else if(velocity.x)
			{
				AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this), "Walk");
			}
			else
			{
				AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this), "Idle");
			}

			break;

		case kBodyStopped:

			if(-1 == this->jumps)
			{
				return true;
			}
			break;
	}

	return Base::handleMessage(Actor::safeCast(this), telegram);
}

// process message
bool Hero::handlePropagatedMessage(int message)
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

void Hero::suspend()
{


	__CALL_BASE_METHOD(Actor, suspend, this);
}

void Hero::resume()
{


	__CALL_BASE_METHOD(Actor, resume, this);

	Camera::focus(Camera::getInstance(), false);

	Vector3DFlag positionFlag = {true, true, true};
	CustomCameraMovementManager::setPositionFlag(CustomCameraMovementManager::getInstance(), positionFlag);
}

bool Hero::isBelow(Shape shape, const CollisionInformation* collisionInformation)
{


	RightBox shapeRightBox = Shape::getSurroundingRightBox(shape);
	RightBox collidingShapeRightBox = Shape::getSurroundingRightBox(collisionInformation->collidingShape);

	fix10_6 heroBottomPosition = shapeRightBox.y1 - ((shapeRightBox.y1 - shapeRightBox.y0) >> 1) - (Body::getLastDisplacement(this->body).y << 1) / 2;

	return heroBottomPosition > collidingShapeRightBox.y0 || __ABS(collisionInformation->solutionVector.direction.y) < __ABS(collisionInformation->solutionVector.direction.x);
}

u16 Hero::getAxisForFlipping()
{
	return __X_AXIS;
}

bool Hero::isAffectedByRelativity()
{


	return true;
}

void Hero::updateSprite(Direction direction)
{
	CharSet charSet = Texture::getCharSet(Sprite::getTexture(Sprite::safeCast(VirtualList::front(this->sprites))), true);
	CharSet charSetBlack = Texture::getCharSet(Sprite::getTexture(Sprite::safeCast(VirtualList::back(this->sprites))), true);

	CharSetDefinition* charSetDefinition = NULL;
	CharSetDefinition* charSetBlackDefinition = NULL;

	switch(direction.x)
	{
		case __LEFT:

			charSetDefinition = &HERO_LEFT_CH;
			charSetBlackDefinition = &HERO_LEFT_BLACK_CH;
			break;

		default:
		case __RIGHT:

			charSetDefinition = &HERO_RIGHT_CH;
			charSetBlackDefinition = &HERO_RIGHT_BLACK_CH;
			break;
	}

	CharSet::setCharSetDefinition(charSet, charSetDefinition);
	CharSet::setCharSetDefinition(charSetBlack, charSetBlackDefinition);
	CharSet::rewrite(charSet);
	CharSet::rewrite(charSetBlack);
}

void Hero::syncRotationWithBody()
{


	fix10_6 xLastDisplacement = Body::getLastDisplacement(this->body).x;

	Direction direction = Entity::getDirection(Entity::safeCast(this));

	if(0 < xLastDisplacement)
	{
		direction.x = __RIGHT;
		Entity::setDirection(Entity::safeCast(this), direction);
		Hero::updateSprite(this, direction);
	}
	else if(0 > xLastDisplacement)
	{
		direction.x = __LEFT;
		Entity::setDirection(Entity::safeCast(this), direction);
		Hero::updateSprite(this, direction);
	}
}

void Hero::exitCollision(Shape shape, Shape shapeNotCollidingAnymore, bool isShapeImpenetrable)
{


	Base::exitCollision(this, shape, shapeNotCollidingAnymore, isShapeImpenetrable);
}

u16 Hero::getAxesForShapeSyncWithDirection()
{
	return __NO_AXIS;
}

bool Hero::isVisible(int pad __attribute__ ((unused)), bool recursive __attribute__ ((unused)))
{
	return true;
}