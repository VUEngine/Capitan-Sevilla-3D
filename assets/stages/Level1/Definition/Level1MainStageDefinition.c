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

#include <Stage.h>
#include <macros.h>
#include <PlatformerLevelState.h>
#include <Languages.h>
#include <VIPManager.h>
#include <Fonts.h>
#include <Hero.h>
#include <PostProcessingEffects.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern EntityDefinition BARBER_SHOP_1_IM;
extern EntityDefinition BENCH_1_IM;
extern EntityDefinition BIKE_1_IM;
extern EntityDefinition BULLY_1_AC;
extern EntityDefinition BUSH_BG_1_IM;
extern EntityDefinition BUSH_BG_2_IM;
extern EntityDefinition CAR_1_AC;
extern EntityDefinition CAR_BG_2_IM;
extern EntityDefinition CAR_BG_1_IM;
extern EntityDefinition CITY_BG_IM;
extern EntityDefinition CITY_FLOOR_IM;
extern EntityDefinition CLOTHES_1_IM;
extern EntityDefinition COLLISION_CL;
extern EntityDefinition CONTAINER_1_IM;
extern EntityDefinition FENCE_1_IM;
extern EntityDefinition FENCE_2_IM;
extern EntityDefinition GARAGE_1_IM;
extern EntityDefinition GARAGE_2_IM;
extern EntityDefinition GRANNY_1_PE;
extern EntityDefinition GUI_IM;
extern EntityDefinition HOUSE_1_IM;
extern EntityDefinition HOUSE_2_IM;
extern EntityDefinition HOUSE_3_IM;
extern EntityDefinition HOUSE_4_IM;
extern EntityDefinition HOUSE_5_IM;
extern EntityDefinition HOUSE_6_IM;
extern EntityDefinition HOVER_CAR_1_AC;
extern EntityDefinition LANTERN_1_IM;
extern EntityDefinition MOTORBIKE_1_IM;
extern EntityDefinition PLAYGROUND_1_IM;
extern EntityDefinition PLAYGROUND_SIGN_1_IM;
extern EntityDefinition STATUE_1_IM;
extern EntityDefinition THING_1_IM;
extern EntityDefinition TRASH_BIN_1_IM;
extern EntityDefinition TREE_1_IM;
extern EntityDefinition TREE_BG_1_IM;
extern EntityDefinition WALL_1_IM;

extern CharSetDefinition BULLY_1_CH;
extern CharSetDefinition CAR_1_CH;
extern CharSetDefinition FLOWER_POT_1_CH;
extern CharSetDefinition GUI_CH;
extern CharSetDefinition HERO_RIGHT_CH;
extern CharSetDefinition HERO_RIGHT_BLACK_CH;
extern CharSetDefinition HOVER_CAR_1_CH;

extern TextureDefinition BULLY_1_TX;
extern TextureDefinition CAR_1_TX;
extern TextureDefinition GUI_TX;
extern TextureDefinition FLOWER_POT_1_TX;
extern TextureDefinition HERO_TX;
extern TextureDefinition HERO_BLACK_TX;
extern TextureDefinition HOVER_CAR_1_TX;

extern Size collision_2_28_8;
extern Size collision_64_2_8;


