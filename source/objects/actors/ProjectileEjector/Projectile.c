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

// class's constructor
void Projectile::constructor(ProjectileDefinition* projectileDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor((ActorDefinition*)&projectileDefinition->actorDefinition, id, internalId, name);

	// save definition
	this->projectileDefinition = projectileDefinition;

	// init members
	this->maxGlobalPosition = (Vector3D){0, 0, 0};
}

// class's constructor
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
	// adjustments relative to direction
 	Direction direction = Entity::getDirection(Entity::safeCast(this->parent));
 	Entity::setDirection(Entity::safeCast(this), direction);
	Velocity velocity = this->projectileDefinition->velocity;
	velocity.x *= direction.x;
	velocity.y *= direction.y;
	velocity.z *= direction.z;
	Vector3D position = this->projectileDefinition->position;
	position.x *= direction.x;
	position.y *= direction.y;
	position.z *= direction.z;

	// set back to local position
	Actor::setLocalPosition(Actor::safeCast(this), &position);

	// compute max global position to check against later
	if(this->projectileDefinition->checkDelay > -1)
	{
		this->maxGlobalPosition.x = (this->projectileDefinition->maxPosition.x > 0)
			? this->transformation.globalPosition.x + (this->projectileDefinition->maxPosition.x * direction.x)
			: 0;
		this->maxGlobalPosition.y = (this->projectileDefinition->maxPosition.y > 0)
			? this->transformation.globalPosition.y + (this->projectileDefinition->maxPosition.y * direction.y)
			: 0;
		this->maxGlobalPosition.z = (this->projectileDefinition->maxPosition.z > 0)
			? this->transformation.globalPosition.z + (this->projectileDefinition->maxPosition.z * direction.z)
			: 0;
	}

	// activate shapes
	Entity::activateShapes(Entity::safeCast(this), true);

	// play default animation
	AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this), this->projectileDefinition->actorDefinition.animatedEntityDefinition.initialAnimation);

	// show me
	Entity::show(Entity::safeCast(this));

	// start moving
	/*
	if(this->projectileDefinition->movementType == __UNIFORM_MOVEMENT)
	{
	*/
		Actor::moveUniformly(Actor::safeCast(this), &velocity);
	/*
	}
	else
	{
		Actor::addForce(Actor::safeCast(this), &this->projectileDefinition->velocity);
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
	Actor::stopAllMovement(Actor::safeCast(this));

	// deactivate shapes
	Entity::activateShapes(Entity::safeCast(this), false);

	// hide me
	Entity::hide(Entity::safeCast(this));
}

void Projectile::checkPosition()
{
 	Direction direction = Entity::getDirection(Entity::safeCast(this));

	// TODO: check if conditions for y and z are correct
	if(	((this->maxGlobalPosition.x > 0) && (((direction.x == __RIGHT) && this->transformation.globalPosition.x > this->maxGlobalPosition.x) ||
											 ((direction.x == __LEFT)  && this->transformation.globalPosition.x < this->maxGlobalPosition.x))) ||
		((this->maxGlobalPosition.y > 0) && (((direction.y == __DOWN)  && this->transformation.globalPosition.y > this->maxGlobalPosition.y) ||
											 ((direction.y == __UP)    && this->transformation.globalPosition.y < this->maxGlobalPosition.y))) ||
		((this->maxGlobalPosition.z > 0) && (((direction.z == __FAR)   && this->transformation.globalPosition.z > this->maxGlobalPosition.z) ||
											 ((direction.z == __NEAR)  && this->transformation.globalPosition.z < this->maxGlobalPosition.z))))
	{
		Projectile::stopMovement(this);
	}
	else
	{
		MessageDispatcher::dispatchMessage(this->projectileDefinition->checkDelay, Object::safeCast(this), Object::safeCast(this), kProjectileCheckPosition, NULL);
	}
}

// state's handle message
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
	return !SpatialObject::isMoving(this);
}

// deactivate a projectile after "hit" animation completes
void Projectile::onHitAnimationComplete()
{
	Projectile::stopMovement(this);
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kProjectileCheckPosition);
}
