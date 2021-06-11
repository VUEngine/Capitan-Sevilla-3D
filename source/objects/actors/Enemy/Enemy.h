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
