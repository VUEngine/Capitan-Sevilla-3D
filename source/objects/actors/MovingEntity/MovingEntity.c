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
#include <MessageDispatcher.h>
#include <CollisionManager.h>
#include <Optics.h>
#include <PhysicalWorld.h>
#include <MessageDispatcher.h>
#include <PlatformerLevelState.h>
#include <debugUtilities.h>


#include "MovingEntity.h"


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void MovingEntity::constructor(MovingEntityDefinition* movingEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor((ActorDefinition*)&movingEntityDefinition->actorDefinition, id, internalId, name);

	this->movingEntityDefinition = movingEntityDefinition;

	this->initialPosition = 0;

	Direction direction =
	{
		__RIGHT, __DOWN, __FAR
	};

	switch(this->movingEntityDefinition->axis)
	{
		case __X_AXIS:

			direction.x = this->movingEntityDefinition->direction;
			break;

		case __Y_AXIS:

			direction.y = this->movingEntityDefinition->direction;
			break;
	}

	Entity::setDirection(Entity::safeCast(this), direction);
}

// class's constructor
void MovingEntity::destructor()
{
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kMovingEntityStartMovement);
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kMovingEntityCheckDirection);

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// set definition
void MovingEntity::setDefinition(void* movingEntityDefinition)
{
	// save definition
	this->movingEntityDefinition = movingEntityDefinition;

	Base::setDefinition(this, &((MovingEntityDefinition*)movingEntityDefinition)->actorDefinition);
}

// ready method
void MovingEntity::ready(bool recursive)
{
	// call base
	Base::ready(this, recursive);

	// save initial position
	switch(this->movingEntityDefinition->axis)
	{
		case __X_AXIS:

			this->initialPosition = this->transformation.globalPosition.x;
			break;

		case __Y_AXIS:

			this->initialPosition = this->transformation.globalPosition.y;
			break;
	}

	MovingEntity::startMovement(this);
}

bool MovingEntity::handleMessage(Telegram telegram)
{
	Direction direction = Entity::getDirection(Entity::safeCast(this));

	switch(Telegram::getMessage(telegram))
	{
		case kMovingEntityCheckDirection:

			if(Body::isAwake(this->body))
			{
				MovingEntity::checkDisplacement(this);
			}
			break;

		case kMovingEntityStartMovement:
			{
				Vector3D position = this->transformation.globalPosition;

				switch(this->movingEntityDefinition->axis)
				{
					case __X_AXIS:
						position.x = this->initialPosition + this->movingEntityDefinition->maximumDisplacement * direction.x;
						break;

					case __Y_AXIS:
						position.y = this->initialPosition + this->movingEntityDefinition->maximumDisplacement * direction.y;
						break;
				}

				Actor::setPosition(Actor::safeCast(this), &position);
			}

			MovingEntity::startMovement(this);
			return true;
			break;
	}

	return false;
}

// tell me I've been hit
void MovingEntity::takeHit(u16 axis __attribute__ ((unused)), s8 direction __attribute__ ((unused)))
{
}

void MovingEntity::checkDisplacement()
{
	// update position
	switch(this->movingEntityDefinition->axis)
	{
		case __X_AXIS:
			{
				fix10_6 distance = __ABS((this->transformation.globalPosition.x - this->initialPosition));

				if(distance > this->movingEntityDefinition->maximumDisplacement)
				{
					// make sure that I don't get stuck moving back and forth
					Body::stopMovement(this->body, (__X_AXIS | __Y_AXIS | __Z_AXIS));

					MessageDispatcher::dispatchMessage(this->movingEntityDefinition->idleDuration, Object::safeCast(this), Object::safeCast(this), kMovingEntityStartMovement, NULL);
				}
				else
				{
					MessageDispatcher::dispatchMessage(MOVING_ENTITY_DIRECTION_CHECK_DELAY, Object::safeCast(this), Object::safeCast(this), kMovingEntityCheckDirection, NULL);
				}
			}
			break;

		case __Y_AXIS:
			{
				fix10_6 distance = __ABS((this->transformation.globalPosition.y - this->initialPosition));

				if(distance > this->movingEntityDefinition->maximumDisplacement)
				{
					// make sure that I don't get stuck moving back and forth
					Body::stopMovement(this->body, (__X_AXIS | __Y_AXIS | __Z_AXIS));

					MessageDispatcher::dispatchMessage(this->movingEntityDefinition->idleDuration, Object::safeCast(this), Object::safeCast(this), kMovingEntityStartMovement, NULL);
				}
				else
				{
					MessageDispatcher::dispatchMessage(MOVING_ENTITY_DIRECTION_CHECK_DELAY, Object::safeCast(this), Object::safeCast(this), kMovingEntityCheckDirection, NULL);
				}
			}
			break;
	}
}

// start moving
void MovingEntity::startMovement()
{
	Direction direction = Entity::getDirection(Entity::safeCast(this));

	switch(this->movingEntityDefinition->axis)
	{
		case __X_AXIS:

			switch(direction.x)
			{
				case __LEFT:

					direction.x = __RIGHT;
					break;

				case __RIGHT:

					direction.x = __LEFT;
					break;
			}

			{
				Velocity velocity =
				{
					((int)this->movingEntityDefinition->velocity * direction.x),
					0,
					0,
				};

				Body::moveUniformly(this->body, velocity);
			}
			break;

		case __Y_AXIS:

			switch(direction.y)
			{
				case __UP:

					direction.y = __DOWN;
					break;

				case __DOWN:

					direction.y = __UP;
					break;
			}

			{
				Velocity velocity =
				{
					0,
					((int)this->movingEntityDefinition->velocity * direction.y),
					0,
				};

				Body::moveUniformly(this->body, velocity);
			}
			break;
	}

	MessageDispatcher::dispatchMessage(MOVING_ENTITY_DIRECTION_CHECK_DELAY, Object::safeCast(this), Object::safeCast(this), kMovingEntityCheckDirection, NULL);
}

u16 MovingEntity::getAxesForShapeSyncWithDirection()
{
	return this->movingEntityDefinition->axesForShapeSyncWithDirection;
}
