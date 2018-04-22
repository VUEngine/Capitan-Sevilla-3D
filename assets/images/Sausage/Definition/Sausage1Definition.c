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
#include "Sausage.h"


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE Sausage1Tiles[];
extern BYTE Sausage1Map[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMDef SAUSAGE_1_DEFAULT_ANIM =
{
	// number of frames of this animation function
	4,

	// frames to play in animation
	{4, 3, 2, 1},

	// number of cycles a frame of animation is displayed
	6,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Default",
};

// an animation definition
AnimationDescriptionROMDef SAUSAGE_1_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&SAUSAGE_1_DEFAULT_ANIM,
		NULL,
	}
};

CharSetROMDef SAUSAGE_1_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	9,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char definition
	Sausage1Tiles,
};

TextureROMDef SAUSAGE_1_TX =
{
	// charset definition
	(CharSetDefinition*)&SAUSAGE_1_CH,

	// bgmap definition
	Sausage1Map,

	// cols (max 64)
	3,

	// rows (max 64)
	3,

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

ObjectSpriteROMDef SAUSAGE_1_SPRITE =
{
	{
		// sprite's type
		__TYPE(ObjectAnimatedSprite),

		// texture definition
		(TextureDefinition*)&SAUSAGE_1_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
	__WORLD_OBJECT,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

ObjectSpriteROMDef* const SAUSAGE_1_SPRITES[] =
{
	&SAUSAGE_1_SPRITE,
	NULL
};

ShapeROMDef SAUSAGE_1_PR_SHAPES[] =
{
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{16, 16, 128},

		// displacement (x, y, z, p)
		{0, 0, 0, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{__I_TO_FIX7_9(1), __I_TO_FIX7_9(1), __I_TO_FIX7_9(1)},

		// if true this shape checks for collisions against other shapes
		true,

		// layers in which I live
		kEnemiesLayer,

		// layers to ignore when checking for collisions
		kPlayerLayer,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kNoLayer, kNoLayer}
};

ProjectileROMDef SAUSAGE_1_PR =
{
	// actor
	{
		{
			{
				// class allocator
				__TYPE(Sausage),

				// sprites
				(SpriteROMDef**)SAUSAGE_1_SPRITES,

				// collision shapes
				(ShapeDefinition*)SAUSAGE_1_PR_SHAPES,

				// size
				// if 0, width and height will be inferred from the first sprite's texture's size
				{0, 0, 0},

				// gameworld's character's type
				kSausage,

				// physical specification
				(PhysicalSpecification*)NULL,
			},

			// pointer to the animation definition for the character
			(AnimationDescription*)&SAUSAGE_1_ANIM,

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
    	__F_TO_FIX10_6(5.2f),
    	0,
    	0,
	},

	// position relative to ejector
    {
    	0,
    	0,
    	0,
    },

	// max position relative to ejector before position reset
    {
    	0,
    	__PIXELS_TO_METERS(80),
    	0,
    },

	// delay between position checks (-1 to disable)
	-1,
};