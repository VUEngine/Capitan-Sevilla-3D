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

#include <libgccvb.h>
#include <BgmapAnimatedSprite.h>
#include <CameraTriggerEntity.h>
#include <Box.h>
#include <InverseBox.h>

#include "Hero.h"


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE HeroTiles[];
extern BYTE HeroBlackTiles[];
extern BYTE HeroMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMDef HERO_IDLE_ANIM =
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

// a function which defines the frames to play
AnimationFunctionROMDef HERO_WALK_ANIM =
{
	// number of frames of this animation function
	4,

	// frames to play in animation
	{0, 1, 2, 1},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Walk",
};

// a function which defines the frames to play
AnimationFunctionROMDef HERO_KNEEL_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{3},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Walk",
};

// a function which defines the frames to play
AnimationFunctionROMDef HERO_JUMP_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{5},

	// number of cycles a frame of animation is displayed
	16,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Jump",
};

// a function which defines the frames to play
AnimationFunctionROMDef HERO_FALL_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{4},

	// number of cycles a frame of animation is displayed
	16,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Fall",
};

// a function which defines the frames to play
AnimationFunctionROMDef HERO_SLIDE_ANIM =
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
	"Slide",
};

// a function which defines the frames to play
AnimationFunctionROMDef HERO_HIT_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{6},

	// number of cycles a frame of animation is displayed
	16,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Hit",
};

// a function which defines the frames to play
AnimationFunctionROMDef HERO_DEAD_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{7},

	// number of cycles a frame of animation is displayed
	16,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Dead",
};

// an animation definition
AnimationDescriptionROMDef HERO_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&HERO_IDLE_ANIM,
		(AnimationFunction*)&HERO_WALK_ANIM,
		(AnimationFunction*)&HERO_KNEEL_ANIM,
		(AnimationFunction*)&HERO_JUMP_ANIM,
		(AnimationFunction*)&HERO_FALL_ANIM,
		(AnimationFunction*)&HERO_SLIDE_ANIM,
		(AnimationFunction*)&HERO_HIT_ANIM,
		(AnimationFunction*)&HERO_DEAD_ANIM,
		NULL,
	}
};

CharSetROMDef HERO_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	24,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char definition
	HeroTiles,
};

CharSetROMDef HERO_BLACK_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	24,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char definition
	HeroBlackTiles,
};

TextureROMDef HERO_TX =
{
	(CharSetDefinition*)&HERO_CH,

	// bgmap definition
	HeroMap,

	// cols (max 64)
	4,

	// rows (max 64)
	6,

	// padding for affine/hbias transformations (cols, rows)
	{1, 1},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	1,

	// palette number (0-3)
	0,

	// recyclable
	false,
};

TextureROMDef HERO_BLACK_TX =
{
	(CharSetDefinition*)&HERO_BLACK_CH,

	// bgmap definition
	HeroMap,

	// cols (max 64)
	4,

	// rows (max 64)
	6,

	// padding for affine/hbias transformations (cols, rows)
	{1, 1},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	1,

	// palette number (0-3)
	1,

	// recyclable
	false,
};

BgmapSpriteROMDef HERO_AFFINE_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture definition
		(TextureDefinition*)&HERO_TX,

		// transparent
		false,

		// displacement
		{0, 0, 0, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
	__WORLD_AFFINE,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMDef HERO_BLACK_AFFINE_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture definition
		(TextureDefinition*)&HERO_BLACK_TX,

		// transparent
		false,

		// displacement
		{0, 0, 0, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
	__WORLD_AFFINE,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMDef* const HERO_AFFINE_SPRITES[] =
{
	&HERO_BLACK_AFFINE_SPRITE,
	&HERO_AFFINE_SPRITE,
	NULL
};

ShapeROMDef HERO_AC_SHAPES[] =
{
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{19, 37, 32},

		// displacement (x, y, z, p)
		{0, -3, -16, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{__I_TO_FIX7_9(1), __I_TO_FIX7_9(1), __I_TO_FIX7_9(1)},

		// if true this shape checks for collisions against other shapes
		true,

		// layers in which I live
		kPlayerLayer,

		// layers to ignore when checking for collisions
		kParticlesLayer,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kNoLayer, kNoLayer}
};

PhysicalSpecificationROMDef HERO_PHYSICAL_PROPERTIES =
{
	// mass
	__F_TO_FIX10_6(0.65f),

	// friction
	__F_TO_FIX10_6(0),

	// elasticity
	__F_TO_FIX10_6(HERO_ELASTICITY),
};

HeroROMDef HERO_AC =
{
	{
		{
			// class allocator
			__TYPE(Hero),

			// sprites
			(SpriteROMDef**)HERO_AFFINE_SPRITES,

			// collision shapes
			(ShapeDefinition*)HERO_AC_SHAPES,

			// size
			// if 0, width and height will be inferred from the first sprite's texture's size
			{0, 0, 0},

			// gameworld's character's type
			kHero,

			// physical specification
			(PhysicalSpecification*)&HERO_PHYSICAL_PROPERTIES,
		},

		// pointer to the animation definition for the character
		(AnimationDescription*)&HERO_ANIM,

		// initial animation
		"Idle",
	},

	// true to create a body
	true,

	// axes subject to gravity
	__Y_AXIS
};

ShapeROMDef CAMERA_BOUNDING_BOX_IG_SHAPES[] =
{
	{
		// shape
		__TYPE(InverseBox),

		// size (x, y, z)
		{16 * 8, 24 * 8, 4 * 8},

		// displacement (x, y, z, p)
		{0, 0, 0, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{0, 0, 0},

		// if true this shape checks for collisions against other shapes
		false,

		// layers in which I live
		kTriggersLayer,

		// layers to ignore when checking for collisions
		kAllLayers,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kNoLayer, kNoLayer}
};


CameraTriggerEntityROMDef CAMERA_BOUNDING_BOX_IG =
{
	// class allocator
	__TYPE(CameraTriggerEntity),

	// sprites
	(SpriteROMDef**)NULL,

	// collision shapes
	(ShapeDefinition*)CAMERA_BOUNDING_BOX_IG_SHAPES,

	// size
	// if 0, width and height will be inferred from the first sprite's texture's size
	{0, 0, 0},

	// gameworld's character's type
	kCameraTarget,

	// physical specification
	(PhysicalSpecification*)NULL,
};
