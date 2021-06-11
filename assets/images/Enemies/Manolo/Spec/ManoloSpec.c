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
#include <macros.h>
#include <ProjectileEjector.h>
#include <Enemy.h>
#include <Box.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern ActorSpec PILL_PR;
extern BYTE ManoloTiles[];
extern BYTE ManoloMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec MANOLO_IDLE_ANIM =
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
	"Idle",
};

AnimationFunctionROMSpec MANOLO_SHOOT_ANIM =
{
	// number of frames of this animation function
	6,

	// frames to play in animation
	{1, 2, 1, 2, 1, 2},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)&Enemy_onEjectAnimationComplete,

	// function's name
	"Shoot",
};

AnimationDescriptionROMSpec MANOLO_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&MANOLO_IDLE_ANIM,
		(AnimationFunction*)&MANOLO_SHOOT_ANIM,
		NULL,
	}
};

CharSetROMSpec MANOLO_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	5 * 7,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char spec
	ManoloTiles,
};

TextureROMSpec MANOLO_TX =
{
	// charset spec
	(CharSetSpec*)&MANOLO_CH,

	// bgmap spec
	ManoloMap,

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

ObjectSpriteROMSpec MANOLO_SPRITE =
{
	{
		// sprite's type
		__TYPE(ObjectAnimatedSprite),

		// texture spec
		(TextureSpec*)&MANOLO_TX,

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

ObjectSpriteROMSpec* const MANOLO_SPRITES[] =
{
	&MANOLO_SPRITE,
	NULL
};

ShapeROMSpec MANOLO_SHAPES[] =
{
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{18, 48, 24},

		// displacement (x, y, z, p)
		{-3, 4, 0, 0},

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

ProjectileEjectorROMSpec PILL_EJECTOR_PE =
{
	// animated entity
	{
		{
			// class allocator
			__TYPE(ProjectileEjector),

			// children
			NULL,

			// behaviors
			NULL,

			// extra
			NULL,
			
			// sprites
			NULL,

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
			(PhysicalSpecification*)NULL,
		},

		// pointer to the animation spec for the character
		NULL,

		// initial animation
		NULL
	},

	// projectile
    {(EntitySpec*)&PILL_PR, {0, 0, 0, 0}, 0, NULL, NULL, NULL, true},

	// delay of the first projectile ejection (only relevant if initially active)
	800,

	// pause between projectile ejections
	1500,

	// whether the ejector should be active on creation
	true,

	// maximum number of projectiles on screen at the same time
	1,

	// name of animation to play on projectile ejection
	NULL,

	// name of animation to play when idle
	NULL,
};

EnemyROMSpec MANOLO_EM =
{
	{
		{
			{
				{
					// class allocator
					__TYPE(Enemy),

					// children
					NULL,

					// behaviors
					NULL,

					// extra
					NULL,

					// sprites
					(SpriteSpec**)MANOLO_SPRITES,

					// use z displacement in projection
					false,

					// collision shapes
					(ShapeSpec*)MANOLO_SHAPES,

					// size
					// if 0, width and height will be inferred from the first sprite's texture's size
					{0, 0, 0},

					// gameworld's character's type
					kEnemy,

					// physical specification
					(PhysicalSpecification*)NULL,
				},

				// pointer to the animation spec for the character
				(AnimationDescription*)&MANOLO_ANIM,

				// initial animation
				"Idle"
			},

			// true to create a body
			true,

			// axes subject to gravity
			__NO_AXIS,

			// axis around which to rotate the entity when syncronizing with body
			__Y_AXIS
		},

		// speed (x axis)
		0,
	},

	// energy
	3,

	// projectile ejector to add
	(ProjectileEjectorSpec*)&PILL_EJECTOR_PE,

	// relative position of projectile ejector
	{0, 0, 0},

	// respawn
	true
};
