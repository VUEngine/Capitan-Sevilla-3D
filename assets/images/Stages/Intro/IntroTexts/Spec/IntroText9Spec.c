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


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE IntroText9Tiles[];
extern BYTE IntroText9Map[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec INTRO_TEXT_9_ENGLISH_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{1},
	//{0},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"0",
};

AnimationFunctionROMSpec INTRO_TEXT_9_SPANISH_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{1},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"1",
};

AnimationFunctionROMSpec INTRO_TEXT_9_GERMAN_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{1},
	//{2},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"2",
};

AnimationFunctionROMSpec INTRO_TEXT_9_FRENCH_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{1},
	//{3},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"3",
};

AnimationDescriptionROMSpec INTRO_TEXT_9_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&INTRO_TEXT_9_ENGLISH_ANIM,
		(AnimationFunction*)&INTRO_TEXT_9_SPANISH_ANIM,
		(AnimationFunction*)&INTRO_TEXT_9_GERMAN_ANIM,
		(AnimationFunction*)&INTRO_TEXT_9_FRENCH_ANIM,
		NULL,
	}
};

CharSetROMSpec INTRO_TEXT_9_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	48,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char spec
	IntroText9Tiles,
};

TextureROMSpec INTRO_TEXT_9_TX =
{
	// charset spec
	(CharSetSpec*)&INTRO_TEXT_9_CH,

	// bgmap spec
	IntroText9Map,

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
};

BgmapSpriteROMSpec INTRO_TEXT_9_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&INTRO_TEXT_9_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const INTRO_TEXT_9_SPRITES[] =
{
	&INTRO_TEXT_9_SPRITE,
	NULL
};

ActorROMSpec INTRO_TEXT_9_AC =
{
	{
		{
			// class allocator
			__TYPE(Actor),

			// behaviors 
			NULL,

			// sprites
			(SpriteSpec**)INTRO_TEXT_9_SPRITES,

			// collision shapes
			(ShapeSpec*)NULL,

			// size
			// if 0, width and height will be inferred from the first sprite's texture's size
			{0, 0, 0},

			// gameworld's character's type
			kNoType,

			// physical specification
			(PhysicalSpecification*)NULL,
		},

		// pointer to the animation spec for the character
		(AnimationDescription*)&INTRO_TEXT_9_ANIM,

		// initial animation
		"0"
	},

	// true to create a body
	false,

	// axes subject to gravity
	__NO_AXIS,

	// axis around which to rotate the entity when syncronizing with body
	__NO_AXIS
};

