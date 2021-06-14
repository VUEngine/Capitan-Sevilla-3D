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
#include <BgmapSprite.h>
#include <Box.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE Level1Stage3Building3aTiles[];
extern BYTE Level1Stage3Building3aLMap[];
extern BYTE Level1Stage3Building3aRMap[];
extern BYTE Level1Stage3Building3aWallMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec LEVEL_1_STAGE_3_BUILDING_3A_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	290,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__NOT_ANIMATED,

	// char spec
	Level1Stage3Building3aTiles,
};

/* Left */

TextureROMSpec LEVEL_1_STAGE_3_BUILDING_3A_L_TX =
{
	// charset spec
	(CharSetSpec*)&LEVEL_1_STAGE_3_BUILDING_3A_CH,

	// bgmap spec
	Level1Stage3Building3aLMap,

	// cols (max 64)
	33,

	// rows (max 64)
	15,

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	1,

	// palette number (0-3)
	1,

	// recyclable
	false,

	// vertical flip
	false,

	// horizontal flip
	false,
};

BgmapSpriteROMSpec LEVEL_1_STAGE_3_BUILDING_3A_L_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapSprite),

		// texture spec
		(TextureSpec*)&LEVEL_1_STAGE_3_BUILDING_3A_L_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 2, 1}
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_LON,
};

/* Right */

TextureROMSpec LEVEL_1_STAGE_3_BUILDING_3A_R_TX =
{
	// charset spec
	(CharSetSpec*)&LEVEL_1_STAGE_3_BUILDING_3A_CH,

	// bgmap spec
	Level1Stage3Building3aRMap,

	// cols (max 64)
	33,

	// rows (max 64)
	15,

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	1,

	// palette number (0-3)
	1,

	// recyclable
	false,

	// vertical flip
	false,

	// horizontal flip
	false,
};

BgmapSpriteROMSpec LEVEL_1_STAGE_3_BUILDING_3A_R_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapSprite),

		// texture spec
		(TextureSpec*)&LEVEL_1_STAGE_3_BUILDING_3A_R_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 2, 1}
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_RON,
};

/* Front Wall */

TextureROMSpec LEVEL_1_STAGE_3_BUILDING_3A_WALL_TX =
{
	// charset spec
	(CharSetSpec*)&LEVEL_1_STAGE_3_BUILDING_3A_CH,

	// bgmap spec
	Level1Stage3Building3aWallMap,

	// cols (max 64)
	38,

	// rows (max 64)
	7,

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	1,

	// palette number (0-3)
	1,

	// recyclable
	false,

	// vertical flip
	false,

	// horizontal flip
	false,
};

BgmapSpriteROMSpec LEVEL_1_STAGE_3_BUILDING_3A_WALL_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapSprite),

		// texture spec
		(TextureSpec*)&LEVEL_1_STAGE_3_BUILDING_3A_WALL_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{-20, 24, -1, 1}
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

/* Entity */

BgmapSpriteROMSpec* const LEVEL_1_STAGE_3_BUILDING_3A_SPRITES[] =
{
	&LEVEL_1_STAGE_3_BUILDING_3A_L_SPRITE,
	&LEVEL_1_STAGE_3_BUILDING_3A_R_SPRITE,
	&LEVEL_1_STAGE_3_BUILDING_3A_WALL_SPRITE,
	NULL
};

ShapeROMSpec LEVEL_1_STAGE_3_BUILDING_3A_SHAPES[] =
{
	// statue
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{40, 40, 32},

		// displacement (x, y, z, p)
		{-148, 34, 0, 0},

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

	// floor
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{288, 32, 32},

		// displacement (x, y, z, p)
		{-4, 64, 0, 0},

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

PhysicalSpecificationROMSpec LEVEL_1_STAGE_3_BUILDING_3A_PHYSICAL_PROPERTIES =
{
	// mass
	__F_TO_FIX10_6(0),

	// friction
	__F_TO_FIX10_6(0.85f),

	// bounciness
	__F_TO_FIX10_6(FLOOR_BOUNCINESS),

	// maximum velocity
	{__I_TO_FIX10_6(100), __I_TO_FIX10_6(100), __I_TO_FIX10_6(100)},

	// maximum speed
	__I_TO_FIX10_6(0)
};

EntityROMSpec LEVEL_1_STAGE_3_BUILDING_3A_EN =
{
	// class allocator
	__TYPE(Entity),

	// children
	NULL,

	// behaviors
	NULL,

	// extra
	NULL,

	// sprites
	(SpriteSpec**)LEVEL_1_STAGE_3_BUILDING_3A_SPRITES,

	// use z displacement in projection
	false,

	// collision shapes
	(ShapeSpec*)LEVEL_1_STAGE_3_BUILDING_3A_SHAPES,

	// size
	// if 0, width and height will be inferred from the first sprite's texture's size
	{0, 0, 0},

	// gameworld's character's type
	kFloor,

	// physical specification
	(PhysicalSpecification*)&LEVEL_1_STAGE_3_BUILDING_3A_PHYSICAL_PROPERTIES,
};
