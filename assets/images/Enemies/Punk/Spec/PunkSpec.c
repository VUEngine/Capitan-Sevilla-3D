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

#include <BgmapAnimatedSprite.h>
#include <Box.h>
#include <Punk.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE PunkTiles[];
extern BYTE PunkBlackTiles[];
extern BYTE PunkMap[];
extern BYTE PunkBlackMap[];

extern BYTE PunkDyingTiles[];
extern BYTE PunkDyingBlackTiles[];
extern BYTE PunkDyingMap[];
extern BYTE PunkDyingBlackMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec PUNK_MOVE_ANIM =
{
	// number of frames of this animation function
	12,

	// frames to play in animation
	{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Move",
};

AnimationFunctionROMSpec PUNK_DIE_ANIM =
{
	// number of frames of this animation function
	38,

	// frames to play in animation
	{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
	 10, 10,
	 11, 12, 13, 14, 15, 16, 17, 18,
	 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
	 19, 20, 21, 22, 23},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)&Punk_onDieAnimationComplete,

	// function's name
	"Die",
};

AnimationDescriptionROMSpec PUNK_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&PUNK_MOVE_ANIM,
		(AnimationFunction*)&PUNK_DIE_ANIM,
		NULL,
	}
};

CharSetROMSpec PUNK_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	4*6,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SHARED_COORDINATED,

	// char spec
	PunkTiles,
};

CharSetROMSpec PUNK_BLACK_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	4*6,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SHARED_COORDINATED,

	// char spec
	PunkBlackTiles,
};

TextureROMSpec PUNK_TX =
{
	(CharSetSpec*)&PUNK_CH,

	// bgmap spec
	PunkMap,

	// cols (max 64)
	4,

	// rows (max 64)
	6,

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

TextureROMSpec PUNK_BLACK_TX =
{
	(CharSetSpec*)&PUNK_BLACK_CH,

	// bgmap spec
	PunkBlackMap,

	// cols (max 64)
	4,

	// rows (max 64)
	6,

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

BgmapSpriteROMSpec PUNK_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&PUNK_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, 2},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or BgmapSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec PUNK_BLACK_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&PUNK_BLACK_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 1, 2},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or BgmapSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const PUNK_SPRITES[] =
{
	&PUNK_SPRITE,
	&PUNK_BLACK_SPRITE,
	NULL
};

ShapeROMSpec PUNK_SHAPES[] =
{
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{16, 38, 24},

		// displacement (x, y, z, p)
		{0, 1, 0, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{0, 0, 0},

		// if true this shape checks for collisions against other shapes
		true,

		// layers in which I live
		kEnemiesLayer,

		// layers to ignore when checking for collisions
		~kEnemiesWallsLayer,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kLayerNone, kLayerNone}
};

EnemyROMSpec PUNK_EM =
{
	{
		{
			{
				{
					// class allocator
					__TYPE(Punk),

					// children
					NULL,

					// behaviors
					NULL,

					// extra
					NULL,
					
					// sprites
					(SpriteSpec**)PUNK_SPRITES,

					// use z displacement in projection
					false,

					// collision shapes
					(ShapeSpec*)PUNK_SHAPES,

					// size
					// if 0, width and height will be inferred from the first sprite's texture's size
					{0, 0, 0},

					// gameworld's character's type
					kEnemy,

					// physical specification
					(PhysicalSpecification*)NULL,
				},

				// pointer to the animation spec for the character
				(AnimationDescription*)&PUNK_ANIM,

				// initial animation
				"Move",
			},

			// true to create a body
			true,

			// axes subject to gravity
			__NO_AXIS,

			// axis around which to rotate the entity when syncronizing with body
			__Y_AXIS
		},

		// speed (x axis)
		__I_TO_FIX10_6(-3),
	},

	// energy
	2,

	// projectile ejector to add
	NULL,

	// relative position of projectile ejector
	{0, 0, 0},

	// respawn
	true
};

CharSetROMSpec PUNK_DYING_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	8*6,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char spec
	PunkDyingTiles,
};

CharSetROMSpec PUNK_DYING_BLACK_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	8*6,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char spec
	PunkDyingBlackTiles,
};

TextureROMSpec PUNK_DYING_TX =
{
	(CharSetSpec*)&PUNK_DYING_CH,

	// bgmap spec
	PunkDyingMap,

	// cols (max 64)
	8,

	// rows (max 64)
	6,

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

TextureROMSpec PUNK_DYING_BLACK_TX =
{
	(CharSetSpec*)&PUNK_DYING_BLACK_CH,

	// bgmap spec
	PunkDyingBlackMap,

	// cols (max 64)
	8,

	// rows (max 64)
	6,

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

BgmapSpriteROMSpec PUNK_DYING_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&PUNK_DYING_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, 2},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or BgmapSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};


BgmapSpriteROMSpec PUNK_DYING_BLACK_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&PUNK_DYING_BLACK_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 1, 2},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or BgmapSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const PUNK_DYING_SPRITES[] =
{
	&PUNK_DYING_SPRITE,
	&PUNK_DYING_BLACK_SPRITE,
	NULL
};