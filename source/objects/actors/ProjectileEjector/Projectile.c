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

void Projectile::constructor(ProjectileDefinition* projectileDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor((ActorDefinition*)&projectileDefinition->actorDefinition, id, internalId, name);

	// save definition
	this->projectileDefinition = projectileDefinition;

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

	Projectile::stopMovement(this);
}

// start moving
void Projectile::startMovement()
{
	// adjustments relative to ejector direction
 	Direction direction = Entity::getDirection(Entity::safeCast(this->parent));
	Velocity velocity = this->projectileDefinition->velocity;
	velocity.x *= direction.x;
	velocity.y *= direction.y;
	velocity.z *= direction.z;
	Vector3D position = this->projectileDefinition->position;
	position.x *= direction.x;
	position.y *= direction.y;
	position.z *= direction.z;

	// set back to local position
	Actor::setLocalPosition(this, &position);

	// save current global position to check distance later
	this->originalPosition = this->transformation.globalPosition;

	// activate shapes
	Entity::activateShapes(this, true);

	// play default animation
	AnimatedEntity::playAnimation(this, this->projectileDefinition->actorDefinition.animatedEntityDefinition.initialAnimation);

	// show me
	Entity::show(this);

	// start moving
	/*
	if(this->projectileDefinition->movementType == __UNIFORM_MOVEMENT)
	{
	*/
		Actor::moveUniformly(this, &velocity);
	/*
	}
	else
	{
		Actor::addForce(this, &this->projectileDefinition->velocity);
	}
	*/

	// send first message of periodic position check
	if(this->projectileDefinition->checkDelay > -1)
	{
		MessageDispatcher::dispatchMessage(this->projectileDefinition->checkDelay, Object::safeCast(this), Object::safeCast(this), kProjectileCheckPosition, NULL);
	}
}

void Projectile::stopMovement()
{
	// stop movement
	Actor::stopAllMovement(this);

	// deactivate shapes
	Entity::activateShapes(this, false);

	// hide me
	Entity::hide(this);
}

void Projectile::checkPosition()
{
	if( (this->projectileDefinition->maxDistance.x != 0 && __ABS(this->originalPosition.x - this->transformation.globalPosition.x) > this->projectileDefinition->maxDistance.x) ||
		(this->projectileDefinition->maxDistance.y != 0 && __ABS(this->originalPosition.y - this->transformation.globalPosition.y) > this->projectileDefinition->maxDistance.y) ||
		(this->projectileDefinition->maxDistance.z != 0 && __ABS(this->originalPosition.z - this->transformation.globalPosition.z) > this->projectileDefinition->maxDistance.z) )
	{
		Projectile::stopMovement(this);
	}
	else
	{
		MessageDispatcher::dispatchMessage(this->projectileDefinition->checkDelay, Object::safeCast(this), Object::safeCast(this), kProjectileCheckPosition, NULL);
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
	Projectile::stopMovement(this);
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kProjectileCheckPosition);
}

bool Projectile::isVisible(int pad __attribute__ ((unused)), bool recursive __attribute__ ((unused)))
{
	// always return true so the Projectile is never streamed out
	return true;
}

// process collisions
bool Projectile::enterCollision(const CollisionInformation* collisionInformation __attribute__ ((unused)))
{
	// don't further process collision
	return false;
}
