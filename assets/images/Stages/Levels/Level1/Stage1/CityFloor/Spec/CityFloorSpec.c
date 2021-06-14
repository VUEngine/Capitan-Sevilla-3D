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
#include <MBgmapSprite.h>
#include <Collision.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE CityFloorTiles[];
extern BYTE CityFloorLMap[];
extern BYTE CityFloorRMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec CITY_FLOOR_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	6,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__NOT_ANIMATED,

	// char spec
	CityFloorTiles,
};

/* LEFT */

TextureROMSpec CITY_FLOOR_L_TX =
{
	// charset spec
	(CharSetSpec*)&CITY_FLOOR_CH,

	// bgmap spec
	CityFloorLMap,

	// cols (max 64)
	64,

	// rows (max 64)
	3,

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	1,

	// palette number (0-3)
	0,

	// recyclable
	false,

	// vertical flip
	false,

	// horizontal flip
	false,
};

TextureROMSpec* const CITY_FLOOR_L_TEXTURES[] =
{
	(TextureSpec*)&CITY_FLOOR_L_TX,
	NULL
};

MBgmapSpriteROMSpec CITY_FLOOR_L_SPRITE =
{
	{
		{
			// sprite's type
			__TYPE(MBgmapSprite),

			// texture spec
			NULL,

			// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
			false,

			// displacement
			{0, 0, 2, 1},
		},

		// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
		// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
		__WORLD_BGMAP,

		// pointer to affine/hbias manipulation function
		NULL,

		// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
		__WORLD_LON,
	},

	// textures
	(TextureSpec**)CITY_FLOOR_L_TEXTURES,

	// SCX/SCY (__WORLD_1x1, 1x2, 1x4, 1x8, 2x1, 2x2, 2x4, 4x1, 4x2, or 8x1)
	// textures must be 64x64 for anything other than 1x1
	__WORLD_1x1,

	// x loop
	true,

	// y loop
	false,

	// bounds the sprite's width to provide culling
	// if 0, the value is inferred from the texture
	0,

	// bounds the sprite's height to provide culling
	// if 0, the value is inferred from the texture
	0,
};

/* RIGHT */

TextureROMSpec CITY_FLOOR_R_TX =
{
	// charset spec
	(CharSetSpec*)&CITY_FLOOR_CH,

	// bgmap spec
	CityFloorRMap,

	// cols (max 64)
	64,

	// rows (max 64)
	3,

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	1,

	// palette number (0-3)
	0,

	// recyclable
	false,

	// vertical flip
	false,

	// horizontal flip
	false,
};

TextureROMSpec* const CITY_FLOOR_R_TEXTURES[] =
{
	(TextureSpec*)&CITY_FLOOR_R_TX,
	NULL
};

MBgmapSpriteROMSpec CITY_FLOOR_R_SPRITE =
{
	{
		{
			// sprite's type
			__TYPE(MBgmapSprite),

			// texture spec
			NULL,

			// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
			false,

			// displacement
			{0, 0, 2, 1},
		},

		// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
		// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
		__WORLD_BGMAP,

		// pointer to affine/hbias manipulation function
		NULL,

		// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
		__WORLD_RON,
	},

	// textures
	(TextureSpec**)CITY_FLOOR_R_TEXTURES,

	// SCX/SCY (__WORLD_1x1, 1x2, 1x4, 1x8, 2x1, 2x2, 2x4, 4x1, 4x2, or 8x1)
	// textures must be 64x64 for anything other than 1x1
	__WORLD_1x1,

	// x loop
	true,

	// y loop
	false,

	// bounds the sprite's width to provide culling
	// if 0, the value is inferred from the texture
	0,

	// bounds the sprite's height to provide culling
	// if 0, the value is inferred from the texture
	0,
};

/* ENTITY */

BgmapSpriteROMSpec* const CITY_FLOOR_SPRITES[] =
{
	(BgmapSpriteROMSpec*)&CITY_FLOOR_L_SPRITE,
	(BgmapSpriteROMSpec*)&CITY_FLOOR_R_SPRITE,
	NULL
};

EntityROMSpec CITY_FLOOR_EN =
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
	(SpriteSpec**)CITY_FLOOR_SPRITES,

	// use z displacement in projection
	false,

	// collision shapes
	NULL,

	// size
	// if 0, width and height will be inferred from the first sprite's texture's size
	{0, 0, 0},

	// gameworld's character's type
	kTypeNone,

	// physical specification
	NULL,
};

PhysicalSpecificationROMSpec CITY_FLOOR_COLLISION_CL_PHYSICAL_PROPERTIES =
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

CollisionROMSpec CITY_FLOOR_COLLISION_CL =
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
	kFloor,

	// physical specification
	(PhysicalSpecification*)&CITY_FLOOR_COLLISION_CL_PHYSICAL_PROPERTIES,
};
