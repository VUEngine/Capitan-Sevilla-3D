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

#include <ObjectAnimatedSprite.h>
#include <Ball.h>
#include <Projectile.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE PillTiles[];
extern BYTE PillMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec PILL_DEFAULT_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{0},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Default",
};

AnimationDescriptionROMSpec PILL_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&PILL_DEFAULT_ANIM,
		NULL,
	}
};

CharSetROMSpec PILL_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	2 * 2,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char spec
	PillTiles,
};

TextureROMSpec PILL_TX =
{
	// charset spec
	(CharSetSpec*)&PILL_CH,

	// bgmap spec
	PillMap,

	// cols (max 64)
	2,

	// rows (max 64)
	2,

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

	// vertical flip
	false,

	// horizontal flip
	false,
};

ObjectSpriteROMSpec PILL_SPRITE =
{
	{
		// sprite's type
		__TYPE(ObjectAnimatedSprite),

		// texture spec
		(TextureSpec*)&PILL_TX,

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

ObjectSpriteROMSpec* const PILL_SPRITES[] =
{
	&PILL_SPRITE,
	NULL
};

ShapeROMSpec PILL_PR_SHAPES[] =
{
	{
		// shape
		__TYPE(Ball),

		// size (x, y, z)
		{16, 16, 16},

		// displacement (x, y, z, p)
		{0, 0, 0, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{__I_TO_FIX7_9(1), __I_TO_FIX7_9(1), __I_TO_FIX7_9(1)},

		// if true this shape checks for collisions against other shapes
		true,

		// layers in which I live
		kEnemiesLayer,

		// layers to ignore when checking for collisions
		kAllLayers & ~kPlayerLayer,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kLayerNone, kLayerNone}
};

ProjectileROMSpec PILL_PR =
{
	// actor
	{
		{
			{
				// class allocator
				__TYPE(Projectile),

				// children
				NULL,

				// behaviors
				NULL,

				// extra
				NULL,
				
				// sprites
				(SpriteSpec**)PILL_SPRITES,

				// use z displacement in projection
				false,

				// collision shapes
				(ShapeSpec*)PILL_PR_SHAPES,

				// size
				// if 0, width and height will be inferred from the first sprite's texture's size
				{0, 0, 0},

				// gameworld's character's type
				kEnemyProjectile,

				// physical specification
				(PhysicalSpecification*)NULL,
			},

			// pointer to the animation spec for the character
			(AnimationDescription*)&PILL_ANIM,

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
    	__F_TO_FIX10_6(-8.0f),
    	0,
    	0,
	},

	// position relative to ejector
    {
    	__PIXELS_TO_METERS(-24),
    	__PIXELS_TO_METERS(2),
    	0,
    },

	// max position relative to ejector before position reset
    {
    	__PIXELS_TO_METERS(216),
    	0,
    	0,
    },

	// delay between position checks (-1 to disable)
	200,
};
