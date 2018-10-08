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
#define HERO_BOUNCINESS						0.0f
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

typedef const ActorDefinition HeroDefinition;
typedef const HeroDefinition HeroROMDef;


class Hero : Actor
{
	/* sausage entity references for shooting */
	Entity sausageEjectorEntity;
	/* used to know if gap must be changed */
	Direction inputDirection;
	/* hero has energy	*/
	u8 energy;
	/* number of jumps performed (for double jump) */
	s8 jumps;
	/* number of sausages */
	u8 sausages;
	/* flag for invincible mode (after being hit) */
	bool invincible;
	/* flag to keep applying force to the x axis */
	bool keepAddingForce;

	static Hero getInstance();
	void constructor(HeroDefinition* heroDefinition, s16 id, s16 internalId, const char* const name);
	void addForce(u16 axis, bool enableAddingForce);
	void stopAddingForce();
	void startedMovingOnAxis(u16 axis);
	bool stopMovementOnAxis(u16 axis);
	void kneel();
	void jump(bool checkIfYMovement);
	void addMomentumToJump();
	void checkDirection(u32 currentPressedKey, char * animation);
	void takeHitFrom(SpatialObject collidingObject, int energyToReduce, bool pause, bool invincibleWins);
	void flash();
	void toggleFlashPalette();
	void resetPalette();
	void die();
	u8 getEnergy();
	u8 getSausages();
	void setInvincible(bool invincible);
	bool isInvincible();
	void lockCameraTriggerMovement(u8 axisToLockUp, bool locked);
	bool isBelow(Shape shape, const CollisionInformation* collisionInformation);
	void capVelocity(bool discardPreviousMessages);
	void shoot(bool active);
	override void ready(bool recursive);
	override bool handlePropagatedMessage(int message);
	override bool handleMessage(Telegram telegram);
	override void suspend();
	override void resume();
	override bool isAffectedByRelativity();
	override fix10_6 getFrictionOnCollision(SpatialObject collidingObject, const Vector3D* collidingObjectNormal);
	override bool enterCollision(const CollisionInformation* collisionInformation);
	override bool updateCollision(const CollisionInformation* collisionInformation);
	override void syncRotationWithBody();
	override void exitCollision(Shape shape, Shape shapeNotCollidingAnymore, bool isShapeImpenetrable);
	override u16 getAxesForShapeSyncWithDirection();
}


#endif
