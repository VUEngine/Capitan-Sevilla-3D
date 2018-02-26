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
#include "Hero.h"
#include "states/HeroIdle.h"
#include "states/HeroMoving.h"
#include <CustomCameraMovementManager.h>
#include <CustomCameraEffectManager.h>
#include <CameraTriggerEntity.h>
#include <EventManager.h>
#include <SoundManager.h>
#include <debugConfig.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Hero, Actor);


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern double fabs (double);

extern const u16 COLLECT_SND[];
extern const u16 FIRE_SND[];
extern const u16 JUMP_SND[];
extern CharSetDefinition HERO_CH;

extern CameraTriggerEntityROMDef CAMERA_BOUNDING_BOX_IG;


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void Hero_onUserInput(Hero this, Object eventFirer);
void Hero_updateSprite(Hero this);
static void Hero_slide(Hero this);
void Hero_losePowerUp(Hero this);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// Only one instance
Hero hero = NULL;

// there can only be one hero instantiated
Hero Hero_getInstance()
{
	return hero;
}

void Hero_setInstance(Hero instance)
{
	ASSERT(!hero, "Hero::setInstance: already instantiated");

	hero = instance;
}

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Hero, HeroDefinition* heroDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(Hero, heroDefinition, id, internalId, name);

// class's constructor
void Hero_constructor(Hero this, HeroDefinition* heroDefinition, s16 id, s16 internalId, const char* const name)
{
	ASSERT(this, "Hero::constructor: null this");

	// construct base
	__CONSTRUCT_BASE(Actor, (ActorDefinition*)heroDefinition, id, internalId, name);

	// construct the game state machine
	this->stateMachine = __NEW(StateMachine, this);

	// init class variables
	this->coins = 0;
	this->hasKey = false;
	this->cameraBoundingBox = NULL;
	this->energy = HERO_INITIAL_ENERGY;
	this->powerUp = kPowerUpNone;
	this->invincible = false;
	this->jumps = 0;
	this->keepAddingForce = false;
	this->underWater = false;

	Hero_setInstance(this);

	Object_addEventListener(__SAFE_CAST(Object, PlatformerLevelState_getInstance()), __SAFE_CAST(Object, this), (EventListener)Hero_onUserInput, kEventUserInput);

	this->inputDirection = Entity_getDirection(__SAFE_CAST(Entity, this));
}

// class's destructor
void Hero_destructor(Hero this)
{
	ASSERT(this, "Hero::destructor: null this");
	ASSERT(hero, "Hero::destructor: already deleted");
	ASSERT(hero == this, "Hero::destructor: more than one instance");

	// remove event listeners
	Object_removeEventListener(__SAFE_CAST(Object, PlatformerLevelState_getInstance()), __SAFE_CAST(Object, this), (EventListener)Hero_onUserInput, kEventUserInput);

	// announce my dead
	Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), kEventHeroDied);

	// discard pending delayed messages
	MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kHeroCheckVelocity);
	MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kHeroFlash);

	// free the instance pointers
	this->cameraBoundingBox = NULL;
	hero = NULL;

	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

void Hero_ready(Hero this, bool recursive)
{
	ASSERT(this, "Hero::ready: null this");

	Entity_informShapesThatStartedMoving(__SAFE_CAST(Entity, this));

	// call base
	__CALL_BASE_METHOD(Actor, ready, this, recursive);

	// override with progress from progress manager
	ProgressManager progressManager = ProgressManager_getInstance();
	if(progressManager)
	{
		this->energy = ProgressManager_getHeroCurrentEnergy(progressManager);

		u8 currentPowerUp = ProgressManager_getHeroCurrentPowerUp(progressManager);
		if(currentPowerUp != this->powerUp)
		{
			this->powerUp = currentPowerUp;
			Hero_updateSprite(this);
		}

		this->hasKey = ProgressManager_heroHasKey(ProgressManager_getInstance());
	}

	// initialize me as idle
	StateMachine_swapState(this->stateMachine, __SAFE_CAST(State, HeroIdle_getInstance()));
}

