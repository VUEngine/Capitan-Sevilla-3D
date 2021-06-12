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
#include <Punk.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE PunkTiles[];
extern BYTE PunkBlackTiles[];
extern BYTE PunkMap[];
extern BYTE PunkBlackMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec PUNK_MOVE_ANIM =
{
	// number of frames of this animation function
	12,

	// frames to play in animation
	{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Move",
};

AnimationFunctionROMSpec PUNK_DIE_ANIM =
{
	// number of frames of this animation function
	38,

	// frames to play in animation
	{12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
	 22, 22,
	 23, 24, 25, 26, 27, 28, 29, 30,
	 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,
	 31, 32, 33, 34, 35},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)&Punk_onDieAnimationComplete,

	// function's name
	"Die",
};

AnimationDescriptionROMSpec PUNK_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&PUNK_MOVE_ANIM,
		(AnimationFunction*)&PUNK_DIE_ANIM,
		NULL,
	}
};

CharSetROMSpec PUNK_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	8*6,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SHARED_COORDINATED,

	// char spec
	PunkTiles,
};

CharSetROMSpec PUNK_BLACK_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	8*6,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SHARED_COORDINATED,

	// char spec
	PunkBlackTiles,
};

TextureROMSpec PUNK_TX =
{
	(CharSetSpec*)&PUNK_CH,

	// bgmap spec
	PunkMap,

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
	0,

	// recyclable
	false,

	// vertical flip
	false,

	// horizontal flip
	false,
};

TextureROMSpec PUNK_BLACK_TX =
{
	(CharSetSpec*)&PUNK_BLACK_CH,

	// bgmap spec
	PunkBlackMap,

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

	// vertical flip
	false,

	// horizontal flip
	false,
};

BgmapSpriteROMSpec PUNK_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&PUNK_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 1, 2},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or BgmapSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec PUNK_BLACK_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&PUNK_BLACK_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 1, 2},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or BgmapSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const PUNK_SPRITES[] =
{
	&PUNK_SPRITE,
	&PUNK_BLACK_SPRITE,
	NULL
};

ShapeROMSpec PUNK_SHAPES[] =
{
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{16, 38, 24},

		// displacement (x, y, z, p)
		{11, 1, 0, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{0, 0, 0},

		// if true this shape checks for collisions against other shapes
		false,

		// layers in which I live
		kEnemiesLayer,

		// layers to ignore when checking for collisions
		kLayerNone,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kLayerNone, kLayerNone}
};

EnemyROMSpec PUNK_EM =
{
	{
		{
			{
				{
					// class allocator
					__TYPE(Punk),

					// children
					NULL,

					// behaviors
					NULL,

					// extra
					NULL,
					
					// sprites
					(SpriteSpec**)PUNK_SPRITES,

					// use z displacement in projection
					false,

					// collision shapes
					(ShapeSpec*)PUNK_SHAPES,

					// size
					// if 0, width and height will be inferred from the first sprite's texture's size
					{0, 0, 0},

					// gameworld's character's type
					kEnemy,

					// physical specification
					(PhysicalSpecification*)NULL,
				},

				// pointer to the animation spec for the character
				(AnimationDescription*)&PUNK_ANIM,

				// initial animation
				"Move",
			},

			// true to create a body
			true,

			// axes subject to gravity
			__NO_AXIS,

			// axis around which to rotate the entity when syncronizing with body
			__Y_AXIS
		},

		// speed (x axis)
		__I_TO_FIX10_6(-3),
	},

	// energy
	2,

	// projectile ejector to add
	NULL,

	// relative position of projectile ejector
	{0, 0, 0},

	// respawn
	true
};
