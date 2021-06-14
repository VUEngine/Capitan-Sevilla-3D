/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
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
#define CAPTAIN_MAX_GUMS						4

#define CAPTAIN_MASS							1
#define CAPTAIN_BOUNCINESS						0.0f
#define CAPTAIN_FRICTION						0

#define CAPTAIN_FLASH_PALETTE					3
#define CAPTAIN_FLASH_DURATION					2000
#define CAPTAIN_FLASH_INTERVAL					100

#define CAPTAIN_FORCE_FOR_STOPPING 				__F_TO_FIX10_6(-4.5f)
#define CAPTAIN_INPUT_FORCE 					__I_TO_FIX10_6(60)
#define CAPTAIN_X_INPUT_FORCE_WHILE_JUMPING 	__I_TO_FIX10_6(10)

#define CAPTAIN_MAX_VELOCITY_X					__F_TO_FIX10_6(3.0f)
#define CAPTAIN_MAX_VELOCITY_Y					__I_TO_FIX10_6(15)
#define CAPTAIN_MAX_VELOCITY_Z					__I_TO_FIX10_6(4)
#define CAPTAIN_NORMAL_JUMP_INPUT_FORCE			__I_TO_FIX10_6(-280)

#define CAPTAIN_CHECK_Y_VELOCITY				(20/16)

#define CAPTAIN_HEAD_X_OFFSET					4
#define CAPTAIN_HEAD_Y_OFFSET					-3


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
	// number of gums
	u8 gums;
	// number of ducks
	u8 ducks;
	// flag for invincible mode (after being hit)
	bool invincible;
	// flag to keep applying force to the x axis
	bool keepAddingForce;

	static Captain getInstance();
	void constructor(CaptainSpec* captainSpec, s16 internalId, const char* const name);
	void applyForce(u16 axis, bool enableAddingForce);
	void stopAddingForce();
	void startedMovingOnAxis(u16 axis);
	bool stopMovementOnAxis(u16 axis);
	void kneel();
	void standUp();
	bool isJumping();
	void jump(bool checkIfYMovement);
	void addMomentumToJump();
	void checkDirection(u32 currentPressedKey, char * animation);
	void takeDamageFrom(int energyToReduce);
	void die();
	s8 getEnergy();
	u8 getGums();
	u8 getDucks();
	void setInvincible(bool invincible);
	bool isInvincible();
	void lockCameraTriggerMovement(u8 axisToLockUp, bool locked);
	bool isBelow(Shape shape, const CollisionInformation* collisionInformation);
	void capVelocity(bool discardPreviousMessages);
	void startShooting();
	void stopShooting();
	void toggleShapes(bool kneeling);
	void resetPalette();
	void startFlashing();
	void stopFlashing();
	override void ready(bool recursive);
	override bool handlePropagatedMessage(int message);
	override bool handleMessage(Telegram telegram);
	override void suspend();
	override void resume();
	override fix10_6 getFrictionOnCollision(SpatialObject collidingObject, const Vector3D* collidingObjectNormal);
	override bool enterCollision(const CollisionInformation* collisionInformation);
	override void exitCollision(Shape shape, Shape shapeNotCollidingAnymore, bool isShapeImpenetrable);
	override bool updateCollision(const CollisionInformation* collisionInformation);
	override void syncRotationWithBody();
	override u16 getAxisForShapeSyncWithDirection();
	override void setDirection(Direction direction);
	override void update(u32 elapsedTime);
	void reload();
	void onHitAnimationComplete(Object eventFirer);
	void onReloadAnimationComplete(Object eventFirer);
}


#endif