void Hero_locateOverNextFloor(Hero this __attribute__ ((unused)))
{
/*	Vector3D direction = {0, 1, 0};

	SpatialObject collidingSpatialObject = CollisionManager_searchNextObjectOfCollision(Game_getCollisionManager(Game_getInstance()), this->shape, direction);
	ASSERT(collidingSpatialObject, "Hero::locateOverNextFloor: null collidingSpatialObject");

	if(collidingSpatialObject)
	{
		Vector3D displacement =
		{
			__I_TO_FIX10_6(0),
			__1I_FIX10_6,
			__I_TO_FIX10_6(0),
		};

		Shape_resolveCollision(this->shape, VirtualList_front(this->shapes), collidingShapesToRemove, displacement, true);
	}
	*/
}

// make him jump
void Hero_jump(Hero this, bool checkIfYMovement)
{
	ASSERT(this, "Hero::jump: null this");

	if(this->body)
	{
		// determine the maximum number of possible jumps before reaching ground again
		s8 allowedNumberOfJumps = this->underWater ? 127 : (this->powerUp == kPowerUpBandana) ? 2 : 1;

#ifdef GOD_MODE
	allowedNumberOfJumps = 127;
#endif

		// check if more jumps are allowed
		if(this->jumps < allowedNumberOfJumps)
		{
			// init a force to add to the hero's momentum
			Force force = {0, 0, 0};

			fix10_6 yBouncingPlaneNormal = Body_getLastNormalDirection(this->body).y;

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
				//Hero_startedMovingOnAxis(this, __Y_AXIS);

				// add more force when running, normal force otherwise
				force.y = __FIX10_6_MULT(__ABS(yBouncingPlaneNormal), HERO_NORMAL_JUMP_INPUT_FORCE);

				// add the force to actually make the hero jump
				Actor_addForce(__SAFE_CAST(Actor, this), &force);
			}
			else
			{
				// hack to avoid the processing of kBodyStopped message triggered by the call to Actor_stopMovement
				this->jumps = -1;

				// stop movement to gain full momentum of the jump force that will be added
				Actor_stopMovement(__SAFE_CAST(Actor, this), __Y_AXIS);

				// set second jump performed
				this->jumps = 2;

				// add the force to actually make the hero jump
				Actor_addForce(__SAFE_CAST(Actor, this), &force);
			}

			// play jump animation
			AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Jump");

			// play jump sound
			SoundManager_playFxSound(SoundManager_getInstance(), JUMP_SND, this->transformation.globalPosition);
		}
	}
}

// keep movement
void Hero_addForce(Hero this, u16 axis, bool enableAddingForce)
{
	ASSERT(this, "Hero::addForce: null this");

	if(enableAddingForce)
	{
		this->keepAddingForce = true;
	}

	if(!this->keepAddingForce)
	{
		return;
	}

	fix10_6 maxVelocity = HERO_MAX_VELOCITY_X;

	maxVelocity = this->underWater ? maxVelocity >> 1: maxVelocity;

	Velocity velocity = Body_getVelocity(this->body);

	Direction direction = Entity_getDirection(__SAFE_CAST(Entity, this));

	if(direction.x != this->inputDirection.x ||
		((__X_AXIS & axis) && maxVelocity > __ABS(velocity.x)) ||
		((__Z_AXIS & axis) && maxVelocity > __ABS(velocity.z)) ||
		Actor_hasChangedDirection(__SAFE_CAST(Actor, this), __X_AXIS) ||
		Actor_hasChangedDirection(__SAFE_CAST(Actor, this), __Z_AXIS))
	{
		fix10_6 inputForce = !Body_getNormal(this->body).y ? HERO_X_INPUT_FORCE_WHILE_JUMPING : HERO_INPUT_FORCE;
		fix10_6 xForce = (__X_AXIS & axis) ? __RIGHT == this->inputDirection.x ? inputForce : -inputForce : 0;
		fix10_6 zForce = 0; //(__Z_AXIS & axis) ? __FAR == this->inputDirection.z ? inputForce : -inputForce : 0;
		Force force =
		{
			xForce,
			0,
			zForce
		};

		Actor_addForce(__SAFE_CAST(Actor, this), &force);
	}
	else
	{
		if(__UNIFORM_MOVEMENT != Body_getMovementType(this->body).x || (__ABS(velocity.x) > maxVelocity && !(__Y_AXIS & Body_getMovementOnAllAxes(this->body))))
		{
			Velocity newVelocity =
			{
				(__X_AXIS & axis) ? ((int)maxVelocity * this->inputDirection.x) : 0,
				0,
				(__Z_AXIS & axis) ? ((int)maxVelocity * this->inputDirection.z) : 0,
			};

			Body_moveUniformly(this->body, newVelocity);
		}
	}
}

