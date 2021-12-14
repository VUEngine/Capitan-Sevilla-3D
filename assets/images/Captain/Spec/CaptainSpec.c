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

#include <ObjectAnimatedSprite.h>
#include <Box.h>
#include "Captain.h"


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE CaptainTiles[];
extern BYTE CaptainBlackTiles[];
extern BYTE CaptainMap[];
extern BYTE CaptainBlackMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec CaptainIdleAnimation =
{
	// number of frames of this animation function
	8,

	// frames to play in animation
	{0, 1, 2, 3, 4, 5, 6, 7},

	// number of cycles a frame of animation is displayed
	6,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Idle",
};

AnimationFunctionROMSpec CaptainWalkAnimation =
{
	// number of frames of this animation function
	12,

	// frames to play in animation
	{8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19},

	// number of cycles a frame of animation is displayed
	3,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Walk",
};

AnimationFunctionROMSpec CaptainKneelDownAnimation =
{
	// number of frames of this animation function
	6,

	// frames to play in animation
	{20, 21, 22, 23, 24, 25},

	// number of cycles a frame of animation is displayed
	3,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"KneelDown",
};

AnimationFunctionROMSpec CaptainJumpAnimation =
{
	// number of frames of this animation function
	23,

	// frames to play in animation
	{26, 27, 28, 29, 30, 31, 32, 31, 32, 31, 32, 31, 32, 31, 32, 31, 32, 31, 32, 31, 32, 31, 32},

	// number of cycles a frame of animation is displayed
	3,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Jump",
};

AnimationFunctionROMSpec CaptainFallAnimation =
{
	// number of frames of this animation function
	18,

	// frames to play in animation
	{33, 34, 35, 36, 35, 36, 35, 36, 35, 36, 35, 36, 35, 36, 35, 36, 35, 36},

	// number of cycles a frame of animation is displayed
	3,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Fall",
};

AnimationFunctionROMSpec CaptainLandAnimation =
{
	// number of frames of this animation function
	3,

	// frames to play in animation
	{37, 38, 39},

	// number of cycles a frame of animation is displayed
	3,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Land",
};

AnimationFunctionROMSpec CaptainHitAnimation =
{
	// number of frames of this animation function
	16,

	// frames to play in animation
	{21, 20, 40, 41, 40, 41, 40, 41, 42, 43, 43, 43, 43, 43, 43, 43},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)&Captain_onHitAnimationComplete,

	// function's name
	"Hit",
};

AnimationFunctionROMSpec CaptainReloadAnimation =
{
	// number of frames of this animation function
	20,

	// frames to play in animation
	{44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63},

	// number of cycles a frame of animation is displayed
	3,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)&Captain_onReloadAnimationComplete,

	// function's name
	"Reload",
};

AnimationFunctionROMSpec CaptainDeadAnimation =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{64},

	// number of cycles a frame of animation is displayed
	16,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Dead",
};

AnimationDescriptionROMSpec CaptainAnimation =
{
	// animation functions
	{
		(AnimationFunction*)&CaptainIdleAnimation,
		(AnimationFunction*)&CaptainWalkAnimation,
		(AnimationFunction*)&CaptainKneelDownAnimation,
		(AnimationFunction*)&CaptainJumpAnimation,
		(AnimationFunction*)&CaptainFallAnimation,
		(AnimationFunction*)&CaptainLandAnimation,
		(AnimationFunction*)&CaptainHitAnimation,
		(AnimationFunction*)&CaptainReloadAnimation,
		(AnimationFunction*)&CaptainDeadAnimation,
		NULL,
	}
};

CharSetROMSpec CaptainCharset =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	35,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char spec
	CaptainTiles,
};

CharSetROMSpec CaptainBlackCharset =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	35,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char spec
	CaptainBlackTiles,
};

TextureROMSpec CaptainTexture =
{
	(CharSetSpec*)&CaptainCharset,

	// bgmap spec
	CaptainMap,

	// cols (max 64)
	5,

	// rows (max 64)
	7,

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

TextureROMSpec CaptainBlackTexture =
{
	(CharSetSpec*)&CaptainBlackCharset,

	// bgmap spec
	CaptainBlackMap,

	// cols (max 64)
	5,

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

ObjectSpriteROMSpec CaptainSprite =
{
	{
		// sprite's type
		__TYPE(ObjectAnimatedSprite),

		// texture spec
		(TextureSpec*)&CaptainTexture,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, 2},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_OBJECT,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

ObjectSpriteROMSpec CaptainBlackSprite =
{
	{
		// sprite's type
		__TYPE(ObjectAnimatedSprite),

		// texture spec
		(TextureSpec*)&CaptainBlackTexture,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 1, 2},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_OBJECT,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

ObjectSpriteROMSpec* const CaptainSprites[] =
{
	&CaptainSprite,
	&CaptainBlackSprite,
	NULL
};

ShapeROMSpec CaptainShapes[] =
{
	// standing
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{19, 37, 48},

		// displacement (x, y, z, p)
		{4, 7, -16, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{1, 1, 1},

		// if true this shape checks for collisions against other shapes
		true,

		// layers in which I live
		kPlayerLayer,

		// layers to ignore when checking for collisions
		kParticlesLayer | kPlayerLayer | kEnemiesWallsLayer,
	},

	// kneeling
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{19, 28, 48},

		// displacement (x, y, z, p)
		{4, 11, -16, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{1, 1, 1},

		// if true this shape checks for collisions against other shapes
		true,

		// layers in which I live
		kPlayerLayer,

		// layers to ignore when checking for collisions
		kParticlesLayer | kPlayerLayer | kEnemiesWallsLayer,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kLayerNone, kLayerNone}
};

PhysicalSpecificationROMSpec CaptainPhysicalProperties =
{
	// mass
	__F_TO_FIX10_6(0.65f),

	// friction
	__F_TO_FIX10_6(0),

	// bounciness
	__F_TO_FIX10_6(CAPTAIN_BOUNCINESS),

	// maximum velocity
	{__I_TO_FIX10_6(100), __I_TO_FIX10_6(100), __I_TO_FIX10_6(100)},

	// maximum speed
	__I_TO_FIX10_6(0)
};

CaptainROMSpec CaptainEntity =
{
	{
		{
			// class allocator
			__TYPE(Captain),

			// children
			NULL,

			// behaviors
			NULL,

			// extra
			NULL,

			// sprites
			(SpriteSpec**)CaptainSprites,

			// use z displacement in projection
			false,

			// collision shapes
			(ShapeSpec*)CaptainShapes,

			// size
			// if 0, width and height will be inferred from the first sprite's texture's size
			{0, 0, 0},

			// gameworld's character's type
			kCaptain,

			// physical specification
			(PhysicalSpecification*)&CaptainPhysicalProperties,
		},

		// pointer to the animation spec for the character
		(AnimationDescription*)&CaptainAnimation,

		// initial animation
		"Idle",
	},

	// true to create a body
	true,

	// axes subject to gravity
	__Y_AXIS,

	// axis around which to rotate the entity when syncronizing with body
	__Y_AXIS
};
