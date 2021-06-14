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
#include <Enemy.h>
#include "GumProjectile.h"


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void GumProjectile::constructor(ProjectileSpec* projectileSpec, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(projectileSpec, internalId, name);
}

void GumProjectile::destructor()
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// process collisions
bool GumProjectile::enterCollision(const CollisionInformation* collisionInformation)
{
	Shape collidingShape = collisionInformation->collidingShape;
	SpatialObject collidingObject = Shape::getOwner(collidingShape);

	switch(SpatialObject::getInGameType(collidingObject))
	{
		case kEnemy:
		{
			// stop movement
			Actor::stopAllMovement(this);

			// deactivate shapes
			Entity::activeCollisionChecks(this, false);

			// set direction to right, so that the text is never mirrored
			Direction direction = {__RIGHT, __DOWN, __FAR};
			Actor::setDirection(this, direction);

			// play hitting animation
			AnimatedEntity::playAnimation(this, "Hit");

			// deactivate position checks
			MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kProjectileCheckPosition);

			// inform enemy
			Enemy::takeHit(Enemy::safeCast(collidingObject), 1);

			return false;
			break;
		}
	}

	// don't further process collision
	return false;
}