static void Hero_slide(Hero this)
{
	AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Slide");
}

// start movement
void Hero_stopAddingForce(Hero this)
{
	ASSERT(this, "Hero::stopMovement: null this");

	Velocity velocity = Body_getVelocity(this->body);

	this->keepAddingForce = false;

	// no input
//	this->inputDirection.x = 0;
//	this->inputDirection.y = 0;
//	this->inputDirection.z = 0;

	// if walking over something
	if(0 > Body_getNormal(this->body).y)
	{
		Hero_slide(this);
	}

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

		Actor_addForce(__SAFE_CAST(Actor, this), &force);
	}
	else
	{
		Hero_stopMovingOnAxis(this, __X_AXIS | __Z_AXIS);
	}
}

// started moving over axis
void Hero_startedMovingOnAxis(Hero this, u16 axis)
{
	if(__Y_AXIS & axis)
	{
		Hero_capVelocity(this, true);
	}

	// start movement
	if(__SAFE_CAST(State, HeroMoving_getInstance()) != StateMachine_getCurrentState(this->stateMachine))
	{
		if(__X_AXIS & axis)
		{
			this->keepAddingForce = true;
			AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Walk");
		}

		StateMachine_swapState(this->stateMachine, __SAFE_CAST(State,  HeroMoving_getInstance()));
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
bool Hero_stopMovingOnAxis(Hero this, u16 axis)
{
	ASSERT(this, "Hero::stopMovingOnAxis: null this");

	// if being hit do nothing
	if(!Body_isActive(this->body))
	{
		return false;
	}

	bool movementState = Body_getMovementOnAllAxes(this->body);

	if((__X_AXIS & axis) && !(__Y_AXIS & movementState))
	{
		AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Idle");
	}

	// if there is something below
	if(0 > Body_getNormal(this->body).y)
	{
		if(__Y_AXIS & axis)
		{
			MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kHeroCheckVelocity);

			Hero_lockCameraTriggerMovement(this, __Y_AXIS, true);

			this->jumps = 0;

			if(Body_getVelocity(this->body).x)
			{
				if(this->inputDirection.x)
				{
					AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Walk");
				}
				else
				{
					Hero_slide(this);
				}
			}
		}

		if(__Z_AXIS & axis)
		{
			this->keepAddingForce = false;
			this->jumps = 0;
			StateMachine_swapState(this->stateMachine, __SAFE_CAST(State, HeroIdle_getInstance()));
			return true;
		}

		if(!movementState && __SAFE_CAST(State, HeroIdle_getInstance()) != StateMachine_getCurrentState(this->stateMachine))
		{
			this->keepAddingForce = false;
			this->jumps = 0;
			StateMachine_swapState(this->stateMachine, __SAFE_CAST(State, HeroIdle_getInstance()));
			return true;
		}
		else
		{
			AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Walk");
		}
	}
	else
	{
		AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Fall");
	}

	return false;
}

// check direction
void Hero_checkDirection(Hero this, u32 pressedKey, char* animation)
{
	ASSERT(this, "Hero::checkDirection: null this");

	bool movementState = Body_getMovementOnAllAxes(this->body);
	Direction direction = Entity_getDirection(__SAFE_CAST(Entity, this));

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

	if(direction.x != this->inputDirection.x)
	{
		Hero_lockCameraTriggerMovement(this, __X_AXIS, true);
	}

	if(animation && !(__Y_AXIS & movementState))
	{
		AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), animation);
	}
}

void Hero_lockCameraTriggerMovement(Hero this, u8 axisToLockUp, bool locked)
{
	if(this->cameraBoundingBox)
	{
		Vector3DFlag overridePositionFlag = CameraTriggerEntity_getOverridePositionFlag(__SAFE_CAST(CameraTriggerEntity, this->cameraBoundingBox));

		Vector3DFlag positionFlag = CustomCameraMovementManager_getPositionFlag(CustomCameraMovementManager_getInstance());

		if(__X_AXIS & axisToLockUp)
		{
			overridePositionFlag.x = locked;

			positionFlag.x = !locked;
		}

		if(__Y_AXIS & axisToLockUp)
		{
			overridePositionFlag.y = locked;
		}

		CameraTriggerEntity_setOverridePositionFlag(__SAFE_CAST(CameraTriggerEntity, this->cameraBoundingBox), overridePositionFlag);
		CustomCameraMovementManager_setPositionFlag(CustomCameraMovementManager_getInstance(), positionFlag);
	}
}

