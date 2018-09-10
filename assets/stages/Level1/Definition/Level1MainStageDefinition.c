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
extern EntityDefinition CITY_FLOOR_COLLISION_CL;
extern EntityDefinition FENCE_2_IM;
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
extern EntityDefinition PLAYGROUND_1_IM;
extern EntityDefinition PLAYGROUND_SIGN_1_IM;
extern EntityDefinition STATUE_1_IM;
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
extern Size collision_64_2_8;


//---------------------------------------------------------------------------------------------------------
//											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef LEVEL_1_MAIN_STAGE_ST_CHILDREN[] =
{
	{&CITY_BG_IM,					{   0,  57, 256,   0}, 		0, NULL, NULL, NULL, true},
	{&CITY_FLOOR_IM,				{   0, 178,   0,   0}, 		0, NULL, NULL, NULL, true},

	{&COLLISION_CL,					{  -8,  96,   0,   0},		0, NULL, NULL, (void*)&collision_2_28_8, false}, // left border
	{&CITY_FLOOR_COLLISION_CL,		{ 256, 204,   0,   0},		0, NULL, NULL, (void*)&collision_64_2_8, false}, // bottom border

	{&LANTERN_1_IM,					{  32, 123,   0,   0}, 		0, "Start", NULL, NULL, false},
	{&LEVEL_1_BUILDING_1_EN,		{ 200,  96,   0,   4}, 		0, NULL, NULL, NULL, false},
	{&GRANNY_1_PE,					{ 193,  68,   0,   1}, 		0, NULL, NULL, NULL, false},
	{&TREE_1_IM,					{ 384, 127,   0,   5}, 		0, NULL, NULL, NULL, false},

	{&CAR_1_AC,						{ 540, 168,   0,   0}, 		0, NULL, NULL, (void*)-6, true},
	{&BULLY_1_AC,					{ 640, 155,   0,   0}, 		0, NULL, NULL, (void*)-3, true},

	{&LEVEL_1_BUILDING_2_EN,		{ 552, 140,   0,   4}, 		0, NULL, NULL, NULL, false},
	{&LANTERN_1_IM,					{ 655, 123,   0,   0}, 		0, NULL, NULL, NULL, false},
	{&CAR_BG_1_IM,					{ 704, 134,   0,   6}, 		0, NULL, NULL, NULL, false},
	{&TREE_BG_1_IM,					{ 752, 114,   0,   5}, 		0, NULL, NULL, NULL, false},

	{&CITY_FLOOR_COLLISION_CL,		{ 768, 204,   0,   0},		0, NULL, NULL, (void*)&collision_64_2_8, false}, // bottom border

	{&BULLY_1_AC,					{ 860, 155,   0,   0}, 		0, NULL, NULL, (void*)-3, false},
	{&LEVEL_1_BUILDING_3_EN,		{ 864,  96,   0,   4}, 		0, NULL, NULL, NULL, false},
	{&GRANNY_1_PE,					{ 909,  51,   0,   0}, 		0, NULL, NULL, NULL, false},
	{&LEVEL_1_BUILDING_4_EN,		{1056, 118,   0,   4}, 		0, NULL, NULL, NULL, false},
	{&HOVER_CAR_1_AC,				{1200, 114,   0,   0}, 		0, NULL, NULL, (void*)-5, false},
	{&BUSH_BG_1_IM,					{1212, 104,   0,   0}, 		0, NULL, NULL, NULL, false},
	{&LANTERN_1_IM,					{1230, 123,   0,   0}, 		0, NULL, NULL, NULL, false},
	{&BULLY_1_AC,					{1230, 155,   0,   0}, 		0, NULL, NULL, (void*)-3, false},
	{&CAR_1_AC,						{1240, 168,   0,   0}, 		0, NULL, NULL, (void*)-6, false},

	{&CITY_FLOOR_COLLISION_CL,		{1280, 204,   0,   0},		0, NULL, NULL, (void*)&collision_64_2_8, false}, // bottom border

	{&BUSH_BG_2_IM,					{1584, 104,   0,   0}, 		0, NULL, NULL, NULL, false},
	{&TREE_1_IM,					{1272, 111,   0,   0}, 		0, NULL, NULL, NULL, false},
	{&TREE_1_IM,					{1328, 111,   0,   0}, 		0, NULL, NULL, NULL, false},
	{&PLAYGROUND_SIGN_1_IM,			{1320,  84,   0,   0}, 		0, NULL, NULL, NULL, false},
	{&PLAYGROUND_1_IM,				{1422,  96,   0,   0}, 		0, NULL, NULL, NULL, false},
	{&STATUE_1_IM,					{1518,  96,   0,   0}, 		0, NULL, NULL, NULL, false},
	{&HOVER_CAR_1_AC,				{1518, 114,   0,   0}, 		0, NULL, NULL, (void*)-5, false},
	{&FENCE_2_IM,					{1414, 135,   0,   0}, 		0, NULL, NULL, NULL, false},

	{&LANTERN_1_IM,					{1618, 123,   0,   0}, 		0, NULL, NULL, NULL, false},

	{&CITY_FLOOR_COLLISION_CL,		{1792, 204,   0,   0},		0, NULL, NULL, (void*)&collision_64_2_8, false}, // bottom border

	{&CAR_1_AC,						{1810, 168,   0,   0}, 		0, NULL, NULL, (void*)-6, false},
	{&LEVEL_1_BUILDING_6_EN,		{1810,  79,   0,   4}, 		0, NULL, NULL, NULL, false},
	{&GRANNY_1_PE,					{1848,  31,   0,   0}, 		0, NULL, NULL, NULL, false},
	{&LEVEL_1_BUILDING_7_EN,		{1994, 102,   0,   4}, 		0, NULL, NULL, NULL, false},
	{&LEVEL_1_BUILDING_8_EN,		{2170,  80,   0,   4}, 		0, NULL, NULL, NULL, false},
	{&CLOTHES_1_IM,					{2322,  36,   0,   0}, 		0, NULL, NULL, NULL, false},
	{&BIKE_1_IM,					{2367, 143,   0,   0}, 		0, NULL, NULL, NULL, false},

	{&CITY_FLOOR_COLLISION_CL,		{2304, 204,   0,   0},		0, NULL, NULL, (void*)&collision_64_2_8, false}, // bottom border

	{&LEVEL_1_BUILDING_9_EN,		{2626,  80,   0,   4}, 		0, NULL, NULL, NULL, false},
	{&GRANNY_1_PE,					{2422,  46,   0,   0}, 		0, NULL, NULL, NULL, false},

	{&GRANNY_1_PE,					{2644,  18,   0,   0}, 		0, NULL, NULL, NULL, false},
	{&CAR_1_AC,						{2700, 168,   0,   0}, 		0, NULL, NULL, (void*)-6, false},
	{&CITY_FLOOR_COLLISION_CL,		{2817, 204,   0,   0},		0, NULL, NULL, (void*)&collision_64_2_8, false}, // bottom border

	{&LEVEL_1_BUILDING_10_EN,		{3098,  80,   0,   4}, 		0, NULL, NULL, NULL, false},
	{&LANTERN_1_IM,					{3354, 123,   0,   0}, 		0, NULL, NULL, NULL, false},
	{&TREE_1_IM,					{3378, 111,   0,   0}, 		0, NULL, NULL, NULL, false},
	{&BENCH_1_IM,					{3434, 143,   0,   0}, 		0, NULL, NULL, NULL, false},

	{&CITY_FLOOR_COLLISION_CL,		{3329, 204,   0,   0},		0, NULL, NULL, (void*)&collision_64_2_8, false}, // bottom border

	{&CAR_BG_2_IM,					{3671, 144,   0,   0}, 		0, NULL, NULL, NULL, false},
	{&LEVEL_1_BUILDING_11_EN,		{3675,  64,   0,   1}, 		0, NULL, NULL, NULL, false},

	{&CITY_FLOOR_COLLISION_CL,		{3700, 204,   0,   0},		0, NULL, NULL, (void*)&collision_64_2_8, false}, // bottom border

	{&COLLISION_CL,					{3700,  96,   0,   0},		0, NULL, NULL, (void*)&collision_2_28_8, false}, // right border

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
			__MAXIMUM_X_VIEW_DISTANCE, __MAXIMUM_Y_VIEW_DISTANCE,
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