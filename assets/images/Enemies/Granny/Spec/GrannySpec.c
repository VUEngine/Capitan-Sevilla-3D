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
#include <macros.h>
#include <ProjectileEjector.h>
#include <Actor.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern ActorSpec FlowerPotPr;
extern BYTE GrannyTiles[];
extern BYTE GrannyMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec GrannyIdleAnimation =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{0},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Idle",
};

AnimationFunctionROMSpec GrannyShootAnimation =
{
	// number of frames of this animation function
	4,

	// frames to play in animation
	{1, 1, 1, 1},

	// number of cycles a frame of animation is displayed
	16,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)&ProjectileEjector_onEjectAnimationComplete,

	// function's name
	"Shoot",
};

AnimationDescriptionROMSpec GrannyAnimation =
{
	// animation functions
	{
		(AnimationFunction*)&GrannyIdleAnimation,
		(AnimationFunction*)&GrannyShootAnimation,
		NULL,
	}
};

CharSetROMSpec GrannyCharset =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	20,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char spec
	GrannyTiles,
};

TextureROMSpec GrannyTexture =
{
	// charset spec
	(CharSetSpec*)&GrannyCharset,

	// bgmap spec
	GrannyMap,

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

ObjectSpriteROMSpec GrannySprite =
{
	{
		// sprite's type
		__TYPE(ObjectAnimatedSprite),

		// texture spec
		(TextureSpec*)&GrannyTexture,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 2, 3},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_OBJECT,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

ObjectSpriteROMSpec* const GrannySprites[] =
{
	&GrannySprite,
	NULL
};

ProjectileEjectorROMSpec GrannyPe =
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
			(SpriteSpec**)GrannySprites,

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
		(AnimationDescription*)&GrannyAnimation,

		// initial animation
		"Idle"
	},

	// projectile
    {(EntitySpec*)&FlowerPotPr, {0, 0, 0, 0}, 0, NULL, NULL, NULL, true},

	// delay of the first projectile ejection (only relevant if initially active)
	1500,

	// pause between projectile ejections
	2800,

	// whether the ejector should be active on creation
	true,

	// maximum number of projectiles on screen at the same time
	1,

	// name of animation to play on projectile ejection
	"Shoot",

	// name of animation to play when idle
	"Idle",
};
