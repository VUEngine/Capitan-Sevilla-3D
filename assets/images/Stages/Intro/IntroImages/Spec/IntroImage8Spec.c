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

#include <Entity.h>
#include <BgmapSprite.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE IntroImage8Map[];
extern CharSetROMSpec INTRO_IMAGES_CH;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMSpec INTRO_IMAGE_8_TX =
{
	// charset spec
	(CharSetSpec*)&INTRO_IMAGES_CH,

	// bgmap spec
	IntroImage8Map,

	// cols (max 64)
	17,

	// rows (max 64)
	10,

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

BgmapSpriteROMSpec INTRO_IMAGE_8_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapSprite),

		// texture spec
		(TextureSpec*)&INTRO_IMAGE_8_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD) (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, 1},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const INTRO_IMAGE_8_SPRITES[] =
{
	&INTRO_IMAGE_8_SPRITE,
	NULL

};

EntityROMSpec INTRO_IMAGE_8_IM =
{
	// class allocator
	__TYPE(Entity),

	// children
	NULL,

	// behaviors
	NULL,

	// extra
	NULL,

	// sprites
	(SpriteSpec**)INTRO_IMAGE_8_SPRITES,

	// use z displacement in projection
	false,

	// collision shapes
	(ShapeSpec*)NULL,

	// size
	// if 0, width and height will be inferred from the first sprite's texture's size
	{0, 0, 0},

	// gameworld's character's type
	kTypeNone,

	// physical specification
	(PhysicalSpecification*)NULL,
};
