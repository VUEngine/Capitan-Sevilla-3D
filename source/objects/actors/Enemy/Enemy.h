/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef ENEMY_H_
#define ENEMY_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <MovingOneWayEntity.h>
#include <ProjectileEjector.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

#define ENEMY_FLASH_PALETTE						3
#define ENEMY_FLASH_DURATION					2000
#define ENEMY_FLASH_INTERVAL					100


//---------------------------------------------------------------------------------------------------------
//											TYPE DEFINITIONS
//---------------------------------------------------------------------------------------------------------

typedef struct EnemySpec
{
	/// MovingOneWayEntity Spec
	MovingOneWayEntitySpec movingOneWayEntitySpec;

	/// energy
	u8 energy;

	/// projectile ejector to add
	ProjectileEjectorSpec* projectileEjectorSpec;

	/// relative position of projectile ejector
	Vector3D projectileEjectorPosition;

	// respawn
	bool respawn;

} EnemySpec;

typedef const EnemySpec EnemyROMSpec;


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

class Enemy : MovingOneWayEntity
{
	// spec pointer
	EnemySpec* enemySpec;
	// projectile ejector entity reference
	Entity projectileEjectorEntity;
	// energy
	u8 energy;

	void constructor(EnemySpec* enemySpec, s16 internalId, const char* const name);
	override void ready(bool recursive);
	override bool handleMessage(Telegram telegram);
	void takeHit(u8 power);
	virtual void onProjectileEjected(Object eventFirer);
	void startFlashing();
	void stopFlashing();
	void onEjectAnimationComplete();
	virtual void die();
	override bool respawn();
}


#endif
