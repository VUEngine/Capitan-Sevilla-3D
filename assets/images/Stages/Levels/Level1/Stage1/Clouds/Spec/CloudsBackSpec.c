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

#include <MovingOneWayEntity.h>
#include <MBgmapSprite.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE CloudsTiles[];
extern BYTE CloudsBackMap[];
extern CharSetSpec CLOUDS_CH;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMSpec CLOUDS_BACK_TX =
{
	// charset spec
	(CharSetSpec*)&CLOUDS_CH,

	// bgmap spec
	CloudsBackMap,

	// cols (max 64)
	64,

	// rows (max 64)
	2,

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
};

TextureROMSpec* const CLOUDS_BACK_TEXTURES[] =
{
	(TextureSpec*)&CLOUDS_BACK_TX,
	NULL
};

MBgmapSpriteROMSpec CLOUDS_BACK_SPRITE =
{
	{
		{
			// sprite's type
			__TYPE(MBgmapSprite),

			// texture spec
			NULL,

			// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
			false,

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
	},

	// textures
	(TextureSpec**)CLOUDS_BACK_TEXTURES,

	// SCX/SCY (__WORLD_1x1, 1x2, 1x4, 1x8, 2x1, 2x2, 2x4, 4x1, 4x2, or 8x1)
	// textures must be 64x64 for anything other than 1x1
	__WORLD_1x1,

	// x loop
	true,

	// y loop
	false,

	// bounds the sprite's width to provide culling
	// if 0, the value is inferred from the texture
	0,

	// bounds the sprite's height to provide culling
	// if 0, the value is inferred from the texture
	0,
};

BgmapSpriteROMSpec* const CLOUDS_BACK_SPRITES[] =
{
	(BgmapSpriteROMSpec*)&CLOUDS_BACK_SPRITE,
	NULL
};

MovingOneWayEntityROMSpec CLOUDS_BACK_EN =
{
	{
		{
			{
				// class allocator
				__TYPE(MovingOneWayEntity),

				// behaviors 
				NULL,

				// sprites
				(SpriteSpec**)CLOUDS_BACK_SPRITES,

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
			NULL,

			// initial animation
			NULL,
		},

		// true to create a body
		true,

		// axes subject to gravity
		__NO_AXIS,

		// axis around which to rotate the entity when syncronizing with body
		__NO_AXIS
	},

	// speed (x axis)
	__F_TO_FIX10_6(-0.5f),
};

