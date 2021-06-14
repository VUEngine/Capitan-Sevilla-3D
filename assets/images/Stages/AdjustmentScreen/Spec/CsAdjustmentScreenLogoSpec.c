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


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE CsAdjustmentScreenLogoTiles[];
extern BYTE CsAdjustmentScreenLogoMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec CS_ADJUSTMENT_SCREEN_LOGO_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	45,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__NOT_ANIMATED,

	// char spec
	CsAdjustmentScreenLogoTiles,
};

TextureROMSpec CS_ADJUSTMENT_SCREEN_LOGO_TX =
{
	// charset spec
	(CharSetSpec*)&CS_ADJUSTMENT_SCREEN_LOGO_CH,

	// bgmap spec
	CsAdjustmentScreenLogoMap,

	// cols (max 64)
	21,

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

BgmapSpriteROMSpec CS_ADJUSTMENT_SCREEN_LOGO_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapSprite),

		// texture spec
		(TextureSpec*)&CS_ADJUSTMENT_SCREEN_LOGO_TX,

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

BgmapSpriteROMSpec* const CS_ADJUSTMENT_SCREEN_LOGO_SPRITES[] =
{
	&CS_ADJUSTMENT_SCREEN_LOGO_SPRITE,
	NULL
};

EntityROMSpec CS_ADJUSTMENT_SCREEN_LOGO_EN =
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
	(SpriteSpec**)CS_ADJUSTMENT_SCREEN_LOGO_SPRITES,

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
