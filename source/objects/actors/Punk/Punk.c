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
#include <CustomCameraEffectManager.h>
#include <SoundManager.h>
#include "Punk.h"


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void Punk::constructor(EnemySpec* enemySpec, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(enemySpec, internalId, name);
}

void Punk::destructor()
{
	// destroy the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void Punk::die()
{
	extern SpriteSpec* const PUNK_DYING_SPRITES[];
	Punk::releaseSprites(this);
	Punk::addSprites(this, (SpriteSpec**)PUNK_DYING_SPRITES);
	Punk::stopAllMovement(this);
	Punk::allowCollisions(this, false);
	Punk::playAnimation(this, "Die");
	this->invalidateGraphics |= __INVALIDATE_ROTATION;
	this->respawn = false;
}

void Punk::onDieAnimationComplete(Object eventFirer __attribute__ ((unused)))
{
	Punk::deleteMyself(this);
}

// process collisions
bool Punk::enterCollision(const CollisionInformation* collisionInformation)
{
	Shape collidingShape = collisionInformation->collidingShape;
	SpatialObject collidingObject = Shape::getOwner(collidingShape);
	u32 collidingObjectInGameType = SpatialObject::getInGameType(collidingObject);

	Velocity velocity = (Velocity){-this->speed, 0, 0};

	switch(collidingObjectInGameType)
	{
		// speed things up by breaking early
		case kEnemyWall:

			this->speed = -this->speed;
			Punk::moveUniformly(this, &velocity);
			break;
	}

	return false;
}