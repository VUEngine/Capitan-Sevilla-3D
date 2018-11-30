/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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

AnimationFunctionROMDef CAPTAIN_IDLE_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{0},

	// number of cycles a frame of animation is displayed
	16,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Idle",
};

AnimationFunctionROMDef CAPTAIN_WALK_ANIM =
{
	// number of frames of this animation function
	12,

	// frames to play in animation
	{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Walk",
};

AnimationFunctionROMDef CAPTAIN_KNEEL_DOWN_ANIM =
{
	// number of frames of this animation function
	6,

	// frames to play in animation
	{12, 13, 14, 15, 16, 17},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"KneelDown",
};

AnimationFunctionROMDef CAPTAIN_JUMP_ANIM =
{
	// number of frames of this animation function
	18,

	// frames to play in animation
	{18, 19, 20, 21, 22, 21, 22, 21, 22, 21, 22, 21, 22, 21, 22, 21, 22, 21, 22},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Jump",
};

AnimationFunctionROMDef CAPTAIN_FALL_ANIM =
{
	// number of frames of this animation function
	17,

	// frames to play in animation
	{23, 24, 25, 26, 25, 26, 25, 26, 25, 26, 25, 26, 25, 26, 25, 26, 25, 26},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Fall",
};

AnimationFunctionROMDef CAPTAIN_LAND_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{27, 28},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Land",
};

AnimationFunctionROMDef CAPTAIN_HIT_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{29},

	// number of cycles a frame of animation is displayed
	16,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Hit",
};

AnimationFunctionROMDef CAPTAIN_SHOOT_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{29},

	// number of cycles a frame of animation is displayed
	16,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Shoot",
};

AnimationFunctionROMDef CAPTAIN_DEAD_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{30},

	// number of cycles a frame of animation is displayed
	16,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Dead",
};

AnimationDescriptionROMDef CAPTAIN_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&CAPTAIN_IDLE_ANIM,
		(AnimationFunction*)&CAPTAIN_WALK_ANIM,
		(AnimationFunction*)&CAPTAIN_KNEEL_DOWN_ANIM,
		(AnimationFunction*)&CAPTAIN_JUMP_ANIM,
		(AnimationFunction*)&CAPTAIN_FALL_ANIM,
		(AnimationFunction*)&CAPTAIN_LAND_ANIM,
		(AnimationFunction*)&CAPTAIN_HIT_ANIM,
		(AnimationFunction*)&CAPTAIN_SHOOT_ANIM,
		(AnimationFunction*)&CAPTAIN_DEAD_ANIM,
		NULL,
	}
};

CharSetROMDef CAPTAIN_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	24,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char definition
	CaptainTiles,
};

CharSetROMDef CAPTAIN_BLACK_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	24,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char definition
	CaptainBlackTiles,
};

TextureROMDef CAPTAIN_TX =
{
	(CharSetDefinition*)&CAPTAIN_CH,

	// bgmap definition
	CaptainMap,

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
};

TextureROMDef CAPTAIN_BLACK_TX =
{
	(CharSetDefinition*)&CAPTAIN_BLACK_CH,

	// bgmap definition
	CaptainBlackMap,

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
};

ObjectSpriteROMDef CAPTAIN_SPRITE =
{
	{
		// sprite's type
		__TYPE(ObjectAnimatedSprite),

		// texture definition
		(TextureDefinition*)&CAPTAIN_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, 1},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
	__WORLD_OBJECT,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

ObjectSpriteROMDef CAPTAIN_BLACK_SPRITE =
{
	{
		// sprite's type
		__TYPE(ObjectAnimatedSprite),

		// texture definition
		(TextureDefinition*)&CAPTAIN_BLACK_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, 1},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
	__WORLD_OBJECT,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

ObjectSpriteROMDef* const CAPTAIN_SPRITES[] =
{
	&CAPTAIN_SPRITE,
	&CAPTAIN_BLACK_SPRITE,
	NULL
};

ShapeROMDef CAPTAIN_AC_SHAPES[] =
{
	// standing
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{19, 37, 48},

		// displacement (x, y, z, p)
		{0, 3, -16, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{1, 1, 1},

		// if true this shape checks for collisions against other shapes
		true,

		// layers in which I live
		kPlayerLayer,

		// layers to ignore when checking for collisions
		kParticlesLayer | kPlayerLayer,
	},

	// kneeling
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{19, 28, 48},

		// displacement (x, y, z, p)
		{0, 7, -16, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{1, 1, 1},

		// if true this shape checks for collisions against other shapes
		true,

		// layers in which I live
		kPlayerLayer,

		// layers to ignore when checking for collisions
		kParticlesLayer | kPlayerLayer,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kNoLayer, kNoLayer}
};

PhysicalSpecificationROMDef CAPTAIN_PHYSICAL_PROPERTIES =
{
	// mass
	__F_TO_FIX10_6(0.65f),

	// friction
	__F_TO_FIX10_6(0),

	// bounciness
	__F_TO_FIX10_6(CAPTAIN_BOUNCINESS),

	// maximum velocity
	{__I_TO_FIX10_6(100), __I_TO_FIX10_6(100), __I_TO_FIX10_6(100)}
};

CaptainROMDef CAPTAIN_AC =
{
	{
		{
			// class allocator
			__TYPE(Captain),

			// sprites
			(SpriteROMDef**)CAPTAIN_SPRITES,

			// collision shapes
			(ShapeDefinition*)CAPTAIN_AC_SHAPES,

			// size
			// if 0, width and height will be inferred from the first sprite's texture's size
			{0, 0, 0},

			// gameworld's character's type
			kCaptain,

			// physical specification
			(PhysicalSpecification*)&CAPTAIN_PHYSICAL_PROPERTIES,
		},

		// pointer to the animation definition for the character
		(AnimationDescription*)&CAPTAIN_ANIM,

		// initial animation
		"Idle",
	},

	// true to create a body
	true,

	// axes subject to gravity
	__Y_AXIS
};
