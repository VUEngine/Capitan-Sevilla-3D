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
#include <ProjectileEjector.h>
#include <Actor.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern ActorSpec GUM_PROJECTILE_PR;
extern BYTE CaptainHeadTiles[];
extern BYTE CaptainHeadBlackTiles[];
extern BYTE CaptainHeadMap[];
extern BYTE CaptainHeadBlackMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec CAPTAIN_HEAD_IDLE_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{0},

	// number of cycles a frame of animation is displayed
	16,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Idle",
};

AnimationFunctionROMSpec CAPTAIN_HEAD_SPIT_ANIM =
{
	// number of frames of this animation function
	4,

	// frames to play in animation
	{1, 2, 3, 4},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)&ProjectileEjector_onEjectAnimationComplete,

	// function's name
	"Spit",
};

AnimationDescriptionROMSpec CAPTAIN_HEAD_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&CAPTAIN_HEAD_IDLE_ANIM,
		(AnimationFunction*)&CAPTAIN_HEAD_SPIT_ANIM,
		NULL,
	}
};

CharSetROMSpec CAPTAIN_HEAD_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	4,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char spec
	CaptainHeadTiles,
};

CharSetROMSpec CAPTAIN_HEAD_BLACK_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	4,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char spec
	CaptainHeadBlackTiles,
};

TextureROMSpec CAPTAIN_HEAD_TX =
{
	(CharSetSpec*)&CAPTAIN_HEAD_CH,

	// bgmap spec
	CaptainHeadMap,

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
	0,

	// recyclable
	false,

	// vertical flip
	false,

	// horizontal flip
	false,
};

TextureROMSpec CAPTAIN_HEAD_BLACK_TX =
{
	(CharSetSpec*)&CAPTAIN_HEAD_BLACK_CH,

	// bgmap spec
	CaptainHeadBlackMap,

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
	false,

	// vertical flip
	false,

	// horizontal flip
	false,
};

ObjectSpriteROMSpec CAPTAIN_HEAD_SPRITE =
{
	{
		// sprite's type
		__TYPE(ObjectAnimatedSprite),

		// texture spec
		(TextureSpec*)&CAPTAIN_HEAD_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, -2, 2},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_OBJECT,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

ObjectSpriteROMSpec CAPTAIN_HEAD_BLACK_SPRITE =
{
	{
		// sprite's type
		__TYPE(ObjectAnimatedSprite),

		// texture spec
		(TextureSpec*)&CAPTAIN_HEAD_BLACK_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, -1, 2},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_OBJECT,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

ObjectSpriteROMSpec* const CAPTAIN_HEAD_SPRITES[] =
{
	&CAPTAIN_HEAD_SPRITE,
	&CAPTAIN_HEAD_BLACK_SPRITE,
	NULL
};

ProjectileEjectorROMSpec CAPTAIN_HEAD_PE =
{
	// animated entity
	{
		{
			// class allocator
			__TYPE(ProjectileEjector),

			// children
			NULL,

			// behaviors
			NULL,

			// extra
			NULL,
			
			// sprites
			(SpriteSpec**)CAPTAIN_HEAD_SPRITES,

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
		(AnimationDescription*)&CAPTAIN_HEAD_ANIM,

		// initial animation
		"Idle",
	},

	// projectile
    {(EntitySpec*)&GUM_PROJECTILE_PR, {0, 0, 0, 0}, 0, NULL, NULL, NULL, true},

	// delay of the first projectile ejection (only relevant if initially active)
	0,

	// pause between projectile ejections
	1000,

	// whether the ejector should be active on creation
	false,

	// maximum number of projectiles on screen at the same time
	4,

	// name of animation to play on projectile ejection
	"Spit",

	// name of animation to play when idle
	"Idle",
};
