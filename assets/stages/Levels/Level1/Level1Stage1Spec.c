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
#include <Captain.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern EntitySpec LOW_POWER_INDICATOR_LB;

extern EntitySpec ATTACK_DOG_EM;
extern EntitySpec HIGHWAYMEN_EN;
extern EntitySpec STOP_YOU_CANNOT_PASS_EN;
extern EntitySpec LEVEL_1_STAGE_1_MAIN_EXIT_XP;
extern EntitySpec BENCH_EN;
extern EntitySpec BIKE_EN;
extern EntitySpec PUNK_EM;
extern EntitySpec BUSH_BG_1_EN;
extern EntitySpec BUSH_BG_2_EN;
extern EntitySpec CAR_1_AC;
extern EntitySpec CAR_BG_1_EN;
extern EntitySpec CAR_BG_2_EN;
extern EntitySpec CITY_BG_1_EN;
extern EntitySpec CITY_FLOOR_3D_EN;
extern EntitySpec CITY_FLOOR_COLLISION_CL;
extern EntitySpec CITY_FLOOR_EN;
extern EntitySpec CLOUDS_BACK_EN;
extern EntitySpec CLOUDS_FRONT_EN;
extern EntitySpec CLOTHES_1_EN;
extern EntitySpec COLLISION_CL;
extern EntitySpec COMIC_NIVEL_1_EN;
extern EntitySpec LEVEL_1_MISSION_EN;
extern EntitySpec FENCE_EN;
extern EntitySpec FOLDING_STAND_EN;
extern EntitySpec GARAGE_CAR_EN;
extern EntitySpec GARAGE_SIGN_EN;
extern EntitySpec GRANNY_PE;
extern EntitySpec GUI_EN;
extern EntitySpec HOVER_CAR_EM;
extern EntitySpec LANTERN_1_EN;
extern EntitySpec LEVEL_1_STAGE_1_BUILDING_1_EN;
extern EntitySpec LEVEL_1_STAGE_1_BUILDING_2_EN;
extern EntitySpec LEVEL_1_STAGE_1_BUILDING_3_EN;
extern EntitySpec LEVEL_1_STAGE_1_BUILDING_4_EN;
extern EntitySpec LEVEL_1_STAGE_1_BUILDING_6_EN;
extern EntitySpec LEVEL_1_STAGE_1_BUILDING_7_EN;
extern EntitySpec LEVEL_1_STAGE_1_BUILDING_8_EN;
extern EntitySpec LEVEL_1_STAGE_1_BUILDING_9_A_EN;
extern EntitySpec LEVEL_1_STAGE_1_BUILDING_9_B_EN;
extern EntitySpec LEVEL_1_STAGE_1_BUILDING_10_EN;
extern EntitySpec LEVEL_1_STAGE_1_BUILDING_11_EN;
extern EntitySpec MANOLO_EM;
extern EntitySpec PLAYGROUND_EN;
extern EntitySpec PLAYGROUND_SIGN_EN;
extern EntitySpec STATUE_1_EN;
extern EntitySpec TREE_1_EN;
extern EntitySpec TREE_BG_1_EN;

extern CharSetSpec PUNK_CH;
extern CharSetSpec CAR_1_CH;
extern CharSetSpec FLOWER_POT_CH;
extern CharSetSpec GUI_CH;
extern CharSetSpec CAPTAIN_CH;
extern CharSetSpec CAPTAIN_BLACK_CH;
extern CharSetSpec HOVER_CAR_CH;
extern CharSetSpec CITY_BG_1_CH;

extern TextureSpec CITY_BG_1_A_TX;
extern TextureSpec CITY_BG_1_B_TX;
extern TextureSpec PUNK_TX;
extern TextureSpec CAR_1_TX;
extern TextureSpec GUI_TX;
extern TextureSpec FLOWER_POT_TX;
extern TextureSpec CAPTAIN_TX;
extern TextureSpec CAPTAIN_BLACK_TX;
extern TextureSpec HOVER_CAR_TX;

