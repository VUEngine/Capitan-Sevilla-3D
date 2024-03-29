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

#include <Mission.h>
#include <BgmapAnimatedSprite.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern uint32 Level1MissionTiles[];
extern uint16 Level1MissionMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec Level1MissionEnglishAnimation =
{
	// number of frames of this animation function
	29,

	// frames to play in animation
	{
		0, 3, 2, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 2, 3, 0,
	},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)&Mission_delete,

	// function's name
	"0",
};

AnimationFunctionROMSpec Level1MissionSpanishAnimation =
{
	// number of frames of this animation function
	38,

	// frames to play in animation
	{
		0, 6, 5, 4,
		4, 4, 4, 4, 4, 4, 4, 4, 4,
		4, 4, 4, 4, 4, 4, 4, 4, 4,
		4, 4, 4, 4, 4, 4, 4, 4, 4,
		4, 5, 6, 0,
	},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)&Mission_delete,

	// function's name
	"1",
};
AnimationFunctionROMSpec Level1MissionGermanAnimation =
{
	// number of frames of this animation function
	38,

	// frames to play in animation
	{
		0, 9, 8, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 8, 9, 0,
	},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)&Mission_delete,

	// function's name
	"2",
};

AnimationFunctionROMSpec Level1MissionFrenchAnimation =
{
	// number of frames of this animation function
	38,

	// frames to play in animation
	{
		 0, 12, 11, 10,
		10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
		10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
		10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
		10, 11, 12, 0,
	},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)&Mission_delete,

	// function's name
	"3",
};

AnimationFunctionROMSpec Level1MissionTransparentAnimation =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{
		0,
	},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Transparent",
};

AnimationDescriptionROMSpec Level1MissionAnimation =
{
	// animation functions
	{
		(AnimationFunction*)&Level1MissionEnglishAnimation,
		(AnimationFunction*)&Level1MissionSpanishAnimation,
		(AnimationFunction*)&Level1MissionGermanAnimation,
		(AnimationFunction*)&Level1MissionFrenchAnimation,
		(AnimationFunction*)&Level1MissionTransparentAnimation,
		NULL,
	}
};

CharSetROMSpec Level1MissionCharset =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	26,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char spec
	Level1MissionTiles,

	// pointer to the frames offsets
	NULL,
};

TextureROMSpec Level1MissionTexture =
{
	// charset definition
	(CharSetSpec*)&Level1MissionCharset,

	// bgmap definition
	Level1MissionMap,

	// cols (max 64)
	13,

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

BgmapSpriteROMSpec Level1MissionSprite =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture definition
		(TextureSpec*)&Level1MissionTexture,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const Level1MissionSprites[] =
{
	&Level1MissionSprite,
	NULL
};

MissionROMSpec Level1MissionEntity =
{
	{
		// class allocator
		__TYPE(Mission),

		// children
		NULL,

		// behaviors
		NULL,

		// extra
		NULL,

		// sprites
		(SpriteSpec**)Level1MissionSprites,

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
		0,

		// physical specification
		(PhysicalSpecification*)NULL,
	},

	// pointer to the animation definition for the item
	(AnimationDescription*)&Level1MissionAnimation,

	// initial animation
	"Transparent",
};
