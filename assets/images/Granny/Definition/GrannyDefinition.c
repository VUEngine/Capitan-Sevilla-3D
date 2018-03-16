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

#include <BgmapAnimatedSprite.h>
#include <Actor.h>
#include <macros.h>
#include <ProjectileEjector.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE GrannyTiles[];
extern BYTE GrannyMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMDef GRANNY_1_IDLE_ANIM =
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
	"Idle",
};

AnimationFunctionROMDef GRANNY_1_SHOOT_ANIM =
{
	// number of frames of this animation function
	4,

	// frames to play in animation
	{1, 1, 1, 1},

	// number of cycles a frame of animation is displayed
	16,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)&ProjectileEjector_onShootAnimationComplete,

	// function's name
	"Shoot",
};

// an animation definition
AnimationDescriptionROMDef GRANNY_1_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&GRANNY_1_IDLE_ANIM,
		(AnimationFunction*)&GRANNY_1_SHOOT_ANIM,
		NULL,
	}
};

CharSetROMDef GRANNY_1_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	20,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char definition
	GrannyTiles,
};

TextureROMDef GRANNY_1_TX =
{
	// charset definition
	(CharSetDefinition*)&GRANNY_1_CH,

	// bgmap definition
	GrannyMap,

	// cols (max 64)
	4,

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
};

BgmapSpriteROMDef GRANNY_1_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture definition
		(TextureDefinition*)&GRANNY_1_TX,

		// transparent
		false,

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

BgmapSpriteROMDef* const GRANNY_1_SPRITES[] =
{
	&GRANNY_1_SPRITE,
	NULL
};

ActorROMDef GRANNY_1_AC =
{
	{
		{
			// class allocator
			__TYPE(ProjectileEjector),

			// sprites
			(SpriteROMDef**)GRANNY_1_SPRITES,

			// collision shapes
			(ShapeDefinition*)NULL,

			// size
			// if 0, width and height will be inferred from the first sprite's texture's size
			{0, 0, 0},

			// gameworld's character's type
			kNotShape,

			// physical specification
			(PhysicalSpecification*)NULL,
		},

		// pointer to the animation definition for the character
		(AnimationDescription*)&GRANNY_1_ANIM,

		// initial animation
		"Idle"
	},

	// true to create a body
	false,

	// axes subject to gravity
	__NO_AXIS
};

