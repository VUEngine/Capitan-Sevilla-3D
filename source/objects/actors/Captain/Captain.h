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

#ifndef CAPTAIN_H_
#define CAPTAIN_H_


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

#define CAPTAIN_INITIAL_ENERGY					3
#define CAPTAIN_INITIAL_SAUSAGES				12

#define CAPTAIN_MASS							1
#define CAPTAIN_BOUNCINESS						0.0f
#define CAPTAIN_FRICTION						0

#define CAPTAIN_FLASH_PALETTE					3
#define CAPTAIN_FLASH_DURATION					2000
#define CAPTAIN_FLASH_INTERVAL					100

#define CAPTAIN_FORCE_FOR_STOPPING 			__F_TO_FIX10_6(-4.5f)
#define CAPTAIN_INPUT_FORCE 					__I_TO_FIX10_6(60)
#define CAPTAIN_X_INPUT_FORCE_WHILE_JUMPING	__I_TO_FIX10_6(10)

#define CAPTAIN_MAX_VELOCITY_X					__I_TO_FIX10_6(4)
#define CAPTAIN_MAX_VELOCITY_Y					__I_TO_FIX10_6(15)
#define CAPTAIN_MAX_VELOCITY_Z					__I_TO_FIX10_6(4)
#define CAPTAIN_NORMAL_JUMP_INPUT_FORCE		__I_TO_FIX10_6(-280)

#define CAPTAIN_CHECK_Y_VELOCITY				(20/16)

#define CAPTAIN_HEAD_X_OFFSET					4
#define CAPTAIN_HEAD_Y_OFFSET					-7


//---------------------------------------------------------------------------------------------------------
//											TYPE DEFINITIONS
//---------------------------------------------------------------------------------------------------------

typedef const ActorSpec CaptainSpec;
typedef const CaptainSpec CaptainROMSpec;


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

class Captain : Actor
{
	// projectile ejector entity references for shooting
	Entity headEntity;
	// jump dust entity reference
	Entity jumpDustEntity;
	// land dust entity reference
	Entity landDustEntity;
	// used to know if gap must be changed
	Direction inputDirection;
	// captain has energy
	s8 energy;
	// number of jumps performed (for double jump)
	s8 jumps;
	// number of sausages
	u8 sausages;
	// flag for invincible mode (after being hit)
	bool invincible;
	// flag to keep applying force to the x axis
	bool keepAddingForce;

	static Captain getInstance();
	void constructor(CaptainSpec* captainSpec, s16 id, s16 internalId, const char* const name);
	void addForce(u16 axis, bool enableAddingForce);
	void stopAddingForce();
	void startedMovingOnAxis(u16 axis);
	bool stopMovementOnAxis(u16 axis);
	void kneel();
	void standUp();
	void jump(bool checkIfYMovement);
	void addMomentumToJump();
	void checkDirection(u32 currentPressedKey, char * animation);
	void takeHitFrom(int energyToReduce);
	void die();
	s8 getEnergy();
	u8 getSausages();
	void setInvincible(bool invincible);
	bool isInvincible();
	void lockCameraTriggerMovement(u8 axisToLockUp, bool locked);
	bool isBelow(Shape shape, const CollisionInformation* collisionInformation);
	void capVelocity(bool discardPreviousMessages);
	void startShooting();
	void stopShooting();
	void toggleShapes(bool kneeling);
	override void ready(bool recursive);
	override bool handlePropagatedMessage(int message);
	override bool handleMessage(Telegram telegram);
	override void suspend();
	override void resume();
	override bool isAffectedByRelativity();
	override fix10_6 getFrictionOnCollision(SpatialObject collidingObject, const Vector3D* collidingObjectNormal);
	override bool enterCollision(const CollisionInformation* collisionInformation);
	override void exitCollision(Shape shape, Shape shapeNotCollidingAnymore, bool isShapeImpenetrable);
	override bool updateCollision(const CollisionInformation* collisionInformation);
	override void syncRotationWithBody();
	override u16 getAxesForShapeSyncWithDirection();
	override void setDirection(Direction direction);
	override void update(u32 elapsedTime);
	void onHitAnimationComplete(Object eventFirer);
}


#endif
