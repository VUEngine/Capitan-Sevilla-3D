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
#include <Box.h>
#include <Lift.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE Level1Stage2LiftTiles[];
extern BYTE Level1Stage2LiftMap[];
extern StageEntryPointSpec LEVEL_1_STAGE_3_MAIN_EP;
extern StageEntryPointSpec LEVEL_1_STAGE_4_MAIN_EP;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec LEVEL_1_STAGE_2_LIFT_OPEN_ANIM =
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

AnimationFunctionROMSpec LEVEL_1_STAGE_2_LIFT_CLOSED_ANIM =
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

AnimationFunctionROMSpec LEVEL_1_STAGE_2_LIFT_BROKEN_ANIM =
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

AnimationDescriptionROMSpec LEVEL_1_STAGE_2_LIFT_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&LEVEL_1_STAGE_2_LIFT_OPEN_ANIM,
		(AnimationFunction*)&LEVEL_1_STAGE_2_LIFT_CLOSED_ANIM,
		(AnimationFunction*)&LEVEL_1_STAGE_2_LIFT_BROKEN_ANIM,
		NULL,
	}
};

CharSetROMSpec LEVEL_1_STAGE_2_LIFT_CH =
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
};

TextureROMSpec LEVEL_1_STAGE_2_LIFT_TX =
{
	(CharSetSpec*)&LEVEL_1_STAGE_2_LIFT_CH,

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

BgmapSpriteROMSpec LEVEL_1_STAGE_2_LIFT_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&LEVEL_1_STAGE_2_LIFT_TX,

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

BgmapSpriteROMSpec* const LEVEL_1_STAGE_2_LIFT_SPRITES[] =
{
	&LEVEL_1_STAGE_2_LIFT_SPRITE,
	NULL
};

ShapeROMSpec LEVEL_1_STAGE_2_LIFT_SHAPES[] =
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
		kLayerNone,
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
		kLayerNone,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kLayerNone, kLayerNone}
};

LiftROMSpec LEVEL_1_STAGE_2_LIFT_EN =
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
				(SpriteSpec**)LEVEL_1_STAGE_2_LIFT_SPRITES,

				// use z displacement in projection
				false,

				// collision shapes
				(ShapeSpec*)LEVEL_1_STAGE_2_LIFT_SHAPES,

				// size
				// if 0, width and height will be inferred from the first sprite's texture's size
				{0, 0, 0},

				// gameworld's character's type
				kLift,

				// physical specification
				(PhysicalSpecification*)NULL,
			},

			// pointer to the animation spec for the character
			(AnimationDescription*)&LEVEL_1_STAGE_2_LIFT_ANIM,

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
	{0, __I_TO_FIX10_6(-2), 0},

	// entry point to load after entering
	(StageEntryPointSpec*)&LEVEL_1_STAGE_3_MAIN_EP,
};

LiftROMSpec LEVEL_1_STAGE_3_LIFT_EN =
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
				(SpriteSpec**)LEVEL_1_STAGE_2_LIFT_SPRITES,

				// use z displacement in projection
				false,

				// collision shapes
				(ShapeSpec*)LEVEL_1_STAGE_2_LIFT_SHAPES,

				// size
				// if 0, width and height will be inferred from the first sprite's texture's size
				{0, 0, 0},

				// gameworld's character's type
				kLift,

				// physical specification
				(PhysicalSpecification*)NULL,
			},

			// pointer to the animation spec for the character
			(AnimationDescription*)&LEVEL_1_STAGE_2_LIFT_ANIM,

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
	(StageEntryPointSpec*)&LEVEL_1_STAGE_4_MAIN_EP,
};

AnimatedEntityROMSpec LEVEL_1_STAGE_4_LIFT_EN =
{
	{
		// class allocator
		__TYPE(AnimatedEntity),

		// children
		NULL,

		// behaviors
		NULL,

		// extra
		NULL,

		// sprites
		(SpriteSpec**)LEVEL_1_STAGE_2_LIFT_SPRITES,

		// use z displacement in projection
		false,

		// collision shapes
		NULL,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kTypeNone,

		// physical specification
		NULL,
	},

	// pointer to the animation spec for the character
	(AnimationDescription*)&LEVEL_1_STAGE_2_LIFT_ANIM,

	// initial animation
	"Broken"
};
