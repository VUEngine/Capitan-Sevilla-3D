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
#include <PlatformerLevelState.h>
#include <StageExitPoint.h>
#include <Body.h>
#include <Box.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageEntryPointSpec Level1Stage2MainEntryPoint;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

ShapeROMSpec Level1Stage1MainExitPointShapes[] =
{
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{16, 80, 64},

		// displacement (x, y, z, p)
		{0, 0, 0, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{0, 0, 0},

		// if true this shape checks for collisions against other shapes
		false,

		// layers in which I live
		kSolidLayer,

		// layers to ignore when checking for collisions
		kLayerNone,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kLayerNone, kLayerNone}
};

StageExitPointROMSpec Level1Stage1MainExitXp =
{
	{
		// class allocator
		__TYPE(StageExitPoint),

		// children
		NULL,

		// behaviors
		NULL,

		// extra
		NULL,

		// sprites
		NULL,

		// use z displacement in projection
		false,

		// collision shapes
		(ShapeSpec*)Level1Stage1MainExitPointShapes,

		// pixelSize
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kStageExitPoint,

		// physical specification
		NULL,
	},

	// target entry point
	(StageEntryPointSpec*)&Level1Stage2MainEntryPoint,
};