void Hero_takeHitFrom(Hero this, SpatialObject collidingObject, int energyToReduce, bool pause, bool invincibleWins)
{
#ifdef GOD_MODE
	return;
#endif

	if(!Hero_isInvincible(this) || !invincibleWins)
	{
		if(invincibleWins && ((this->energy - energyToReduce >= 0) || (this->powerUp != kPowerUpNone)))
		{
			Hero_setInvincible(this, true);

			// reset invincible a bit later
			MessageDispatcher_dispatchMessage(HERO_FLASH_DURATION, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroStopInvincibility, NULL);

			// start flashing of hero
			MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kHeroFlash);
			MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroFlash, NULL);

			// lose power-up or reduce energy
			if(this->powerUp != kPowerUpNone)
			{
				Hero_losePowerUp(this);
			}
			else
			{
				this->energy -= energyToReduce;
			}

			if(pause)
			{
				Actor_stopAllMovement(__SAFE_CAST(Actor, this));
				Game_disableKeypad(Game_getInstance());
				GameState_pausePhysics(Game_getCurrentState(Game_getInstance()), true);
				//GameState_pauseAnimations(Game_getCurrentState(Game_getInstance()), true);
				MessageDispatcher_dispatchMessage(500, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroResumePhysics, collidingObject);
			}
		}
		else
		{
			Game_disableKeypad(Game_getInstance());
			Hero_setInvincible(this, true);
			this->energy = 0;
			Hero_flash(this);
			AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Dead");
			GameState_pausePhysics(Game_getCurrentState(Game_getInstance()), true);
			GameState_pauseAnimations(Game_getCurrentState(Game_getInstance()), true);
			Entity_activateShapes(__SAFE_CAST(Entity, this), false);
			MessageDispatcher_dispatchMessage(500, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroDied, NULL);
		}

		// start short screen shake
		Camera_startEffect(Camera_getInstance(), kShake, 200);

		// play hit sound
		SoundManager_playFxSound(SoundManager_getInstance(), FIRE_SND, this->transformation.globalPosition);

		// play animation
		AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Hit");

		// inform others to update ui etc
		Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), kEventHitTaken);
	}
}

// flash after being hit
void Hero_flash(Hero this)
{
	ASSERT(this, "Hero::flash: null this");

	// only flash as long as hero is invincible
	if(Hero_isInvincible(this))
	{
		// toggle between original and flash palette
		Hero_toggleFlashPalette(this);

		// next flash state change after HERO_FLASH_INTERVAL milliseconds
		MessageDispatcher_dispatchMessage(HERO_FLASH_INTERVAL, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroFlash, NULL);
	}
	else
	{
		// set palette back to original
		Hero_resetPalette(this);
	}
}

void Hero_toggleFlashPalette(Hero this)
{
	// get all of the hero's sprites and loop through them
	VirtualList sprites = Entity_getSprites(__SAFE_CAST(Entity, this));
	VirtualNode node = VirtualList_begin(sprites);
	for(; node; node = VirtualNode_getNext(node))
	{
		// get sprite's texture
		Sprite sprite = __SAFE_CAST(Sprite, VirtualNode_getData(node));
		Texture texture = Sprite_getTexture(sprite);

		// get original palette
		TextureDefinition* textureDefinition = Texture_getDefinition(texture);

		// set new palette
		if(Texture_getPalette(texture) == textureDefinition->palette)
		{
			Texture_setPalette(texture, HERO_FLASH_PALETTE);
		}
		else
		{
			Texture_setPalette(texture, textureDefinition->palette);
		}

		// rewrite sprite to bgmap to apply changed palette
		Sprite_rewrite(sprite);
	}
}

