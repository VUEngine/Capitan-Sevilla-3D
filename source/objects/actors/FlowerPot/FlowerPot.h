/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef FLOWER_POT_H_
#define FLOWER_POT_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Projectile.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

class FlowerPot : Projectile
{
	void constructor(ProjectileSpec* projectileSpec, s16 internalId, const char* const name);
	override bool enterCollision(const CollisionInformation* collisionInformation);
}


#endif
