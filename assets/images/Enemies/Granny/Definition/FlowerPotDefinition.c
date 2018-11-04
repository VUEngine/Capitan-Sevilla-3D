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
#include "FlowerPot.h"


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE FlowerPotTiles[];
extern BYTE FlowerPotMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMDef FLOWER_POT_DEFAULT_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{0},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Default",
};

AnimationFunctionROMDef FLOWER_POT_BREAK_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{1, 2},

	// number of cycles a frame of animation is displayed
	16,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Break",
};

AnimationDescriptionROMDef FLOWER_POT_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&FLOWER_POT_DEFAULT_ANIM,
		(AnimationFunction*)&FLOWER_POT_BREAK_ANIM,
		NULL,
	}
};

CharSetROMDef FLOWER_POT_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	3 * 2 * 2,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_MULTI,

	// char definition
	FlowerPotTiles,
};

TextureROMDef FLOWER_POT_TX =
{
	// charset definition
	(CharSetDefinition*)&FLOWER_POT_CH,

	// bgmap definition
	FlowerPotMap,

	// cols (max 64)
	2,

	// rows (max 64)
	2,

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	3,

	// palette number (0-3)
	1,

	// recyclable
	true,
};

ObjectSpriteROMDef FLOWER_POT_SPRITE =
{
	{
		// sprite's type
		__TYPE(ObjectAnimatedSprite),

		// texture definition
		(TextureDefinition*)&FLOWER_POT_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, -2},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
	__WORLD_OBJECT,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

ObjectSpriteROMDef* const FLOWER_POT_SPRITES[] =
{
	&FLOWER_POT_SPRITE,
	NULL
};

ShapeROMDef FLOWER_POT_PR_SHAPES[] =
{
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{12, 12, 128},

		// displacement (x, y, z, p)
		{0, 0, 0, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{1, 1, 1},

		// if true this shape checks for collisions against other shapes
		true,

		// layers in which I live
		kEnemiesLayer,

		// layers to ignore when checking for collisions
		kAllLayers & ~kPlayerLayer & ~kSolidLayer,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kNoLayer, kNoLayer}
};

ProjectileROMDef FLOWER_POT_PR =
{
	// actor
	{
		{
			{
				// class allocator
				__TYPE(FlowerPot),

				// sprites
				(SpriteROMDef**)FLOWER_POT_SPRITES,

				// collision shapes
				(ShapeDefinition*)FLOWER_POT_PR_SHAPES,

				// size
				// if 0, width and height will be inferred from the first sprite's texture's size
				{0, 0, 0},

				// gameworld's character's type
				kEnemyProjectile,

				// physical specification
				(PhysicalSpecification*)NULL,
			},

			// pointer to the animation definition for the character
			(AnimationDescription*)&FLOWER_POT_ANIM,

			// initial animation
			"Default",
		},

		// true to create a body
		true,

		// axes subject to gravity
		__NO_AXIS
	},

	// velocity
    {
    	0,
    	__F_TO_FIX10_6(3.2f),
    	0,
	},

	// position relative to ejector
    {
    	0,
    	__PIXELS_TO_METERS(16),
    	0,
    },

	// max position relative to ejector before position reset
    {
    	0,
    	__PIXELS_TO_METERS(192),
    	0,
    },

	// delay between position checks (-1 to disable)
	200,
};