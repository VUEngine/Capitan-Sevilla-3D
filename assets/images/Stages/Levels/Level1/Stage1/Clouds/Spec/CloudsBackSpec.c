/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
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

extern uint32 CloudsTiles[];
extern uint16 CloudsBackMap[];
extern CharSetSpec CloudsCharset;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMSpec CloudsBackTexture =
{
	// charset spec
	(CharSetSpec*)&CloudsCharset,

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

	// vertical flip
	false,

	// horizontal flip
	false,
};

TextureROMSpec* const CloudsBackTextures[] =
{
	(TextureSpec*)&CloudsBackTexture,
	NULL
};

MBgmapSpriteROMSpec CloudsBackSprite =
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
	(TextureSpec**)CloudsBackTextures,

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

BgmapSpriteROMSpec* const CloudsBackSprites[] =
{
	(BgmapSpriteROMSpec*)&CloudsBackSprite,
	NULL
};

MovingOneWayEntityROMSpec CloudsBackEntity =
{
	{
		{
			{
				// class allocator
				__TYPE(MovingOneWayEntity),

				// children
				NULL,

				// behaviors
				NULL,

				// extra
				NULL,
				
				// sprites
				(SpriteSpec**)CloudsBackSprites,

				// use z displacement in projection
				false,
			
				/// meshes
				(MeshSpec*)NULL,

				// collision shapes
				(ShapeSpec*)NULL,

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

