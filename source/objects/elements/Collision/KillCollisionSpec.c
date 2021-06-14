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

#include <Entity.h>
#include <Collision.h>
#include <Body.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CollisionROMSpec KILL_COLLISION_CL =
{
	// class allocator
	__TYPE(Collision),

	// children
	NULL,

	// behaviors
	NULL,

	// extra
	NULL,

	// sprites
	(SpriteSpec**)NULL,

	// use z displacement in projection
	false,

	// collision shapes
	(ShapeSpec*)NULL,

	// pixelSize
	// if 0, width and height will be inferred from the first sprite's texture's size
	{100, 100, 16},

	// gameworld's character's type
	kKillShape,

	// physical specification
	NULL,
};
