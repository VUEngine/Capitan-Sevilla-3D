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
#include <Car.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE Car1Tiles[];
extern BYTE Car1Map[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec CAR_1_MOVE_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{0, 1},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Move",
};

AnimationDescriptionROMSpec CAR_1_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&CAR_1_MOVE_ANIM,
		NULL,
	}
};

CharSetROMSpec CAR_1_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	55,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SHARED_COORDINATED,

	// char spec
	Car1Tiles,
};

TextureROMSpec CAR_1_TX =
{
	(CharSetSpec*)&CAR_1_CH,

	// bgmap spec
	Car1Map,

	// cols (max 64)
	11,

	// rows (max 64)
	5,

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

BgmapSpriteROMSpec CAR_1_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&CAR_1_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, -3, -2},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const CAR_1_SPRITES[] =
{
	&CAR_1_SPRITE,
	NULL
};

MovingOneWayEntityROMSpec CAR_1_AC =
{
	{
		{
			{
				// class allocator
				__TYPE(Car),

				// children
				NULL,

				// behaviors
				NULL,

				// extra
				NULL,

				// sprites
				(SpriteSpec**)CAR_1_SPRITES,

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
			(AnimationDescription*)&CAR_1_ANIM,

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
	__I_TO_FIX10_6(-6),
};
