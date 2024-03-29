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
#include "Projectile.h"


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void Projectile::constructor(ProjectileSpec* projectileSpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor((ActorSpec*)&projectileSpec->actorSpec, internalId, name);

	this->update = false;

	this->dontStreamOut = true;

	// save spec
	this->projectileSpec = projectileSpec;

	// init members
	this->originalPosition = (Vector3D){0, 0, 0};
}

void Projectile::destructor()
{
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kProjectileCheckPosition);

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void Projectile::ready(bool recursive)
{
	// call base
	Base::ready(this, recursive);

	Projectile::stop(this, true);
}

// start moving
void Projectile::startMovement()
{
	this->update = true;

	// adjustments relative to ejector direction
 	Direction direction = Entity::getDirection(Entity::safeCast(this->parent));
	Velocity velocity = this->projectileSpec->velocity;
	velocity.x *= direction.x;
	velocity.y *= direction.y;
	velocity.z *= direction.z;
	Vector3D position = this->projectileSpec->position;
	position.x *= direction.x;
	position.y *= direction.y;
	position.z *= direction.z;

	// set back to local position
	Actor::setLocalPosition(this, &position);

	// save current global position to check distance later
	this->originalPosition = this->transformation.globalPosition;

	// activate shapes
	Entity::activeCollisionChecks(this, true);

	// play default animation
	AnimatedEntity::playAnimation(this, this->projectileSpec->actorSpec.animatedEntitySpec.initialAnimation);

	// show me
	Entity::show(this);

	// start moving
	/*
	if(this->projectileSpec->movementType == __UNIFORM_MOVEMENT)
	{
	*/
		Actor::moveUniformly(this, &velocity);
	/*
	}
	else
	{
		Actor::applyForce(this, &this->projectileSpec->velocity, true);
	}
	*/

	// send first message of periodic position check
	if(this->projectileSpec->checkDelay > -1)
	{
		MessageDispatcher::dispatchMessage(this->projectileSpec->checkDelay, Object::safeCast(this), Object::safeCast(this), kProjectileCheckPosition, NULL);
	}
}

void Projectile::stop(bool hide)
{
	this->update = false;

	// stop movement
	Actor::stopAllMovement(this);

	// deactivate shapes
	Entity::allowCollisions(this, false);

	// hide me
	if(hide)
	{
		Entity::hide(this);
	}

	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kProjectileCheckPosition);
}

void Projectile::checkPosition()
{
	if( (this->projectileSpec->maxDistance.x != 0 && __ABS(this->originalPosition.x - this->transformation.globalPosition.x) > this->projectileSpec->maxDistance.x) ||
		(this->projectileSpec->maxDistance.y != 0 && __ABS(this->originalPosition.y - this->transformation.globalPosition.y) > this->projectileSpec->maxDistance.y) ||
		(this->projectileSpec->maxDistance.z != 0 && __ABS(this->originalPosition.z - this->transformation.globalPosition.z) > this->projectileSpec->maxDistance.z) )
	{
		Projectile::stop(this, true);
	}
	else
	{
		MessageDispatcher::dispatchMessage(this->projectileSpec->checkDelay, Object::safeCast(this), Object::safeCast(this), kProjectileCheckPosition, NULL);
	}
}

bool Projectile::handleMessage(Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kProjectileCheckPosition:

			Projectile::checkPosition(this);
			break;
	}

	return false;
}

bool Projectile::canBeReused()
{
	return !Actor::isMoving(this);
}

// deactivate a projectile after "hit" animation completes
void Projectile::onHitAnimationComplete()
{
	Projectile::stop(this, true);
}

// process collisions
bool Projectile::enterCollision(const CollisionInformation* collisionInformation __attribute__ ((unused)))
{
	// don't further process collision
	return false;
}