void Hero_resetPalette(Hero this)
{
	// get all of hero's sprites and loop through them
	VirtualList sprites = Entity_getSprites(__SAFE_CAST(Entity, this));
	VirtualNode node = VirtualList_begin(sprites);
	for(; node; node = VirtualNode_getNext(node))
	{
		// get sprite's texture
		Sprite sprite = __SAFE_CAST(Sprite, VirtualNode_getData(node));
		Texture texture = Sprite_getTexture(sprite);

		// get original palette and set it
		TextureDefinition* textureDefinition = Texture_getDefinition(texture);
		Texture_setPalette(texture, textureDefinition->palette);

		// rewrite sprite to bgmap to apply changed palette
		Sprite_rewrite(sprite);
	}
}

// die hero
void Hero_die(Hero this)
{
	MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kHeroFlash);

	Container_deleteMyself(__SAFE_CAST(Container, this));

	/*
	// go to dead state
	StateMachine_swapState(this->stateMachine, __SAFE_CAST(State, HeroDead_getInstance()));

	// must unregister the shape for collision detections
	Entity_activateShapes(__SAFE_CAST(Entity, this), false);

	// change in game state
	this->inGameState = kDead;
	*/
}

// process user input
static void Hero_onUserInput(Hero this, Object eventFirer __attribute__ ((unused)))
{
	UserInput userInput = PlatformerLevelState_getUserInput(PlatformerLevelState_getInstance());

	HeroState currentState = __SAFE_CAST(HeroState, StateMachine_getCurrentState(this->stateMachine));

	if(userInput.pressedKey)
	{
		__VIRTUAL_CALL(HeroState, onKeyPressed, currentState, this, &userInput);
	}

	if(userInput.releasedKey)
	{
		__VIRTUAL_CALL(HeroState, onKeyReleased, currentState, this, &userInput);
	}

	if(userInput.holdKey)
	{
		__VIRTUAL_CALL(HeroState, onKeyHold, currentState, this, &userInput);
	}
}

// does the hero have a key?
bool Hero_hasKey(Hero this)
{
	return this->hasKey;
}

// collect a power-up
void Hero_collectPowerUp(Hero this, u8 powerUp)
{
	this->powerUp = powerUp;
	this->keepAddingForce = false;

	Hero_updateSprite(this);

	Actor_stopAllMovement(__SAFE_CAST(Actor, this));
	Game_disableKeypad(Game_getInstance());
	GameState_pausePhysics(Game_getCurrentState(Game_getInstance()), true);

	//AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Transition");
}

// lose a power-up
void Hero_losePowerUp(Hero this)
{
	this->powerUp = kPowerUpNone;
	Hero_updateSprite(this);
	Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), kEventPowerUp);
}

// update sprite, e.g. after collecting a power-up
void Hero_updateSprite(Hero this)
{
	CharSet charSet = Texture_getCharSet(Sprite_getTexture(__SAFE_CAST(Sprite, VirtualList_front(this->sprites))), true);

	CharSetDefinition* charSetDefinition = NULL;

	switch(this->powerUp)
	{
		case kPowerUpBandana:

			//charSetDefinition = &HERO_BANDANA_CH;
			break;

		default:
		case kPowerUpNone:

			charSetDefinition = &HERO_CH;
			break;
	}

	CharSet_setCharSetDefinition(charSet, charSetDefinition);
	CharSet_rewrite(charSet);
}

// get current power-up
u8 Hero_getPowerUp(Hero this)
{
	return this->powerUp;
}

// get energy
u8 Hero_getEnergy(Hero this)
{
	return this->energy;
}

// set invincibility
void Hero_setInvincible(Hero this, bool invincible)
{
	this->invincible = invincible;
}

// get invincibility
bool Hero_isInvincible(Hero this)
{
	return this->invincible;
}

fix10_6 Hero_getFrictionOnCollision(Hero this, SpatialObject collidingObject, const Vector3D* collidingObjectNormal)
{
	// ignore friction on y axis
	if(collidingObjectNormal->x && !collidingObjectNormal->y)
	{
		return 0;
	}

	return Actor_getFrictionOnCollision(__SAFE_CAST(Actor, this), collidingObject, collidingObjectNormal);
}

