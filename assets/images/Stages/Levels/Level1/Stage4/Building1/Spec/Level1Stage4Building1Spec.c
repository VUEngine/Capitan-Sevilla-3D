/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Entity.h>
#include <BgmapSprite.h>
#include <Box.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE Level1Stage4Building1Tiles[];
extern BYTE Level1Stage4Building1LMap[];
extern BYTE Level1Stage4Building1RMap[];
extern BYTE Level1Stage4Building1BlackMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec LEVEL_1_STAGE_4_BUILDING_1_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	697,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__NOT_ANIMATED,

	// char spec
	Level1Stage4Building1Tiles,
};

/* Left */

TextureROMSpec LEVEL_1_STAGE_4_BUILDING_1_L_TX =
{
	// charset spec
	(CharSetSpec*)&LEVEL_1_STAGE_4_BUILDING_1_CH,

	// bgmap spec
	Level1Stage4Building1LMap,

	// cols (max 64)
	62,

	// rows (max 64)
	23,

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

BgmapSpriteROMSpec LEVEL_1_STAGE_4_BUILDING_1_L_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapSprite),

		// texture spec
		(TextureSpec*)&LEVEL_1_STAGE_4_BUILDING_1_L_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 2, 1}
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_LON,
};

/* Right */

TextureROMSpec LEVEL_1_STAGE_4_BUILDING_1_R_TX =
{
	// charset spec
	(CharSetSpec*)&LEVEL_1_STAGE_4_BUILDING_1_CH,

	// bgmap spec
	Level1Stage4Building1RMap,

	// cols (max 64)
	62,

	// rows (max 64)
	23,

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

BgmapSpriteROMSpec LEVEL_1_STAGE_4_BUILDING_1_R_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapSprite),

		// texture spec
		(TextureSpec*)&LEVEL_1_STAGE_4_BUILDING_1_R_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 2, 1}
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_RON,
};

/* Entity */

BgmapSpriteROMSpec* const LEVEL_1_STAGE_4_BUILDING_1_SPRITES[] =
{
	&LEVEL_1_STAGE_4_BUILDING_1_L_SPRITE,
	&LEVEL_1_STAGE_4_BUILDING_1_R_SPRITE,
	NULL
};

ShapeROMSpec LEVEL_1_STAGE_4_BUILDING_1_SHAPES[] =
{
	// first inner wall
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{16, 96, 64},

		// displacement (x, y, z, p)
		{-130, -28, 0, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{__I_TO_FIX7_9(1), __I_TO_FIX7_9(1), __I_TO_FIX7_9(1)},

		// if true this shape checks for collisions against other shapes
		false,

		// layers in which I live
		kSolidLayer,

		// layers to ignore when checking for collisions
		kLayerNone,
	},
	// floor
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{512, 32, 32},

		// displacement (x, y, z, p)
		{16, 96, 0, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{0, 0, 0},

		// if true this shape checks for collisions against other shapes
		false,

		// layers in which I live
		kSolidLayer,

		// layers to ignore when checking for collisions
		kLayerNone,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kLayerNone, kLayerNone}
};

PhysicalSpecificationROMSpec LEVEL_1_STAGE_4_BUILDING_1_PHYSICAL_PROPERTIES =
{
	// mass
	__F_TO_FIX10_6(0),

	// friction
	__F_TO_FIX10_6(0.85f),

	// bounciness
	__F_TO_FIX10_6(FLOOR_BOUNCINESS),

	// maximum velocity
	{__I_TO_FIX10_6(100), __I_TO_FIX10_6(100), __I_TO_FIX10_6(100)},

	// maximum speed
	__I_TO_FIX10_6(0)
};

EntityROMSpec LEVEL_1_STAGE_4_BUILDING_1_EN =
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
	(SpriteSpec**)LEVEL_1_STAGE_4_BUILDING_1_SPRITES,

	// use z displacement in projection
	false,

	// collision shapes
	(ShapeSpec*)LEVEL_1_STAGE_4_BUILDING_1_SHAPES,

	// size
	// if 0, width and height will be inferred from the first sprite's texture's size
	{0, 0, 0},

	// gameworld's character's type
	kTypeNone,

	// physical specification
	(PhysicalSpecification*)&LEVEL_1_STAGE_4_BUILDING_1_PHYSICAL_PROPERTIES,
};
