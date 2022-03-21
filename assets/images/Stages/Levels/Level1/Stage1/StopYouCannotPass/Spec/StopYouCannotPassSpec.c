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
#include <Message.h>
#include <Box.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern uint32 StopYouCannotPassTiles[];
extern uint16 StopYouCannotPassMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec StopYouCannotPassHiddenAnimation =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{0},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Hidden",
};

AnimationFunctionROMSpec StopYouCannotPassHideAnimation =
{
	// number of frames of this animation function
	5,

	// frames to play in animation
	{4, 3, 2, 1, 0},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Hide",
};

AnimationFunctionROMSpec StopYouCannotPassEnglishAnimation =
{
	// number of frames of this animation function
	5,

	// frames to play in animation
	{1, 2, 3, 4, 5},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"0",
};

AnimationFunctionROMSpec StopYouCannotPassSpanishAnimation =
{
	// number of frames of this animation function
	5,

	// frames to play in animation
	{1, 2, 3, 4, 6},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"1",
};

AnimationFunctionROMSpec StopYouCannotPassGermanAnimation =
{
	// number of frames of this animation function
	5,

	// frames to play in animation
	{1, 2, 3, 4, 7},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"2",
};

AnimationFunctionROMSpec StopYouCannotPassFrenchAnimation =
{
	// number of frames of this animation function
	5,

	// frames to play in animation
	{1, 2, 3, 4, 8},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"3",
};

AnimationDescriptionROMSpec StopYouCannotPassAnimation =
{
	// animation functions
	{
		(AnimationFunction*)&StopYouCannotPassHiddenAnimation,
		(AnimationFunction*)&StopYouCannotPassHideAnimation,
		(AnimationFunction*)&StopYouCannotPassEnglishAnimation,
		(AnimationFunction*)&StopYouCannotPassSpanishAnimation,
		(AnimationFunction*)&StopYouCannotPassGermanAnimation,
		(AnimationFunction*)&StopYouCannotPassFrenchAnimation,
		NULL,
	}
};

CharSetROMSpec StopYouCannotPassCharset =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	10 * 5,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char spec
	StopYouCannotPassTiles,

	// pointer to the frames offsets
	NULL,
};

TextureROMSpec StopYouCannotPassTexture =
{
	(CharSetSpec*)&StopYouCannotPassCharset,

	// bgmap spec
	StopYouCannotPassMap,

	// cols (max 64)
	10,

	// rows (max 64)
	5,

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

BgmapSpriteROMSpec StopYouCannotPassSprite =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&StopYouCannotPassTexture,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, 2},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const StopYouCannotPassSprites[] =
{
	&StopYouCannotPassSprite,
	NULL
};

ShapeROMSpec StopYouCannotPassShapes[] =
{
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{112, 160, 24},

		// displacement (x, y, z, p)
		{-32, 0, 0, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{0, 0, 0},

		// if true this shape checks for collisions against other shapes
		true,

		// layers in which I live
		kMessageLayer,

		// layers to ignore when checking for collisions
		~kPlayerLayer,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kLayerNone, kLayerNone}
};

AnimatedEntityROMSpec StopYouCannotPassEntity =
{
	{
		// class allocator
		__TYPE(Message),

		// children
		NULL,

		// behaviors
		NULL,

		// extra
		NULL,

		// sprites
		(SpriteSpec**)StopYouCannotPassSprites,

		// use z displacement in projection
		false,

		// collision shapes
		(ShapeSpec*)StopYouCannotPassShapes,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kMessage,

		// physical specification
		(PhysicalSpecification*)NULL,
	},

	// pointer to the animation spec for the character
	(AnimationDescription*)&StopYouCannotPassAnimation,

	// initial animation
	"Hidden",
};
