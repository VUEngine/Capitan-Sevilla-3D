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
#include <Box.h>
#include <ItemSausage.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE ItemSausageTiles[];
extern BYTE ItemSausageMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec ItemSausageDefaultAnimation =
{
	// number of frames of this animation function
	16,

	// frames to play in animation
	{0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Default",
};

AnimationFunctionROMSpec ItemSausageTakenAnimation =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{7},

	// number of cycles a frame of animation is displayed
	64,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)&ItemSausage_onTakenAnimationComplete,

	// function's name
	"Taken",
};

AnimationDescriptionROMSpec ItemSausageAnimation =
{
	// animation functions
	{
		(AnimationFunction*)&ItemSausageDefaultAnimation,
		(AnimationFunction*)&ItemSausageTakenAnimation,
		NULL,
	}
};

CharSetROMSpec ItemSausageCharset =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	4 * 5,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char spec
	ItemSausageTiles,
};

TextureROMSpec ItemSausageTexture =
{
	(CharSetSpec*)&ItemSausageCharset,

	// bgmap spec
	ItemSausageMap,

	// cols (max 64)
	4,

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

ObjectSpriteROMSpec ItemSausageSprite =
{
	{
		// sprite's type
		__TYPE(ObjectAnimatedSprite),

		// texture spec
		(TextureSpec*)&ItemSausageTexture,

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

ObjectSpriteROMSpec* const ItemSausageSprites[] =
{
	&ItemSausageSprite,
	NULL
};

ShapeROMSpec ItemSausageShapes[] =
{
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{28, 34, 16},

		// displacement (x, y, z, p)
		{2, 3, 0, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{0, 0, 0},

		// if true this shape checks for collisions against other shapes
		false,

		// layers in which I live
		kItemsLayer,

		// layers to ignore when checking for collisions
		kAllLayers,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kLayerNone, kLayerNone}
};

AnimatedEntityROMSpec ItemSausageEntity =
{
	{
		// class allocator
		__TYPE(ItemSausage),

		// children
		NULL,

		// behaviors
		NULL,

		// extra
		NULL,
		
		// sprites
		(SpriteSpec**)ItemSausageSprites,

		// use z displacement in projection
		false,

		// collision shapes
		(ShapeSpec*)ItemSausageShapes,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kItemDuck,

		// physical specification
		(PhysicalSpecification*)NULL,
	},

	// pointer to the animation spec for the character
	(AnimationDescription*)&ItemSausageAnimation,

	// initial animation
	"Default",
};
