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

const PixelSize collision_2_28_8 = 	{2 * 8, 	28 * 8, 	8 * 8};
const PixelSize collision_48_2_8 = 	{48 * 8, 	8 * 8, 		8 * 8};


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void Collision::constructor(EntityDefinition* inGameEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(inGameEntityDefinition, id, internalId, name);
}

// class's destructor
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

		ShapeDefinition shapeDefinition =
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
			kNoLayer,
		};

		Shape shape = CollisionManager::createShape(Game::getCollisionManager(Game::getInstance()), SpatialObject::safeCast(this), &shapeDefinition);

		const Vector3D* myPosition = Entity::getPosition(Entity::safeCast(this));
		const Rotation* myRotation = Entity::getRotation(Entity::safeCast(this));
		const Scale* myScale = Entity::getScale(Entity::safeCast(this));

		Shape::position(shape, myPosition, myRotation, myScale, &this->size);

		VirtualList::pushBack(this->shapes, shape);
	}
}
