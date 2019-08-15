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
#include <MessageDispatcher.h>
#include <Box.h>
#include <PhysicalWorld.h>
#include <macros.h>
#include <debugConfig.h>
#include "Collision.h"


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

const PixelSize collision_16_224_64 = 	{ 16, 	224,	64};
const PixelSize collision_56_56_64 = 	{ 56, 	 56,	64};
const PixelSize collision_384_16_64 = 	{384, 	 64, 	64};
const PixelSize collision_3608_16_64 = 	{3608, 	 64, 	64};


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void Collision::constructor(EntitySpec* entitySpec, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(entitySpec, id, internalId, name);
}

void Collision::destructor()
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// set extra info
void Collision::setExtraInfo(void* extraInfo)
{
	this->size = Size::getFromPixelSize(*((PixelSize*)extraInfo));
}

void Collision::initialTransform(Transformation* environmentTransform, u32 recursive)
{
	Base::initialTransform(this, environmentTransform, recursive);

	if(!this->shapes)
	{
		this->shapes = new VirtualList();

		ShapeSpec shapeSpec =
		{
			// class allocator
			__TYPE(Box),

			// size
			PixelSize::getFromSize(this->size),

			// displacement modifier
			{0, 0, -1, 0},

			// rotation modifier
			{0, 0, 0},

			// scale modifier
			{1, 1, 1},

			// if true this shape checks for collisions against other shapes
			false,

			/// layers in which I live
			kSolidLayer,

			/// layers to ignore when checking for collisions
			kLayerNone,
		};

		Shape shape = CollisionManager::createShape(Game::getCollisionManager(Game::getInstance()), SpatialObject::safeCast(this), &shapeSpec);

		const Vector3D* myPosition = Entity::getPosition(this);
		const Rotation* myRotation = Entity::getRotation(this);
		const Scale* myScale = Entity::getScale(this);

		Shape::position(shape, myPosition, myRotation, myScale, &this->size);

		VirtualList::pushBack(this->shapes, shape);
	}
}
