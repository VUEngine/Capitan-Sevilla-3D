/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Game.h>
#include <CollisionManager.h>
#include <Optics.h>
#include <PlatformerLevelState.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include "FlowerPot.h"


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void FlowerPot::constructor(ProjectileSpec* projectileSpec, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(projectileSpec, internalId, name);
}

void FlowerPot::destructor()
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// process collisions
bool FlowerPot::enterCollision(const CollisionInformation* collisionInformation)
{
	Shape collidingShape = collisionInformation->collidingShape;
	SpatialObject collidingObject = Shape::getOwner(collidingShape);

	switch(SpatialObject::getInGameType(collidingObject))
	{
		case kFloor:
		{
			FlowerPot::stop(this, false);

			// play breaking animation
			AnimatedEntity::playAnimation(this, "Break");

			return false;
			break;
		}
	}

	return false;
}
