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
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE AdjustmentScreenVUEngineIconTiles[];
extern BYTE AdjustmentScreenVUEngineIconMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMDef ADJUSTMENT_SCREEN_VUENGINE_ICON_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	8,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__NOT_ANIMATED,

	// char definition
	AdjustmentScreenVUEngineIconTiles,
};

TextureROMDef ADJUSTMENT_SCREEN_VUENGINE_ICON_TX =
{
	// charset definition
	(CharSetDefinition*)&ADJUSTMENT_SCREEN_VUENGINE_ICON_CH,

	// bgmap definition
	AdjustmentScreenVUEngineIconMap,

	// cols (max 64)
	3,

	// rows (max 64)
	3,

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
};

BgmapSpriteROMDef ADJUSTMENT_SCREEN_VUENGINE_ICON_IM_L_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapSprite),

		// texture definition
		(TextureDefinition*)&ADJUSTMENT_SCREEN_VUENGINE_ICON_TX,

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
	__WORLD_LON,
};

BgmapSpriteROMDef* const ADJUSTMENT_SCREEN_VUENGINE_ICON_IM_L_SPRITES[] =
{
	&ADJUSTMENT_SCREEN_VUENGINE_ICON_IM_L_SPRITE,
	NULL
};

BgmapSpriteROMDef const ADJUSTMENT_SCREEN_VUENGINE_ICON_IM_R_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapSprite),

		// texture definition
		(TextureDefinition*)&ADJUSTMENT_SCREEN_VUENGINE_ICON_TX,

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
	__WORLD_RON,
};

BgmapSpriteROMDef* const ADJUSTMENT_SCREEN_VUENGINE_ICON_IM_R_SPRITES[] =
{
	&ADJUSTMENT_SCREEN_VUENGINE_ICON_IM_R_SPRITE,
	NULL

};

EntityROMDef ADJUSTMENT_SCREEN_VUENGINE_ICON_IM_L =
{
	// class allocator
	__TYPE(Entity),

	// sprites
	(SpriteROMDef**)ADJUSTMENT_SCREEN_VUENGINE_ICON_IM_L_SPRITES,

	// collision shapes
	(ShapeDefinition*)NULL,

	// size
	// if 0, width and height will be inferred from the first sprite's texture's size
	{0, 0, 0},

	// gameworld's character's type
	kNoType,

	// physical specification
	(PhysicalSpecification*)NULL,
};

EntityROMDef ADJUSTMENT_SCREEN_VUENGINE_ICON_IM_R =
{
	// class allocator
	__TYPE(Entity),

	// sprites
	(SpriteROMDef**)ADJUSTMENT_SCREEN_VUENGINE_ICON_IM_R_SPRITES,

	// collision shapes
	(ShapeDefinition*)NULL,

	// size
	// if 0, width and height will be inferred from the first sprite's texture's size
	{0, 0, 0},

	// gameworld's character's type
	kNoType,

	// physical specification
	(PhysicalSpecification*)NULL,
};
