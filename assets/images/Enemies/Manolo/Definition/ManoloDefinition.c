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

extern ActorDefinition PILL_PR;
extern BYTE ManoloTiles[];
extern BYTE ManoloMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMDef MANOLO_IDLE_ANIM =
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

AnimationFunctionROMDef MANOLO_SHOOT_ANIM =
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
	(EventListener)&ProjectileEjector_onEjectAnimationComplete,

	// function's name
	"Shoot",
};

AnimationDescriptionROMDef MANOLO_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&MANOLO_IDLE_ANIM,
		(AnimationFunction*)&MANOLO_SHOOT_ANIM,
		NULL,
	}
};

CharSetROMDef MANOLO_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	5 * 7,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char definition
	ManoloTiles,
};

TextureROMDef MANOLO_TX =
{
	// charset definition
	(CharSetDefinition*)&MANOLO_CH,

	// bgmap definition
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
};

ObjectSpriteROMDef MANOLO_SPRITE =
{
	{
		// sprite's type
		__TYPE(ObjectAnimatedSprite),

		// texture definition
		(TextureDefinition*)&MANOLO_TX,

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

ObjectSpriteROMDef* const MANOLO_SPRITES[] =
{
	&MANOLO_SPRITE,
	NULL
};

ShapeROMDef MANOLO_SHAPES[] =
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
		kNoLayer,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kNoLayer, kNoLayer}
};

ProjectileEjectorROMDef PILL_EJECTOR_PE =
{
	// animated entity
	{
		{
			// class allocator
			__TYPE(ProjectileEjector),

			// sprites
			NULL,

			// collision shapes
			NULL,

			// size
			// if 0, width and height will be inferred from the first sprite's texture's size
			{0, 0, 0},

			// gameworld's character's type
			kNoType,

			// physical specification
			(PhysicalSpecification*)NULL,
		},

		// pointer to the animation definition for the character
		NULL,

		// initial animation
		NULL
	},

	// projectile
    {(EntityDefinition*)&PILL_PR, {0, 0, 0, 0}, 0, NULL, NULL, NULL, true},

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

EnemyROMDef MANOLO_EM =
{
	{
		{
			{
				{
					// class allocator
					__TYPE(Enemy),

					// sprites
					(SpriteROMDef**)MANOLO_SPRITES,

					// collision shapes
					(ShapeDefinition*)MANOLO_SHAPES,

					// size
					// if 0, width and height will be inferred from the first sprite's texture's size
					{0, 0, 0},

					// gameworld's character's type
					kEnemy,

					// physical specification
					(PhysicalSpecification*)NULL,
				},

				// pointer to the animation definition for the character
				(AnimationDescription*)&MANOLO_ANIM,

				// initial animation
				"Idle"
			},

			// true to create a body
			true,

			// axes subject to gravity
			__NO_AXIS
		},

		// speed (x axis)
		0,
	},

	// energy
	3,

	// projectile ejector to add
	(ProjectileEjectorDefinition*)&PILL_EJECTOR_PE,

	// relative position of projectile ejector
	{0, 0, 0},
};
