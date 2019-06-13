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
#include <Ball.h>
#include "GumProjectile.h"


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE GumProjectileTiles[];
extern BYTE GumProjectileMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec GUM_PROJECTILE_DEFAULT_ANIM =
{
	// number of frames of this animation function
	4,

	// frames to play in animation
	{0, 1, 2, 3},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Default",
};

AnimationFunctionROMSpec GUM_PROJECTILE_HIT_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{4},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)&Projectile_onHitAnimationComplete,

	// function's name
	"Hit",
};

AnimationDescriptionROMSpec GUM_PROJECTILE_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&GUM_PROJECTILE_DEFAULT_ANIM,
		(AnimationFunction*)&GUM_PROJECTILE_HIT_ANIM,
		NULL,
	}
};

CharSetROMSpec GUM_PROJECTILE_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	3 * 3,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char spec
	GumProjectileTiles,
};

TextureROMSpec GUM_PROJECTILE_TX =
{
	// charset spec
	(CharSetSpec*)&GUM_PROJECTILE_CH,

	// bgmap spec
	GumProjectileMap,

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
	true,
};

ObjectSpriteROMSpec GUM_PROJECTILE_SPRITE =
{
	{
		// sprite's type
		__TYPE(ObjectAnimatedSprite),

		// texture spec
		(TextureSpec*)&GUM_PROJECTILE_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, 1},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_OBJECT,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

ObjectSpriteROMSpec* const GUM_PROJECTILE_SPRITES[] =
{
	&GUM_PROJECTILE_SPRITE,
	NULL
};

ShapeROMSpec GUM_PROJECTILE_SHAPES[] =
{
	{
		// shape
		__TYPE(Ball),

		// size (x, y, z)
		{8, 8, 16},

		// displacement (x, y, z, p)
		{0, 0, 0, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{1, 1, 1},

		// if true this shape checks for collisions against other shapes
		true,

		// layers in which I live
		kPlayerLayer,

		// layers to ignore when checking for collisions
		kAllLayers & ~kEnemiesLayer,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kNoLayer, kNoLayer}
};

ProjectileROMSpec GUM_PROJECTILE_PR =
{
	// actor
	{
		{
			{
				// class allocator
				__TYPE(GumProjectile),

				// behaviors 
				NULL,

				// sprites
				(SpriteSpec**)GUM_PROJECTILE_SPRITES,

				// collision shapes
				(ShapeSpec*)GUM_PROJECTILE_SHAPES,

				// size
				// if 0, width and height will be inferred from the first sprite's texture's size
				{0, 0, 0},

				// gameworld's character's type
				kGumProjectile,

				// physical specification
				(PhysicalSpecification*)NULL,
			},

			// pointer to the animation spec for the character
			(AnimationDescription*)&GUM_PROJECTILE_ANIM,

			// initial animation
			"Default",
		},

		// true to create a body
		true,

		// axes subject to gravity
		__NO_AXIS,

		// axis around which to rotate the entity when syncronizing with body
		__Y_AXIS
	},

	// velocity
    {
    	__F_TO_FIX10_6(8.0f),
    	0,
    	0,
	},

	// position relative to ejector
    {
    	__PIXELS_TO_METERS(8),
    	__PIXELS_TO_METERS(1),
    	0,
    },

	// max offset relative to ejector before position reset
    {
    	__PIXELS_TO_METERS(256),
    	0,
    	0,
    },

	// delay between position checks (-1 to disable)
	200,
};
