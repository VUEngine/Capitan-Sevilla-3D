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

#include <LocalizedEntity.h>
#include <BgmapAnimatedSprite.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE PressStartButtonTiles[];
extern BYTE PressStartButtonMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec PressStartButtonEnglishAnimation =
{
	// number of frames of this animation function
	9,

	// frames to play in animation
	{0, 0, 0, 1, 2, 12, 12, 2, 1},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"0",
};

AnimationFunctionROMSpec PressStartButtonSpanishAnimation =
{
	// number of frames of this animation function
	9,

	// frames to play in animation
	{3, 3, 3, 4, 5, 12, 12, 5, 4},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"1",
};
AnimationFunctionROMSpec PressStartButtonGermanAnimation =
{
	// number of frames of this animation function
	9,

	// frames to play in animation
	{6, 6, 6, 7, 8, 12, 12, 8, 7},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"2",
};

AnimationFunctionROMSpec PressStartButtonFrenchAnimation =
{
	// number of frames of this animation function
	9,

	// frames to play in animation
	{9, 9, 9, 10, 11, 12, 12, 11, 10},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"3",
};

AnimationFunctionROMSpec PressStartButtonTransparentAnimation =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{12},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Transparent",
};

AnimationDescriptionROMSpec PressStartButtonAnimation =
{
	// animation functions
	{
		(AnimationFunction*)&PressStartButtonEnglishAnimation,
		(AnimationFunction*)&PressStartButtonGermanAnimation,
		(AnimationFunction*)&PressStartButtonSpanishAnimation,
		(AnimationFunction*)&PressStartButtonFrenchAnimation,
		(AnimationFunction*)&PressStartButtonTransparentAnimation,
		NULL,
	}
};

CharSetROMSpec PressStartButtonCharset =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	19,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char definition
	PressStartButtonTiles,
};

TextureROMSpec PressStartButtonTexture =
{
	// charset definition
	(CharSetSpec*)&PressStartButtonCharset,

	// bgmap definition
	PressStartButtonMap,

	// cols (max 64)
	19,

	// rows (max 64)
	1,

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

BgmapSpriteROMSpec PressStartButtonSprite =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture definition
		(TextureSpec*)&PressStartButtonTexture,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const PressStartButtonSprites[] =
{
	&PressStartButtonSprite,
	NULL
};

LocalizedEntityROMSpec PressStartButtonEntity =
{
	{
		// class allocator
		__TYPE(LocalizedEntity),

		// children
		NULL,

		// behaviors
		NULL,

		// extra
		NULL,

		// sprites
		(SpriteSpec**)PressStartButtonSprites,

		// use z displacement in projection
		false,

		// collision shapes
		(ShapeSpec*)NULL,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		0,

		// physical specification
		(PhysicalSpecification*)NULL,
	},

	// pointer to the animation definition for the item
	(AnimationDescription*)&PressStartButtonAnimation,

	// initial animation
	"Transparent",
};
