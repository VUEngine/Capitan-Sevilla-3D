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


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern EntityDefinition LEVEL_1_BUILDING_6_EN;
extern EntityDefinition BENCH_1_IM;
extern EntityDefinition BIKE_1_EN;
extern EntityDefinition BULLY_1_AC;
extern EntityDefinition BUSH_BG_1_EN;
extern EntityDefinition BUSH_BG_2_EN;
extern EntityDefinition CAR_1_AC;
extern EntityDefinition CAR_BG_2_IM;
extern EntityDefinition CAR_BG_1_IM;
extern EntityDefinition CITY_BG_IM;
extern EntityDefinition CITY_FLOOR_IM;
extern EntityDefinition CLOTHES_1_EN;
extern EntityDefinition COLLISION_CL;
extern EntityDefinition CITY_FLOOR_COLLISION_CL;
extern EntityDefinition FENCE_2_EN;
extern EntityDefinition LEVEL_1_BUILDING_4_EN;
extern EntityDefinition LEVEL_1_BUILDING_7_EN;
extern EntityDefinition GRANNY_1_PE;
extern EntityDefinition GUI_IM;
extern EntityDefinition LEVEL_1_BUILDING_1_EN;
extern EntityDefinition LEVEL_1_BUILDING_3_EN;
extern EntityDefinition LEVEL_1_BUILDING_8_EN;
extern EntityDefinition LEVEL_1_BUILDING_9_EN;
extern EntityDefinition LEVEL_1_BUILDING_10_EN;
extern EntityDefinition LEVEL_1_BUILDING_11_EN;
extern EntityDefinition HOVER_CAR_1_AC;
extern EntityDefinition LANTERN_1_IM;
extern EntityDefinition PLAYGROUND_1_EN;
extern EntityDefinition PLAYGROUND_SIGN_1_EN;
extern EntityDefinition STATUE_1_EN;
extern EntityDefinition TREE_1_IM;
extern EntityDefinition TREE_BG_1_IM;
extern EntityDefinition LEVEL_1_BUILDING_2_EN;

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
extern Size collision_48_2_8;