//---------------------------------------------------------------------------------------------------------
//												ASSETS
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
//											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef LEVEL_1_MAIN_STAGE_ST_CHILDREN[] =
{
	{&CITY_BG_IM,			{0,	60, LAYER_4, 0}, 		0, NULL, NULL, NULL, true},
	{&CITY_FLOOR_IM,		{0,	178, 0, 0}, 			0, NULL, NULL, NULL, true},

	{&COLLISION_CL,			{-8, 96, 0, 0},				0, NULL, NULL, (void*)&collision_2_28_8, false}, // left border
	{&COLLISION_CL,			{256, 204, 0, 0},			0, NULL, NULL, (void*)&collision_64_2_8, false}, // bottom border

	{&LANTERN_1_IM,			{32, 123, 0, 0}, 			0, "Start", NULL, NULL, false},
	{&MOTORBIKE_1_IM,		{104, 158, (LAYER_1)-16, 0}, 0, NULL, NULL, NULL, false},
	{&HOUSE_1_IM,			{200, 96, LAYER_1, 0}, 		0, NULL, NULL, NULL, false},
	{&GRANNY_1_PE,			{193, 68, (LAYER_1)-1, 0}, 	0, NULL, NULL, NULL, false},
	{&CONTAINER_1_IM,		{181, 161, (LAYER_1)-16, 0}, 0, NULL, NULL, NULL, false},
	{&TREE_1_IM,			{384, 127, LAYER_2, 0}, 	0, NULL, NULL, NULL, false},

	{&CAR_1_AC,				{540, 164, -16, 0}, 		0, NULL, NULL, (void*)-6, true},
	{&BULLY_1_AC,			{640, 156, 16, 0}, 			0, NULL, NULL, (void*)-3, true},

	{&WALL_1_IM,			{552, 140, LAYER_1, 0}, 	0, NULL, NULL, NULL, false},
	{&THING_1_IM,			{479, 150, (LAYER_1)-16, 0}, 0, NULL, NULL, NULL, false},
	{&LANTERN_1_IM,			{655, 123, 0, 0}, 			0, NULL, NULL, NULL, false},
	{&CAR_BG_1_IM,			{704, 150, LAYER_2, 0}, 	0, NULL, NULL, NULL, false},
	{&TREE_BG_1_IM,			{752, 130, (LAYER_2)+16, 0}, 0, NULL, NULL, NULL, false},

	{&COLLISION_CL,			{768, 204, 0, 0},			0, NULL, NULL, (void*)&collision_64_2_8, false}, // bottom border

	{&BULLY_1_AC,			{860, 156, 16, 0}, 			0, NULL, NULL, (void*)-3, false},
	{&HOUSE_2_IM,			{864, 96, LAYER_1, 0}, 		0, NULL, NULL, NULL, false},
	{&GRANNY_1_PE,			{909, 67, (LAYER_1)-1, 0}, 	0, NULL, NULL, NULL, false},
	{&GARAGE_1_IM,			{1040, 118, (LAYER_1)+16, 0}, 0, NULL, NULL, NULL, false},
	{&HOVER_CAR_1_AC,		{1100, 120, 16, 0}, 		0, NULL, NULL, (void*)-5, false},
	{&TRASH_BIN_1_IM,		{1100, 155, LAYER_1, 0}, 	0, NULL, NULL, NULL, false},
	{&FENCE_1_IM,			{1150, 151, (LAYER_1)-16, 0}, 0, NULL, NULL, NULL, false},
	{&BUSH_BG_1_IM,			{1212, 120, LAYER_2, 0}, 	0, NULL, NULL, NULL, false},
	{&LANTERN_1_IM,			{1230, 123, 0, 0}, 			0, NULL, NULL, NULL, false},
	{&BULLY_1_AC,			{1230, 156, 16, 0}, 		0, NULL, NULL, (void*)-3, false},
	{&CAR_1_AC,				{1240, 164, -16, 0}, 		0, NULL, NULL, (void*)-6, false},

	{&COLLISION_CL,			{1280, 204, 0, 0},			0, NULL, NULL, (void*)&collision_64_2_8, false}, // bottom border

	{&BUSH_BG_2_IM,			{1584, 120, LAYER_2, 0}, 	0, NULL, NULL, NULL, false},
	{&TREE_1_IM,			{1272, 127, LAYER_2, 0}, 	0, NULL, NULL, NULL, false},
	{&TREE_1_IM,			{1328, 127, LAYER_2, 0}, 	0, NULL, NULL, NULL, false},
	{&PLAYGROUND_SIGN_1_IM,	{1320, 100, LAYER_1, 0}, 	0, NULL, NULL, NULL, false},
	{&PLAYGROUND_1_IM,		{1422, 112, LAYER_1, 0}, 	0, NULL, NULL, NULL, false},
	{&STATUE_1_IM,			{1518, 112, LAYER_1, 0}, 	0, NULL, NULL, NULL, false},
	{&HOVER_CAR_1_AC,		{1518, 120, 16, 0}, 		0, NULL, NULL, (void*)-5, false},
	{&FENCE_2_IM,			{1414, 151, (LAYER_1)-16, 0}, 0, NULL, NULL, NULL, false},

	{&LANTERN_1_IM,			{1618, 123, 0, 0}, 			0, NULL, NULL, NULL, false},

	{&COLLISION_CL,			{1792, 204, 0, 0},			0, NULL, NULL, (void*)&collision_64_2_8, false}, // bottom border

	{&CAR_1_AC,				{1810, 164, -16, 0}, 		0, NULL, NULL, (void*)-6, false},
	{&BARBER_SHOP_1_IM,		{1810, 95, LAYER_1, 0}, 	0, NULL, NULL, NULL, false},
	{&GRANNY_1_PE,			{1848, 47, (LAYER_1)-1, 0}, 0, NULL, NULL, NULL, false},
	{&GARAGE_2_IM,			{1994, 118, (LAYER_1)+16, 0}, 0, NULL, NULL, NULL, false},
	{&HOUSE_3_IM,			{2170, 96, LAYER_1, 0}, 	0, NULL, NULL, NULL, false},
	{&CLOTHES_1_IM,			{2322, 52, (LAYER_1)+16, 0}, 0, NULL, NULL, NULL, false},
	{&BIKE_1_IM,			{2367, 159, (LAYER_1)+16, 0}, 0, NULL, NULL, NULL, false},

	{&COLLISION_CL,			{2304, 204, 0, 0},			0, NULL, NULL, (void*)&collision_64_2_8, false}, // bottom border

	{&HOUSE_4_IM,			{2626, 96, LAYER_1, 0}, 	0, NULL, NULL, NULL, false},
	{&GRANNY_1_PE,			{2422, 62, (LAYER_1)-1, 0}, 0, NULL, NULL, NULL, false},

	{&GRANNY_1_PE,			{2644, 34, (LAYER_1)-1, 0}, 0, NULL, NULL, NULL, false},
	{&CAR_1_AC,				{2700, 164, -16, 0}, 		0, NULL, NULL, (void*)-6, false},
	{&COLLISION_CL,			{2817, 204, 0, 0},			0, NULL, NULL, (void*)&collision_64_2_8, false}, // bottom border

	{&HOUSE_5_IM,			{3098, 96, LAYER_1, 0}, 	0, NULL, NULL, NULL, false},
	{&LANTERN_1_IM,			{3354, 123, 0, 0}, 			0, NULL, NULL, NULL, false},
	{&TREE_1_IM,			{3378, 127, LAYER_2, 0}, 	0, NULL, NULL, NULL, false},
	{&BENCH_1_IM,			{3434, 159, LAYER_1, 0}, 	0, NULL, NULL, NULL, false},

	{&COLLISION_CL,			{3329, 204, 0, 0},			0, NULL, NULL, (void*)&collision_64_2_8, false}, // bottom border

	{&CAR_BG_2_IM,			{3671, 147, 0, 0}, 			0, NULL, NULL, NULL, false},
	{&HOUSE_6_IM,			{3675, 80, 0, 16}, 			0, NULL, NULL, NULL, false},

	{&COLLISION_CL,			{3700, 204, 0, 0},			0, NULL, NULL, (void*)&collision_64_2_8, false}, // bottom border

	{&COLLISION_CL,			{3700, 96, 0, 0},			0, NULL, NULL, (void*)&collision_2_28_8, false}, // right border

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_STAGE_ST_UI_CHILDREN[] =
{
	{&GUI_IM, {192, 204, -1, 0}, 0, NULL, NULL, NULL, true},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
//											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMDef* const LEVEL_1_MAIN_STAGE_ST_FONTS[] =
{
	&CAPITAN_DEFAULT_FONT_PARTIAL,

	NULL
};

CharSetROMDef* const LEVEL_1_MAIN_STAGE_ST_CHARSETS[] =
{
	&BULLY_1_CH,
	&CAR_1_CH,
	&FLOWER_POT_1_CH,
	&HOVER_CAR_1_CH,
	&GUI_CH,
	&HERO_RIGHT_CH,
	&HERO_RIGHT_BLACK_CH,

	NULL
};

TextureDefinition* const LEVEL_1_MAIN_STAGE_ST_TEXTURES[] =
{
	&BULLY_1_TX,
	&CAR_1_TX,
	&FLOWER_POT_1_TX,
	&HOVER_CAR_1_TX,
	&GUI_TX,
	&HERO_TX,
	&HERO_BLACK_TX,

	NULL
};

const PostProcessingEffect LEVEL_1_MAIN_STAGE_ST_POST_PROCESSING_EFFECTS[] =
{
	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef LEVEL_1_MAIN_STAGE_ST =
{
	// allocator
	__TYPE(Stage),

	// level
	{
		// size
		{
			// x
			3700,
			// y
			__SCREEN_HEIGHT,
			// z
			__SCREEN_DEPTH,
		},

		// camera's initial position inside the game world
		{
			// x
			0,
			// y
			0,
			// z
			0,
			// p
			0,
		},

		// camera's frustum
        {
        	// x0
        	0,
        	// y0
			0,
			// z0
			-16,
        	// x1
        	__SCREEN_WIDTH,
        	// y1
        	__SCREEN_HEIGHT,
        	// z1
        	__SCREEN_DEPTH,
        },
	},

	// streaming
	{
		// load padding
		40,
		// unload padding
		40,
		// streaming amplitude
		16,
		// particle removal delay cycles
		4,
	},

	// rendering
	{
		// number of cycles the texture writing is idle
		1,

		// maximum number of texture's rows to write each time the texture writing is active
		32,

		// maximum number of rows to compute on each call to the affine functions
		48,

		// colors config
		{
			// background color
			__COLOR_BLACK,

			// brightness
			// these values times the repeat values specified in the column table (max. 16) make the final
			// brightness values on the respective regions of the screen. maximum brightness is 128.
			{
				// dark red
				__BRIGHTNESS_DARK_RED,
				// medium red
				__BRIGHTNESS_MEDIUM_RED,
				// bright red
				__BRIGHTNESS_BRIGHT_RED,
			},

			// brightness repeat
			(BrightnessRepeatDefinition*)NULL,
		},

		// palettes' config
		{
			{
				// bgmap palette 0
				__BGMAP_PALETTE_0,
				// bgmap palette 1
				__BGMAP_PALETTE_1,
				// bgmap palette 2
				__BGMAP_PALETTE_2,
				// bgmap palette 3
				__BGMAP_PALETTE_3,
			},
			{
				// object palette 0
				__OBJECT_PALETTE_0,
				// object palette 1
				__OBJECT_PALETTE_1,
				// object palette 2
				__OBJECT_PALETTE_2,
				// object palette 3
				__OBJECT_PALETTE_3,
			},
		},

		// bgmap segments configuration
		// number of segments reserved for the param table
		1,

		// obj segments sizes (must total 1024)
		{
			// __spt0
			0,
			// __spt1
			0,
			// __spt2
			64,
			// __spt3
			64,
		},

		// OBJECT segments z coordinates
		// Note that each SPT's z coordinate must be larger than or equal to the previous one's,
		// since the VIP renders OBJ Worlds in reverse order (__SPT3 to __SPT0)
		{
			// __spt0
			LAYER_0_PARTICLES,
			// __spt1
			LAYER_0_PARTICLES,
			// __spt2
			LAYER_0_PARTICLES,

			// __spt3
			20,
		},

		// optical configuration values
		{
			// maximum x view distance's power into the horizon (x, y)
			6, 14,
			// distance of the eyes to the screen
			__DISTANCE_EYE_SCREEN,
			// distance from left to right eye (depth sensation)
			__BASE_FACTOR,
			// horizontal view point center
			__HORIZONTAL_VIEW_POINT_CENTER,
			// vertical view point center
			__VERTICAL_VIEW_POINT_CENTER,
			// scaling factor
			__SCALING_MODIFIER_FACTOR,
		},
	},

	// physics
	{
		// gravity (x, y, z)
		{
			__I_TO_FIX10_6(0),
			__F_TO_FIX10_6(__GRAVITY),
			__I_TO_FIX10_6(0)
		},

		// friction
		__F_TO_FIX10_6(0),
	},

	// assets
	{
		// fonts to preload
		(FontDefinition**)LEVEL_1_MAIN_STAGE_ST_FONTS,

		// char sets to preload
		(CharSetDefinition**)LEVEL_1_MAIN_STAGE_ST_CHARSETS,

		// textures to preload
		(TextureDefinition**)LEVEL_1_MAIN_STAGE_ST_TEXTURES,

		// background music
		NULL,
	},

	// entities
	{
		// ui
		{
			LEVEL_1_MAIN_STAGE_ST_UI_CHILDREN,
			__TYPE(UiContainer),
		},

		// children
		LEVEL_1_MAIN_STAGE_ST_CHILDREN,
	},

	// post processing effects
	(PostProcessingEffect*)LEVEL_1_MAIN_STAGE_ST_POST_PROCESSING_EFFECTS,
};


//---------------------------------------------------------------------------------------------------------
//												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMDef LEVEL_1_MAIN_MAIN_EP =
{
	// the stage to load
	(StageDefinition*)&LEVEL_1_MAIN_STAGE_ST,

	// name of the entity to start at
	"Start",

	// offset from entry point (x, y, z)
	{
		32,
		-16,
		1,
		0,
	},

	// whether this entry point acts as a checkpoint
	false,
};