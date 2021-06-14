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

#include <Libgccvb.h>
#include <AnimatedEntity.h>
#include <Dust.h>
#include <ObjectAnimatedSprite.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE LandDustTiles[];
extern BYTE LandDustMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec LAND_DUST_HIDDEN_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{5},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Hidden",
};

AnimationFunctionROMSpec LAND_DUST_SHOW_ANIM =
{
	// number of frames of this animation function
	6,

	// frames to play in animation
	{0, 1, 2, 3, 4, 5},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)&Dust_onShowAnimationComplete,

	// function's name
	"Show",
};

AnimationDescriptionROMSpec LAND_DUST_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&LAND_DUST_HIDDEN_ANIM,
		(AnimationFunction*)&LAND_DUST_SHOW_ANIM,
		NULL,
	}
};

CharSetROMSpec LAND_DUST_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	5,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char definition
	LandDustTiles,
};

TextureROMSpec LAND_DUST_TX =
{
	// charset definition
	(CharSetSpec*)&LAND_DUST_CH,

	// bgmap definition
	LandDustMap,

	// cols (max 64)
	5,

	// rows (max 64)
	1,

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

ObjectSpriteROMSpec LAND_DUST_SPRITE =
{
	{
		// sprite's type
		__TYPE(ObjectAnimatedSprite),

		// texture definition
		(TextureSpec*)&LAND_DUST_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, 2},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
	__WORLD_OBJECT,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

ObjectSpriteROMSpec* const LAND_DUST_SPRITES[] =
{
	&LAND_DUST_SPRITE,
	NULL
};

AnimatedEntityROMSpec LAND_DUST_EN =
{
	{
		// class allocator
		__TYPE(Dust),

		// children
		NULL,

		// behaviors
		NULL,

		// extra
		NULL,

		// sprites
		(SpriteSpec**)LAND_DUST_SPRITES,

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

	// pointer to the animation definition for the item
	(AnimationDescription*)&LAND_DUST_ANIM,

	// initial animation
	"Hidden",
};