//---------------------------------------------------------------------------------------------------------
//											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef LEVEL_1_MAIN_STAGE_ST_CHILDREN[] =
{
	{&CITY_BG_IM,					{   0,  30, 6144,   0},		0, NULL, NULL, NULL, true},
	{&CITY_FLOOR_IM,				{   0, 178,    0,   0},		0, NULL, NULL, NULL, true},

	{&COLLISION_CL,					{  -8,  96,    0,   0},		0, NULL, NULL, (void*)&collision_2_28_8, false}, // left border
	{&CITY_FLOOR_COLLISION_CL,		{ 192, 204,    0,   0},		0, NULL, NULL, (void*)&collision_48_2_8, false}, // bottom border

	{&LANTERN_1_IM,					{  32, 123,    0,   0},		0, "Start", NULL, NULL, false},
	{&LEVEL_1_BUILDING_1_EN,		{ 200,  96,   64,   0},		0, NULL, NULL, NULL, false},
	{&GRANNY_1_PE,					{ 193,  68,   64,   0},		0, NULL, NULL, NULL, false},
	{&TREE_1_IM,					{ 356, 127,   48,   0},		0, NULL, NULL, NULL, false},

	{&CITY_FLOOR_COLLISION_CL,		{ 372, 204,    0,   0},		0, NULL, NULL, (void*)&collision_48_2_8, false}, // bottom border

	{&CAR_1_AC,						{ 540, 168,   -8,   0},		0, NULL, NULL, (void*)-6, true},
	{&BULLY_1_AC,					{ 640, 156,    0,   0},		0, NULL, NULL, (void*)-3, true},

	{&CITY_FLOOR_COLLISION_CL,		{ 552, 204,    0,   0},		0, NULL, NULL, (void*)&collision_48_2_8, false}, // bottom border

	{&LEVEL_1_BUILDING_2_EN,		{ 520, 140,   64,   0},		0, NULL, NULL, NULL, false},
	{&LANTERN_1_IM,					{ 616, 123,    0,   0},		0, NULL, NULL, NULL, false},
	{&CAR_BG_1_IM,					{ 664, 152,   80,   0},		0, NULL, NULL, NULL, false},
	{&TREE_BG_1_IM,					{ 704, 128,   96,   0},		0, NULL, NULL, NULL, false},

	{&CITY_FLOOR_COLLISION_CL,		{ 732, 204,    0,   0},		0, NULL, NULL, (void*)&collision_48_2_8, false}, // bottom border

	{&BULLY_1_AC,					{ 860, 156,    0,   0},		0, NULL, NULL, (void*)-3, false},
	{&LEVEL_1_BUILDING_3_EN,		{ 808,  96,   64,   0},		0, NULL, NULL, NULL, false},
	{&GRANNY_1_PE,					{ 853,  66,   64,   0},		0, NULL, NULL, NULL, false},

	{&CITY_FLOOR_COLLISION_CL,		{ 912, 204,    0,   0},		0, NULL, NULL, (void*)&collision_48_2_8, false}, // bottom border

	{&LEVEL_1_BUILDING_4_EN,		{ 996, 118,   96,   0},		0, NULL, NULL, NULL, false},

	{&CITY_FLOOR_COLLISION_CL,		{1092, 204,    0,   0},		0, NULL, NULL, (void*)&collision_48_2_8, false}, // bottom border

	{&HOVER_CAR_1_AC,				{1200, 120,    0,   0},		0, NULL, NULL, (void*)-5, false},
	{&BUSH_BG_1_EN,					{1132, 104,  128,   0},		0, NULL, NULL, NULL, false},
	{&LANTERN_1_IM,					{1166, 123,    0,   0},		0, NULL, NULL, NULL, false},
	{&BULLY_1_AC,					{1230, 156,    0,   0},		0, NULL, NULL, (void*)-3, false},
	{&CAR_1_AC,						{1240, 168,   -8,   0},		0, NULL, NULL, (void*)-6, false},

	{&CITY_FLOOR_COLLISION_CL,		{1272, 204,    0,   0},		0, NULL, NULL, (void*)&collision_48_2_8, false}, // bottom border

	{&TREE_1_IM,					{1256, 120,   80,   0},		0, NULL, NULL, NULL, false},
	{&PLAYGROUND_SIGN_1_EN,			{1288,  84,   64,   0},		0, NULL, NULL, NULL, false},
	{&TREE_1_IM,					{1312, 110,   96,   0},		0, NULL, NULL, NULL, false},
	{&FENCE_2_EN,					{1376, 151,   32,   0},		0, NULL, NULL, NULL, false},
	{&PLAYGROUND_1_EN,				{1390, 108,   80,   0},		0, NULL, NULL, NULL, false},
	{&STATUE_1_EN,					{1486,  96,   64,   0},		0, NULL, NULL, NULL, false},
	{&HOVER_CAR_1_AC,				{1486, 120,    0,   0},		0, NULL, NULL, (void*)-5, false},
	{&BUSH_BG_2_EN,					{1552, 104,  128,   0},		0, NULL, NULL, NULL, false},

	{&CITY_FLOOR_COLLISION_CL,		{1452, 204,    0,   0},		0, NULL, NULL, (void*)&collision_48_2_8, false}, // bottom border

	{&LANTERN_1_IM,					{1570, 123,    0,   0},		0, NULL, NULL, NULL, false},

	{&CITY_FLOOR_COLLISION_CL,		{1632, 204,    0,   0},		0, NULL, NULL, (void*)&collision_48_2_8, false}, // bottom border

	{&CAR_1_AC,						{1810, 168,   -8,   0},		0, NULL, NULL, (void*)-6, false},
	{&LEVEL_1_BUILDING_6_EN,		{1746,  95,   64,   0},		0, NULL, NULL, NULL, false},
	{&GRANNY_1_PE,					{1784,  47,   64,   0},		0, NULL, NULL, NULL, false},

	{&CITY_FLOOR_COLLISION_CL,		{1812, 204,    0,   0},		0, NULL, NULL, (void*)&collision_48_2_8, false}, // bottom border

	{&LEVEL_1_BUILDING_7_EN,		{1922, 118,   64,   0},		0, NULL, NULL, NULL, false},

	{&CITY_FLOOR_COLLISION_CL,		{1992, 204,    0,   0},		0, NULL, NULL, (void*)&collision_48_2_8, false}, // bottom border

	{&LEVEL_1_BUILDING_8_EN,		{2106,  96,   64,   0},		0, NULL, NULL, NULL, false},
	{&CLOTHES_1_EN,					{2254,  55,   96,   0},		0, NULL, NULL, NULL, false},
	{&BIKE_1_EN,					{2288, 159,   48,   0},		0, NULL, NULL, NULL, false},

	{&CITY_FLOOR_COLLISION_CL,		{2172, 204,    0,   0},		0, NULL, NULL, (void*)&collision_48_2_8, false}, // bottom border

	{&LEVEL_1_BUILDING_9_EN,		{2534,  96,   64,   0},		0, NULL, NULL, NULL, false},
	{&GRANNY_1_PE,					{2340,  62,   64,   0},		0, NULL, NULL, NULL, false},

	{&CITY_FLOOR_COLLISION_CL,		{2352, 204,    0,   0},		0, NULL, NULL, (void*)&collision_48_2_8, false}, // bottom border

	{&GRANNY_1_PE,					{2552,  34,   64,   0},		0, NULL, NULL, NULL, false},
	{&CAR_1_AC,						{2608, 168,   -8,   0},		0, NULL, NULL, (void*)-6, false},

	{&CITY_FLOOR_COLLISION_CL,		{2532, 204,    0,   0},		0, NULL, NULL, (void*)&collision_48_2_8, false}, // bottom border
	{&CITY_FLOOR_COLLISION_CL,		{2712, 204,    0,   0},		0, NULL, NULL, (void*)&collision_48_2_8, false}, // bottom border
	{&CITY_FLOOR_COLLISION_CL,		{2892, 204,    0,   0},		0, NULL, NULL, (void*)&collision_48_2_8, false}, // bottom border

	{&LEVEL_1_BUILDING_10_EN,		{3006,  96,   64,   0},		0, NULL, NULL, NULL, false},

	{&CITY_FLOOR_COLLISION_CL,		{3072, 204,    0,   0},		0, NULL, NULL, (void*)&collision_48_2_8, false}, // bottom border

	{&LANTERN_1_IM,					{3262, 123,    0,   0},		0, NULL, NULL, NULL, false},
	{&TREE_1_IM,					{3286, 127,   80,   0},		0, NULL, NULL, NULL, false},
	{&BENCH_1_IM,					{3342, 159,   64,   0},		0, NULL, NULL, NULL, false},

	{&CITY_FLOOR_COLLISION_CL,		{3252, 204,    0,   0},		0, NULL, NULL, (void*)&collision_48_2_8, false}, // bottom border
	{&CITY_FLOOR_COLLISION_CL,		{3432, 204,    0,   0},		0, NULL, NULL, (void*)&collision_48_2_8, false}, // bottom border

	{&CAR_BG_2_IM,					{3579, 146,    0,   0},		0, NULL, NULL, NULL, false},
	{&LEVEL_1_BUILDING_11_EN,		{3583,  80,    4,   0},		0, NULL, NULL, NULL, false},

	{&CITY_FLOOR_COLLISION_CL,		{3612, 204,    0,   0},		0, NULL, NULL, (void*)&collision_48_2_8, false}, // bottom border
	{&COLLISION_CL,					{3608,  96,    0,   0},		0, NULL, NULL, (void*)&collision_2_28_8, false}, // right border

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_STAGE_ST_UI_CHILDREN[] =
{
	{&GUI_IM, 						{ 192, 204,  -1,   0}, 		0, NULL, NULL, NULL, true},

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
			3608,
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
			-16,
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
		24,
		// unload padding
		4,
		// streaming amplitude
		16,
		// particle removal delay cycles
		4,
		// deferred
		false
	},

	// rendering
	{
		// number of cycles the texture writing is idle
		1,

		// maximum number of texture's rows to write each time the texture writing is active
		48,

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
			256,
			// __spt1
			256,
			// __spt2
			256,
			// __spt3
			256,
		},

		// OBJECT segments z coordinates
		// Note that each SPT's z coordinate must be larger than or equal to the previous one's,
		// since the VIP renders OBJ Worlds in reverse order (__SPT3 to __SPT0)
		{
			// __spt0
			0,
			// __spt1
			0,
			// __spt2
			0,
			// __spt3
			0,
		},

		// optical configuration values
		{
			// maximum x view distance's power into the horizon (x, y)
			16384, 16384,
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
		0,
		HERO_DSPL,
		0,
	},

	// whether this entry point acts as a checkpoint
	false,
};