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
#include <Lift.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern uint32 Level1Stage2LiftTiles[];
extern uint16 Level1Stage2LiftMap[];
extern StageEntryPointSpec Level1Stage3MainEntryPoint;
extern StageEntryPointSpec Level1Stage4MainEntryPoint;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec Level1Stage2LiftOpenAnimation =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{0},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Open",
};

AnimationFunctionROMSpec Level1Stage2LiftClosedAnimation =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{1},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Closed",
};

AnimationFunctionROMSpec Level1Stage2LiftBrokenAnimation =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{2},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Broken",
};

AnimationDescriptionROMSpec Level1Stage2LiftAnimation =
{
	// animation functions
	{
		(AnimationFunction*)&Level1Stage2LiftOpenAnimation,
		(AnimationFunction*)&Level1Stage2LiftClosedAnimation,
		(AnimationFunction*)&Level1Stage2LiftBrokenAnimation,
		NULL,
	}
};

CharSetROMSpec Level1Stage2LiftCharset =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	4 * 9,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char spec
	Level1Stage2LiftTiles,

	// pointer to the frames offsets
	NULL,
};

TextureROMSpec Level1Stage2LiftTexture =
{
	(CharSetSpec*)&Level1Stage2LiftCharset,

	// bgmap spec
	Level1Stage2LiftMap,

	// cols (max 64)
	4,

	// rows (max 64)
	9,

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
	false
};

BgmapSpriteROMSpec Level1Stage2LiftSprite =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&Level1Stage2LiftTexture,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, -1, 1},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const Level1Stage2LiftSprites[] =
{
	&Level1Stage2LiftSprite,
	NULL
};

ShapeROMSpec Level1Stage2LiftShapes[] =
{
	// TODO: this shape should not activate lift
	/*
	// top
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{20, 6, 64},

		// displacement (x, y, z, p)
		{8, -31, 0, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{0, 0, 0},

		// if true this shape checks for collisions against other shapes
		false,

		// layers in which I live
		kSolidLayer,

		// layers to ignore when checking for collisions
		kAllLayers,
	},*/

	// right
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{16, 72, 64},

		// displacement (x, y, z, p)
		{22, 13, 0, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{0, 0, 0},

		// if true this shape checks for collisions against other shapes
		false,

		// layers in which I live
		kSolidLayer,

		// layers to ignore when checking for collisions
		kAllLayers,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kLayerNone, kLayerNone}
};

LiftROMSpec Level1Stage2LiftEntity =
{
	{
		{
			{
				// class allocator
				__TYPE(Lift),

				// children
				NULL,

				// behaviors
				NULL,

				// extra
				NULL,

				// sprites
				(SpriteSpec**)Level1Stage2LiftSprites,

				// use z displacement in projection
				false,

				// collision shapes
				(ShapeSpec*)Level1Stage2LiftShapes,

				// size
				// if 0, width and height will be inferred from the first sprite's texture's size
				{0, 0, 0},

				// gameworld's character's type
				kLift,

				// physical specification
				(PhysicalSpecification*)NULL,
			},

			// pointer to the animation spec for the character
			(AnimationDescription*)&Level1Stage2LiftAnimation,

			// initial animation
			"Open"
		},

		// true to create a body
		true,

		// axes subject to gravity
		__NO_AXIS,

		// axis around which to rotate the entity when syncronizing with body
		__LOCK_AXIS
	},

	// velocity after entering
	{0, __I_TO_FIX10_6(-2), 0},

	// entry point to load after entering
	(StageEntryPointSpec*)&Level1Stage3MainEntryPoint,
};

LiftROMSpec Level1Stage3LiftEntity =
{
	{
		{
			{
				// class allocator
				__TYPE(Lift),

				// children
				NULL,

				// behaviors
				NULL,

				// extra
				NULL,

				// sprites
				(SpriteSpec**)Level1Stage2LiftSprites,

				// use z displacement in projection
				false,

				// collision shapes
				(ShapeSpec*)Level1Stage2LiftShapes,

				// size
				// if 0, width and height will be inferred from the first sprite's texture's size
				{0, 0, 0},

				// gameworld's character's type
				kLift,

				// physical specification
				(PhysicalSpecification*)NULL,
			},

			// pointer to the animation spec for the character
			(AnimationDescription*)&Level1Stage2LiftAnimation,

			// initial animation
			"Open"
		},

		// true to create a body
		true,

		// axes subject to gravity
		__NO_AXIS,

		// axis around which to rotate the entity when syncronizing with body
		__NO_AXIS
	},

	// velocity after entering
	{0, __I_TO_FIX10_6(2), 0},

	// entry point to load after entering
	(StageEntryPointSpec*)&Level1Stage4MainEntryPoint,
};


ShapeROMSpec Level1Stage4LiftShapes[] =
{
	// TODO: this shape should not activate lift
	// bottom
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{32, 6, 64},

		// displacement (x, y, z, p)
		{0, 31, 0, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{0, 0, 0},

		// if true this shape checks for collisions against other shapes
		false,

		// layers in which I live
		kSolidLayer,

		// layers to ignore when checking for collisions
		kAllLayers,
	},


	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kLayerNone, kLayerNone}
};


LiftROMSpec Level1Stage4LiftEntity =
{
	{
		{
			{
				// class allocator
				__TYPE(Lift),

				// children
				NULL,

				// behaviors
				NULL,

				// extra
				NULL,

				// sprites
				(SpriteSpec**)Level1Stage2LiftSprites,

				// use z displacement in projection
				false,

				// collision shapes
				(ShapeSpec*)Level1Stage4LiftShapes,

				// size
				// if 0, width and height will be inferred from the first sprite's texture's size
				{0, 0, 0},

				// gameworld's character's type
				kFloor,

				// physical specification
				(PhysicalSpecification*)NULL,
			},

			// pointer to the animation spec for the character
			(AnimationDescription*)&Level1Stage2LiftAnimation,

			// initial animation
			"Closed"
		},

		// true to create a body
		true,

		// axes subject to gravity
		__NO_AXIS,

		// axis around which to rotate the entity when syncronizing with body
		__NO_AXIS
	},

	// velocity after entering
	{0, __I_TO_FIX10_6(2), 0},

	// entry point to load after entering
	NULL,
};
