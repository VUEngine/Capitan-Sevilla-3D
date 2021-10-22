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
const PixelSize collision_48_56_64 = 	{ 48, 	 56,	64};
const PixelSize collision_56_56_64 = 	{ 56, 	 56,	64};
const PixelSize collision_384_16_64 = 	{384, 	 64, 	64};
const PixelSize collision_3608_16_64 = 	{3608, 	 64, 	64};


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void Collision::constructor(EntitySpec* entitySpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor(entitySpec, internalId, name);
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

void Collision::initialTransform(Transformation* environmentTransform, uint32 recursive)
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
