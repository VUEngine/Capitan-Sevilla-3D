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
#include "FlowerPot.h"


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other



// class's constructor
void FlowerPot::constructor(ProjectileDefinition* projectileDefinition, s16 id, s16 internalId, const char* const name)
{


	// construct base
	Base::constructor(projectileDefinition, id, internalId, name);
}

// class's constructor
void FlowerPot::destructor()
{


	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// process collisions
bool FlowerPot::enterCollision(const CollisionInformation* collisionInformation)
{

	ASSERT(collisionInformation->collidingShape, "FlowerPot::enterCollision: null collidingObjects");

	Shape collidingShape = collisionInformation->collidingShape;
	SpatialObject collidingObject = Shape::getOwner(collidingShape);

	switch(SpatialObject::getInGameType(collidingObject))
	{
		case kFloor:
		{
			// stop movement
			Actor::stopAllMovement(Actor::safeCast(this));

			// deactivate shapes
			Entity::activateShapes(Entity::safeCast(this), false);

			// play breaking animation
			//AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this), "break");

			return false;
			break;
		}
	}

	return Base::enterCollision(Actor::safeCast(this), collisionInformation) && (__ABS(collisionInformation->solutionVector.direction.y) > __ABS(collisionInformation->solutionVector.direction.x));
}