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
const PixelSize collision_64_2_8 = 	{64 * 8, 	8 * 8, 		8 * 8};


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Collision, Entity);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Collision, EntityDefinition* inGameEntityDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(Collision, inGameEntityDefinition, id, internalId, name);

// class's constructor
void Collision_constructor(Collision this, EntityDefinition* inGameEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base_constructor(this, inGameEntityDefinition, id, internalId, name);
}

// class's destructor
void Collision_destructor(Collision this)
{
	// delete the super object
	// must always be called at the end of the destructor
	Base_destructor();
}

// set extra info
void Collision_setExtraInfo(Collision this, void* extraInfo)
{
	ASSERT(this, "Collision::setExtraInfo: null this");

	this->size = Size_getFromPixelSize(*((PixelSize*)extraInfo));
}

void Collision_initialTransform(Collision this, Transformation* environmentTransform, u32 recursive)
{
	ASSERT(this, "Collision::setExtraInfo: null this");

	Base_initialTransform(this, environmentTransform, recursive);

	if(!this->shapes)
	{
		this->shapes = __NEW(VirtualList);

		ShapeDefinition shapeDefinition =
		{
			// class allocator
			__TYPE(Box),

			// size
			PixelSize_getFromSize(this->size),

			// displacement modifier
			{0, 0, -1, 0},

			// rotation modifier
			{0, 0, 0},

			// scale modifier
			{__I_TO_FIX7_9(1), __I_TO_FIX7_9(1), __I_TO_FIX7_9(1)},

			// if true this shape checks for collisions against other shapes
			false,

			/// layers in which I live
			kSolidLayer,

			/// layers to ignore when checking for collisions
			kNoLayer,
		};

		Shape shape = CollisionManager_createShape(Game_getCollisionManager(Game_getInstance()), __SAFE_CAST(SpatialObject, this), &shapeDefinition);

		const Vector3D* myPosition = Entity_getPosition(__SAFE_CAST(Entity, this));
		const Rotation* myRotation = Entity_getRotation(__SAFE_CAST(Entity, this));
		const Scale* myScale = Entity_getScale(__SAFE_CAST(Entity, this));

		Shape_position(shape, myPosition, myRotation, myScale, &this->size);

		VirtualList_pushBack(this->shapes, shape);
	}
}
