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

#ifndef HERO_H_
#define HERO_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Actor.h>
#include <ParticleSystem.h>
#include <ProgressManager.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

#define HERO_NAME							"Capitan"
#define HERO_INITIAL_ENERGY					3
#define HERO_INITIAL_SAUSAGES				12

#define HERO_MASS							1
#define HERO_ELASTICITY						0.0f
#define HERO_FRICTION						0

#define HERO_FLASH_PALETTE					3
#define HERO_FLASH_DURATION					2000
#define HERO_FLASH_INTERVAL					100

#define HERO_FORCE_FOR_STOPPING 			__F_TO_FIX10_6(-4.5f)
#define HERO_INPUT_FORCE 					__I_TO_FIX10_6(60)
#define HERO_X_INPUT_FORCE_WHILE_JUMPING	__I_TO_FIX10_6(10)

#define HERO_MAX_VELOCITY_X					__I_TO_FIX10_6(4)
#define HERO_MAX_VELOCITY_Y					__I_TO_FIX10_6(15)
#define HERO_MAX_VELOCITY_Z					__I_TO_FIX10_6(4)
#define HERO_NORMAL_JUMP_INPUT_FORCE		__I_TO_FIX10_6(-280)

#define HERO_CHECK_Y_VELOCITY				(20/16)


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Hero_METHODS(ClassName)																			\
		Actor_METHODS(ClassName)																		\

#define Hero_SET_VTABLE(ClassName)																		\
		Actor_SET_VTABLE(ClassName)																		\
		__VIRTUAL_SET(ClassName, Hero, ready);															\
		__VIRTUAL_SET(ClassName, Hero, takeHitFrom);													\
		__VIRTUAL_SET(ClassName, Hero, handlePropagatedMessage);										\
		__VIRTUAL_SET(ClassName, Hero, handleMessage);													\
		__VIRTUAL_SET(ClassName, Hero, suspend);														\
		__VIRTUAL_SET(ClassName, Hero, resume);															\
		__VIRTUAL_SET(ClassName, Hero, getAxisForFlipping);												\
		__VIRTUAL_SET(ClassName, Hero, isAffectedByRelativity);											\
		__VIRTUAL_SET(ClassName, Hero, getFrictionOnCollision);											\
		__VIRTUAL_SET(ClassName, Hero, enterCollision);													\
		__VIRTUAL_SET(ClassName, Hero, updateCollision);												\
		__VIRTUAL_SET(ClassName, Hero, syncRotationWithBody);											\
		__VIRTUAL_SET(ClassName, Hero, exitCollision);													\
		__VIRTUAL_SET(ClassName, Hero, getAxesForShapeSyncWithDirection);								\

__CLASS(Hero);

#define Hero_ATTRIBUTES																					\
		/* it is derived from */																		\
		Actor_ATTRIBUTES																				\
		/* sausage entity references for shooting */													\
		Entity sausageEjectorEntity;																	\
		/* used to know if gap must be changed */														\
		Direction inputDirection;																		\
		/* hero has energy	*/																			\
		u8 energy;																						\
		/* number of jumps performed (for double jump) */												\
		s8 jumps;																						\
		/* number of sausages */																		\
		u8 sausages;																					\
		/* flag for invincible mode (after being hit) */												\
		bool invincible;																				\
		/* flag to keep applying force to the x axis */													\
		bool keepAddingForce;																			\

typedef const ActorDefinition HeroDefinition;
typedef const HeroDefinition HeroROMDef;


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

Hero Hero_getInstance();

__CLASS_NEW_DECLARE(Hero, HeroDefinition* heroDefinition, s16 id, s16 internalId, const char* const name);

void Hero_constructor(Hero this, HeroDefinition* heroDefinition, s16 id, s16 internalId, const char* const name);
void Hero_destructor(Hero this);
void Hero_ready(Hero this, bool recursive);
void Hero_addForce(Hero this, u16 axis, bool enableAddingForce);
void Hero_stopAddingForce(Hero this);
void Hero_startedMovingOnAxis(Hero this, u16 axis);
bool Hero_stopMovementOnAxis(Hero this, u16 axis);
void Hero_kneel(Hero this);
void Hero_jump(Hero this, bool checkIfYMovement);
void Hero_addMomentumToJump(Hero this);
void Hero_checkDirection(Hero this, u32 currentPressedKey, char * animation);
void Hero_takeHitFrom(Hero this, SpatialObject collidingObject, int energyToReduce, bool pause, bool invincibleWins);
void Hero_flash(Hero this);
void Hero_toggleFlashPalette(Hero this);
void Hero_resetPalette(Hero this);
void Hero_die(Hero this);
u8 Hero_getEnergy(Hero this);
u8 Hero_getSausages(Hero this);
void Hero_setInvincible(Hero this, bool invincible);
bool Hero_isInvincible(Hero this);
fix10_6 Hero_getFrictionOnCollision(Hero this, SpatialObject collidingObject, const Vector3D* collidingObjectNormal);
bool Hero_enterCollision(Hero this, const CollisionInformation* collisionInformation);
bool Hero_updateCollision(Hero this, const CollisionInformation* collisionInformation);
bool Hero_handleMessage(Hero this, Telegram telegram);
bool Hero_handlePropagatedMessage(Hero this, int message);
void Hero_suspend(Hero this);
void Hero_resume(Hero this);
void Hero_lockCameraTriggerMovement(Hero this, u8 axisToLockUp, bool locked);
bool Hero_isBelow(Hero this, Shape shape, const CollisionInformation* collisionInformation);
u16 Hero_getAxisForFlipping(Hero this);
void Hero_capVelocity(Hero this, bool discardPreviousMessages);
bool Hero_isAffectedByRelativity(Hero this);
void Hero_syncRotationWithBody(Hero this);
void Hero_exitCollision(Hero this, Shape shape, Shape shapeNotCollidingAnymore, bool isShapeImpenetrable);
u16 Hero_getAxesForShapeSyncWithDirection(Hero this);
void Hero_shoot(Hero this);


#endif