extern Size collision_16_224_64;
extern Size collision_384_16_64;
extern Size collision_3608_16_64;

extern Sound CAPITANO_SONG;


//---------------------------------------------------------------------------------------------------------
//											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMSpec LEVEL_1_STAGE_1_ST_CHILDREN[] =
{
	{&COLLISION_CL,						{  -8,  96,    0,   0},		0, NULL, NULL, (void*)&collision_16_224_64, false}, // left border

	{&CLOUDS_BACK_EN,					{  32,   8,  352,   0},		0, NULL, NULL, NULL, true},
	{&CLOUDS_FRONT_EN,					{   0,   0,  320,   0},		0, NULL, NULL, NULL, true},
	{&CITY_BG_1_EN,						{-256,  35,  256,   0},		0, NULL, NULL, NULL, true},

	{&CITY_FLOOR_EN,					{   0, 172,    0,   0},		0, NULL, NULL, NULL, true},

	{&CITY_FLOOR_COLLISION_CL,			{1804, 200,    0,   0},		0, NULL, NULL, (void*)&collision_3608_16_64, true},

	{&PUNK_EM,							{ 586, 147,    0,   0},		0, NULL, NULL, (void*)-2, false},
	{&ATTACK_DOG_EM,					{830, 152,    0,   0},		0, NULL, NULL, (void*)-5, false},
	{&PUNK_EM,							{1130, 147,    0,   0},		0, NULL, NULL, (void*)-3, false},
	{&PUNK_EM,							{1330, 147,    0,   0},		0, NULL, NULL, (void*)-3, false},
	{&ATTACK_DOG_EM,					{1530, 152,    0,   0},		0, NULL, NULL, (void*)-4, false},
	{&PUNK_EM,							{1670, 147,    0,   0},		0, NULL, NULL, (void*)-3, false},
	{&PUNK_EM,							{2280, 147,    0,   0},		0, NULL, NULL, (void*)-4, false},
	{&PUNK_EM,							{2460, 147,    0,   0},		0, NULL, NULL, (void*)-3, false},

	{&HOVER_CAR_EM,						{2160, 114,    0,   0},		0, NULL, NULL, NULL, false},

	{&CAR_1_AC,							{ 500, 166,    0,   0},		0, NULL, NULL, NULL, false},
	{&CAR_1_AC,							{1040, 166,    0,   0},		0, NULL, NULL, NULL, false},
	{&CAR_1_AC,							{3608, 166,    0,   0},		0, NULL, NULL, NULL, false},
	{&CAR_1_AC,							{4810, 166,    0,   0},		0, NULL, NULL, NULL, false},

	{&COMIC_NIVEL_1_EN,					{ 192,  92,   -2,   0},		0, NULL, NULL, NULL, false},

	{&TREE_1_EN,						{  24, 108,   24,   0},		0, NULL, NULL, NULL, false},

	{&LANTERN_1_EN,						{  32, 137,    0,   0},		0, NULL, NULL, NULL, false},
	{&LEVEL_1_STAGE_1_BUILDING_1_EN,	{ 200,  80,    0,   0},		0, NULL, NULL, NULL, false},

	{&TREE_1_EN,						{ 350, 108,   24,   0},		0, NULL, NULL, NULL, false},

	{&LEVEL_1_STAGE_1_BUILDING_2_EN,	{ 518, 126,    0,   0},		0, NULL, NULL, NULL, false},
	{&LANTERN_1_EN,						{ 616, 137,    0,   0},		0, NULL, NULL, NULL, false},
	{&CAR_BG_1_EN,						{ 664, 136,   16,   0},		0, NULL, NULL, NULL, false},
	{&TREE_BG_1_EN,						{ 698, 112,   32,   0},		0, NULL, NULL, NULL, false},

	{&LEVEL_1_STAGE_1_BUILDING_3_EN,	{ 808,  80,    0,   0},		0, NULL, NULL, NULL, false},
	{&GRANNY_PE,						{ 765,  50,    0,   0},		0, NULL, NULL, NULL, false},
	{&GRANNY_PE,						{ 852,  50,    0,   0},		0, NULL, NULL, NULL, false},

	{&LEVEL_1_STAGE_1_BUILDING_4_EN,	{ 996, 102,    0,   0},		0, NULL, NULL, NULL, false},

	{&BUSH_BG_1_EN,						{1138, 112,   64,   0},		0, NULL, NULL, NULL, false},
	{&LANTERN_1_EN,						{1166, 137,    0,   0},		0, NULL, NULL, NULL, false},

	{&TREE_1_EN,						{1256, 104,    0,   0},		0, NULL, NULL, NULL, false},
	{&PLAYGROUND_SIGN_EN,				{1288,  76,    0,   0},		0, NULL, NULL, NULL, false},
	{&TREE_1_EN,						{1312,  94,    0,   0},		0, NULL, NULL, NULL, false},
	{&FENCE_EN,							{1376, 135,    0,   0},		0, NULL, NULL, NULL, false},
	{&PLAYGROUND_EN,					{1390,  92,    0,   0},		0, NULL, NULL, NULL, false},
	{&STATUE_1_EN,						{1486,  80,    0,   0},		0, NULL, NULL, NULL, false},
	{&BUSH_BG_2_EN,						{1534, 112,   64,   0},		0, NULL, NULL, NULL, false},

	{&LANTERN_1_EN,						{1570, 137,    0,   0},		0, NULL, NULL, NULL, false},

	{&LEVEL_1_STAGE_1_BUILDING_6_EN,	{1746,  79,    0,   0},		0, NULL, NULL, NULL, false},
	{&GRANNY_PE,						{1784,  31,    0,   0},		0, NULL, NULL, NULL, false},

	{&LEVEL_1_STAGE_1_BUILDING_7_EN,	{1920, 100,    0,   0},		0, NULL, NULL, NULL, false},

	{&LEVEL_1_STAGE_1_BUILDING_8_EN,	{2106,  80,    0,   0},		0, NULL, NULL, NULL, false},
	{&CLOTHES_1_EN,						{2253,  39,    0,   0},		0, NULL, NULL, NULL, false},
	{&BIKE_EN,							{2288, 144,    0,   0},		0, NULL, NULL, NULL, false},

	{&LEVEL_1_STAGE_1_BUILDING_9_A_EN,	{2406,  80,    0,   0},		0, NULL, NULL, NULL, false},
	{&LEVEL_1_STAGE_1_BUILDING_9_B_EN,	{2662,  80,    0,   0},		0, NULL, NULL, NULL, false},
	{&GRANNY_PE,						{2340,  46,    0,   0},		0, NULL, NULL, NULL, false},

	{&GRANNY_PE,						{2552,  18,    0,   0},		0, NULL, NULL, NULL, false},

	{&LEVEL_1_STAGE_1_BUILDING_10_EN,	{2978,  80,    0,   0},		0, NULL, NULL, NULL, false},
	{&GARAGE_CAR_EN,					{2914, 140,    0,   0},		0, NULL, NULL, NULL, false},
	{&FOLDING_STAND_EN,					{3024, 147,    0,   0},		0, NULL, NULL, NULL, false},
	{&GARAGE_SIGN_EN,					{3152,  63,    0,   0},		0, NULL, NULL, NULL, false},

	{&MANOLO_EM,						{3136, 142,    0,   0},		0, NULL, NULL, NULL, false},

	{&LANTERN_1_EN,						{3238, 137,    0,   0},		0, NULL, NULL, NULL, false},
	{&TREE_1_EN,						{3254, 109,   24,   0},		0, NULL, NULL, NULL, false},
	{&BENCH_EN,							{3318, 143,    0,   0},		0, NULL, NULL, NULL, false},

	{&TREE_1_EN,						{3356, 109,   24,   0},		0, NULL, NULL, NULL, false},

	{&HIGHWAYMEN_EN,					{3440, 144,    0,   0},		0, NULL, NULL, NULL, false},
	{&STOP_YOU_CANNOT_PASS_EN,			{3444,  96,    0,   0},		0, NULL, NULL, NULL, false},

	{&BUSH_BG_1_EN,						{3486, 128,   64,   0},		0, NULL, NULL, NULL, false},

	{&CAR_BG_2_EN,						{3579, 141,    0,   0},		0, NULL, NULL, NULL, false},
	{&LEVEL_1_STAGE_1_BUILDING_11_EN,	{3583,  68,    0,   0},		0, NULL, NULL, NULL, false},
	{&LEVEL_1_STAGE_1_MAIN_EXIT_XP,		{3600,  40,    0,   0},		0, NULL, NULL, NULL, false},

	{&COLLISION_CL,						{3616,  96,    0,   0},		0, NULL, NULL, (void*)&collision_16_224_64, false}, // right border

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_STAGE_1_ST_UI_CHILDREN[] =
{
	//{&CITY_FLOOR_3D_EN, 				{ 192, 172,  16,   0}, 		0, NULL, NULL, NULL, true},
	{&LEVEL_1_MISSION_EN,				{  60, 204,  -2,   0},		0, NULL, NULL, NULL, false},
	{&GUI_EN, 							{ 192, 204,  -1,   0}, 		0, NULL, NULL, NULL, true},
//	{&LOW_POWER_INDICATOR_LB, 			{ 265, 215,  -2,   0}, 		0, NULL, NULL, NULL, true},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
//											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMSpec* const LEVEL_1_STAGE_1_ST_FONTS[] =
{
	NULL
};

CharSetROMSpec* const LEVEL_1_STAGE_1_ST_CHARSETS[] =
{
	NULL
};

TextureSpec* const LEVEL_1_STAGE_1_ST_TEXTURES[] =
{
	NULL
};

const PostProcessingEffect LEVEL_1_STAGE_1_ST_POST_PROCESSING_EFFECTS[] =
{
	NULL
};

SoundROM* const LEVEL_1_STAGE_1_ST_BGM[] =
{
	&CAPITANO_SONG,
	NULL,
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMSpec LEVEL_1_STAGE_1_ST =
{
	// allocator
	__TYPE(Stage),

	// Timer config
	{
		__TIMER_100US,
		20,
		kMS
	},

	// Sound config
	{
		__DEFAULT_PCM_HZ,
		false
	},

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
		16,
		// unload padding
		16,
		// streaming amplitude
		16,
		// particle removal delay cycles
		4,
		// deferred
		false,
	},

	// rendering
	{
		// number of cycles the texture writing is idle
		4,

		// maximum number of texture's rows to write each time the texture writing is active
		8,

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
			(BrightnessRepeatSpec*)NULL,
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
			0,
			// __spt3
			448,
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
		(FontSpec**)LEVEL_1_STAGE_1_ST_FONTS,

		// char sets to preload
		(CharSetSpec**)LEVEL_1_STAGE_1_ST_CHARSETS,

		// textures to preload
		(TextureSpec**)LEVEL_1_STAGE_1_ST_TEXTURES,

		// background sounds
		(Sound**)LEVEL_1_STAGE_1_ST_BGM,
	},

	// entities
	{
		// ui
		{
			(PositionedEntity*)LEVEL_1_STAGE_1_ST_UI_CHILDREN,
			__TYPE(UIContainer),
		},

		// children
		(PositionedEntity*)LEVEL_1_STAGE_1_ST_CHILDREN,
	},

	// post processing effects
	(PostProcessingEffect*)LEVEL_1_STAGE_1_ST_POST_PROCESSING_EFFECTS,
};


//---------------------------------------------------------------------------------------------------------
//												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMSpec LEVEL_1_STAGE_1_MAIN_EP =
{
	// the stage to load
	(StageSpec*)&LEVEL_1_STAGE_1_ST,

	// starting position (x, y, z)
	{64, 133, CAPTAIN_DSPL},

	// facing direction of the captain
	__RIGHT,

	// whether this entry point acts as a checkpoint
	true,
};
