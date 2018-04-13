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
#include "Sausage.h"


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Sausage, Projectile);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Sausage, ProjectileDefinition* projectileDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(Sausage, projectileDefinition, id, internalId, name);

// class's constructor
void Sausage_constructor(Sausage this, ProjectileDefinition* projectileDefinition, s16 id, s16 internalId, const char* const name)
{
	ASSERT(this, "Sausage::constructor: null this");

	// construct base
	__CONSTRUCT_BASE(Projectile, projectileDefinition, id, internalId, name);
}

// class's constructor
void Sausage_destructor(Sausage this)
{
	ASSERT(this, "Sausage::destructor: null this");

	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// process collisions
bool Sausage_enterCollision(Sausage this, const CollisionInformation* collisionInformation)
{
	ASSERT(this, "Sausage::enterCollision: null this");
	ASSERT(collisionInformation->collidingShape, "Sausage::enterCollision: null collidingObjects");

	Shape collidingShape = collisionInformation->collidingShape;
	SpatialObject collidingObject = Shape_getOwner(collidingShape);

	switch(__VIRTUAL_CALL(SpatialObject, getInGameType, collidingObject))
	{
		case kEnemy:
		{
			// stop movement
			Actor_stopAllMovement(__SAFE_CAST(Actor, this));

			// deactivate shapes
			Entity_activateShapes(__SAFE_CAST(Entity, this), false);

			// play hitting animation
			//AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "hit");

			return false;
			break;
		}
	}

	return false;
}