// process collisions
bool Hero_enterCollision(Hero this, const CollisionInformation* collisionInformation)
{
	ASSERT(this, "Hero::enterCollision: null this");
	ASSERT(collisionInformation->collidingShape, "Hero::enterCollision: null collidingObjects");

	Shape collidingShape = collisionInformation->collidingShape;
	SpatialObject collidingObject = Shape_getOwner(collidingShape);

	switch(__VIRTUAL_CALL(SpatialObject, getInGameType, collidingObject))
	{
		// speed things up by breaking early
		case kShape:
			break;

		case kCameraTarget:
			{
				if(collisionInformation->solutionVector.direction.y)
				{
					Hero_lockCameraTriggerMovement(this, __Y_AXIS, false);
				}

				if(collisionInformation->solutionVector.direction.x)
				{
					Hero_lockCameraTriggerMovement(this, __X_AXIS, false);
				}
				else
				{
					Hero_lockCameraTriggerMovement(this, __Y_AXIS, false);
				}

				Vector3D position = CAMERA_BOUNDING_BOX_DISPLACEMENT;

				__VIRTUAL_CALL(Container, setLocalPosition, this->cameraBoundingBox, &position);
			}
			return false;
			break;

		case kHit:

			Hero_takeHitFrom(this, collidingObject, 1, true, true);
			return false;
			break;

		case kMovingPlatform:
		case kTopShape:
			{
				if((0 > Body_getVelocity(this->body).y) || Hero_isBelow(this, collisionInformation->shape, collisionInformation))
				{
					// don't further process collision
					return false;
				}
			}
			break;
	}

	return Actor_enterCollision(__SAFE_CAST(Actor, this), collisionInformation) && (__ABS(collisionInformation->solutionVector.direction.y) > __ABS(collisionInformation->solutionVector.direction.x));
}

// process collisions
bool Hero_updateCollision(Hero this, const CollisionInformation* collisionInformation)
{
	ASSERT(this, "Hero::enterCollision: null this");
	ASSERT(collisionInformation->collidingShape, "Hero::enterCollision: null collidingObjects");

	Shape collidingShape = collisionInformation->collidingShape;
	SpatialObject collidingObject = Shape_getOwner(collidingShape);

	switch(__VIRTUAL_CALL(SpatialObject, getInGameType, collidingObject))
	{
		case kHit:

			Hero_takeHitFrom(this, collidingObject, 1, true, true);
			return false;
			break;
	}

	return false;
}

void Hero_capVelocity(Hero this, bool discardPreviousMessages)
{
	ASSERT(this, "Hero::checkCapVelocity: null this");

	if(discardPreviousMessages)
	{
		MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kHeroCheckVelocity);
	}

	if(Body_isActive(this->body))
	{
		Velocity velocity = Body_getVelocity(this->body);

		if(velocity.y)
		{
			if(HERO_MAX_VELOCITY_Y < velocity.y && __UNIFORM_MOVEMENT != Body_getMovementType(this->body).y)
			{
				velocity.x = 0;
				velocity.y = HERO_MAX_VELOCITY_Y;
				velocity.z = 0;

				//Body_moveUniformly(this->body, velocity);
			}
			else if(0 < velocity.y)
			{
				MessageDispatcher_dispatchMessage(HERO_CHECK_Y_VELOCITY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroCheckVelocity, NULL);
			}
		}
		else
		{
			MessageDispatcher_dispatchMessage(1, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroCheckVelocity, NULL);
		}
	}
}

bool Hero_handleMessage(Hero this, Telegram telegram)
{
	ASSERT(this, "Hero::handleMessage: null this");

	// handle messages that any state would handle here
	switch(Telegram_getMessage(telegram))
	{
		case kHeroCheckVelocity:

			Hero_capVelocity(this, false);
			return true;
			break;

		case kHeroStopInvincibility:

			Hero_setInvincible(this, false);
			return true;
			break;

		case kHeroFlash:

			Hero_flash(this);
			return true;
			break;

		case kHeroResumePhysics:

			Game_enableKeypad(Game_getInstance());
			GameState_pausePhysics(Game_getCurrentState(Game_getInstance()), false);
			GameState_pauseAnimations(Game_getCurrentState(Game_getInstance()), false);

			Velocity velocity = Body_getVelocity(this->body);

			if(!velocity.y)
			{
				if(velocity.x)
				{
					AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Walk");
				}
				else
				{
					AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Idle");
				}
			}
			else if(velocity.x)
			{
				AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Walk");
			}
			else
			{
				AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Idle");
			}

			break;

		case kHeroDied:

			Hero_die(this);
			break;

		case kBodyStopped:

			if(-1 == this->jumps)
			{
				return true;
			}
			break;
	}

	return Actor_handleMessage(__SAFE_CAST(Actor, this), telegram);
}

