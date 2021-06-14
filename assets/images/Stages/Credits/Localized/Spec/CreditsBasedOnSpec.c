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

#include <BgmapAnimatedSprite.h>
#include <LocalizedEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE CreditsBasedOnTiles[];
extern BYTE CreditsBasedOnMap[];
extern AnimationDescription LOCALIZED_ENTITY_ANIM;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec CREDITS_BASED_ON_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	136,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char spec
	CreditsBasedOnTiles,
};

TextureROMSpec CREDITS_BASED_ON_TX =
{
	// charset spec
	(CharSetSpec*)&CREDITS_BASED_ON_CH,

	// bgmap spec
	CreditsBasedOnMap,

	// cols (max 64)
	34,

	// rows (max 64)
	4,

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

BgmapSpriteROMSpec CREDITS_BASED_ON_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&CREDITS_BASED_ON_TX,

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

BgmapSpriteROMSpec* const CREDITS_BASED_ON_SPRITES[] =
{
	&CREDITS_BASED_ON_SPRITE,
	NULL
};

LocalizedEntityROMSpec CREDITS_BASED_ON_EN =
{
	{
		// class allocator
		__TYPE(LocalizedEntity),

		// children
		NULL,

		// behaviors
		NULL,

		// extra
		NULL,

		// sprites
		(SpriteSpec**)CREDITS_BASED_ON_SPRITES,

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
	},

	// pointer to the animation spec for the character
	(AnimationDescription*)&LOCALIZED_ENTITY_ANIM,

	// initial animation
	"0",
};

