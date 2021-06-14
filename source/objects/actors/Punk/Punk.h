/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef PUNK_H_
#define PUNK_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Enemy.h>
#include <ProjectileEjector.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

class Punk : Enemy
{
	void constructor(EnemySpec* enemySpec, s16 internalId, const char* const name);
	void onDieAnimationComplete(Object eventFirer);
	override bool handleMessage(Telegram telegram);
	override bool enterCollision(const CollisionInformation* collisionInformation);
	override void die();
}


#endif