// process message
bool Hero_handlePropagatedMessage(Hero this, int message)
{
	ASSERT(this, "Hero::handlePropagatedMessage: null this");

	switch(message)
	{
		case kLevelSetUp:
			{
				// set camera
				Vector3D cameraBoundingBoxPosition = CAMERA_BOUNDING_BOX_DISPLACEMENT;
				this->cameraBoundingBox = Entity_addChildEntity(__SAFE_CAST(Entity, this), (EntityDefinition*)&CAMERA_BOUNDING_BOX_IG, 0, NULL, &cameraBoundingBoxPosition, NULL);
				Hero_lockCameraTriggerMovement(this, __X_AXIS | __Y_AXIS, true);
			}

			//Hero_locateOverNextFloor(this);

			break;

		case kLevelStarted:
			{
				Vector3DFlag positionFlag = {true, true, true};
				CustomCameraMovementManager_setPositionFlag(CustomCameraMovementManager_getInstance(), positionFlag);
			}
			break;

	}

	return false;
}

void Hero_suspend(Hero this)
{
	ASSERT(this, "Hero::suspend: null this");

	__CALL_BASE_METHOD(Actor, suspend, this);
}

void Hero_resume(Hero this)
{
	ASSERT(this, "Hero::resume: null this");

	__CALL_BASE_METHOD(Actor, resume, this);

	Camera_focus(Camera_getInstance(), false);

	Hero_lockCameraTriggerMovement(this, __X_AXIS | __Y_AXIS, true);

	Vector3DFlag positionFlag = {true, true, true};
	CustomCameraMovementManager_setPositionFlag(CustomCameraMovementManager_getInstance(), positionFlag);

	Hero_updateSprite(this);
}

bool Hero_isBelow(Hero this, Shape shape, const CollisionInformation* collisionInformation)
{
	ASSERT(this, "Hero::isAboveEntity: null this");

	RightBox shapeRightBox = __VIRTUAL_CALL(Shape, getSurroundingRightBox, shape);
	RightBox collidingShapeRightBox = __VIRTUAL_CALL(Shape, getSurroundingRightBox, collisionInformation->collidingShape);

	fix10_6 heroBottomPosition = shapeRightBox.y1 - ((shapeRightBox.y1 - shapeRightBox.y0) >> 1) - (Body_getLastDisplacement(this->body).y << 1) / 2;

	return heroBottomPosition > collidingShapeRightBox.y0 || __ABS(collisionInformation->solutionVector.direction.y) < __ABS(collisionInformation->solutionVector.direction.x);
}

u16 Hero_getAxisForFlipping(Hero this __attribute__ ((unused)))
{
	return __X_AXIS;
}

void Hero_onPowerUpTransitionComplete(Hero this, Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "Hero::onPowerUpTransitionComplete: null this");

	MessageDispatcher_dispatchMessage(300, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroResumePhysics, NULL);
}

bool Hero_isAffectedByRelativity(Hero this __attribute__ ((unused)))
{
	ASSERT(this, "Hero::isAffectedByRelativity: null this");

	return true;
}

void Hero_syncRotationWithBody(Hero this)
{
	ASSERT(this, "Hero::syncRotationWithBody: null this");

	fix10_6 xLastDisplacement = Body_getLastDisplacement(this->body).x;

	Direction direction = Entity_getDirection(__SAFE_CAST(Entity, this));

	if(0 < xLastDisplacement)
	{
		direction.x = __RIGHT;
		Entity_setDirection(__SAFE_CAST(Entity, this), direction);
	}
	else if(0 > xLastDisplacement)
	{
		direction.x = __LEFT;
		Entity_setDirection(__SAFE_CAST(Entity, this), direction);
	}
}

void Hero_exitCollision(Hero this, Shape shape, Shape shapeNotCollidingAnymore, bool isShapeImpenetrable)
{
	ASSERT(this, "Hero::exitCollision: null this");

	__CALL_BASE_METHOD(Actor, exitCollision, this, shape, shapeNotCollidingAnymore, isShapeImpenetrable);
}

u16 Hero_getAxesForShapeSyncWithDirection(Hero this __attribute__ ((unused)))
{
	return __NO_AXIS;
}
