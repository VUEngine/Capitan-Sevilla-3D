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
#include <Fonts.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//											DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern EntityDefinition INTRO_IMAGE_1_IM;
extern EntityDefinition INTRO_IMAGE_2_IM;
extern EntityDefinition INTRO_IMAGE_3_IM;
extern EntityDefinition INTRO_IMAGE_4_IM;
extern EntityDefinition INTRO_IMAGE_5_IM;
extern EntityDefinition INTRO_IMAGE_6_IM;
extern EntityDefinition INTRO_IMAGE_7_IM;
extern EntityDefinition INTRO_IMAGE_8_IM;

extern EntityDefinition INTRO_TEXT_1_AC;
extern EntityDefinition INTRO_TEXT_2_AC;
extern EntityDefinition INTRO_TEXT_3_AC;
extern EntityDefinition INTRO_TEXT_4_AC;
extern EntityDefinition INTRO_TEXT_5_AC;
extern EntityDefinition INTRO_TEXT_6_AC;
extern EntityDefinition INTRO_TEXT_7_AC;
extern EntityDefinition INTRO_TEXT_8_AC;
extern EntityDefinition INTRO_TEXT_9_AC;


//---------------------------------------------------------------------------------------------------------
// 											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef INTRO_STAGE_ST_ENTITIES[] =
{
	{&INTRO_IMAGE_1_IM, {80, 68, 0, 0}, 	0, "IMAGE1", NULL, NULL, false},
	{&INTRO_IMAGE_2_IM, {188, 126, 1, 0}, 	0, "IMAGE2", NULL, NULL, false},
	{&INTRO_IMAGE_3_IM, {328, 56, 2, 0}, 	0, "IMAGE3", NULL, NULL, false},
	{&INTRO_IMAGE_4_IM, {296, 164, 2, 0}, 	0, "IMAGE4", NULL, NULL, false},

	{&INTRO_TEXT_1_AC, 	{80, 32, 0, 0}, 	0, "TEXT1", NULL, NULL, false},
	{&INTRO_TEXT_2_AC, 	{84, 172, 0, 0}, 	0, "TEXT2", NULL, NULL, false},
	{&INTRO_TEXT_3_AC, 	{228, 36, 0, 0}, 	0, "TEXT3", NULL, NULL, false},
	{&INTRO_TEXT_4_AC, 	{264, 197, 0, 0}, 	0, "TEXT4", NULL, NULL, false},
	{&INTRO_TEXT_5_AC, 	{353, 197, 0, 0}, 	0, "TEXT5", NULL, NULL, false},

	{&INTRO_IMAGE_5_IM, {64, 60, 0, 0}, 	0, "IMAGE5", NULL, NULL, false},
	{&INTRO_IMAGE_6_IM, {180, 48, 1, 0}, 	0, "IMAGE6", NULL, NULL, false},
	{&INTRO_IMAGE_7_IM, {308, 44, 2, 0}, 	0, "IMAGE7", NULL, NULL, false},
	{&INTRO_IMAGE_8_IM, {308, 180, 2, 0}, 	0, "IMAGE8", NULL, NULL, false},

	{&INTRO_TEXT_6_AC, 	{64, 165, 0, 0}, 	0, "TEXT6", NULL, NULL, false},
	{&INTRO_TEXT_7_AC, 	{180, 145, 1, 0}, 	0, "TEXT7", NULL, NULL, false},
	{&INTRO_TEXT_8_AC, 	{310, 103, 2, 0}, 	0, "TEXT8", NULL, NULL, false},
	{&INTRO_TEXT_9_AC, 	{344, 154, 2, 0}, 	0, "TEXT9", NULL, NULL, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef INTRO_STAGE_ST_UI_ENTITIES[] =
{

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMDef* const INTRO_STAGE_ST_FONTS[] =
{
	//&CAPITAN_DEFAULT_FONT_PARTIAL,

	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef INTRO_STAGE_ST =
{
	// allocator
	__TYPE(Stage),

	// level
	{
		// size
		{
			// x
			__SCREEN_WIDTH,
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
			0
		},

		// camera's frustum
        {
        	// x0
        	0,
        	// y0
			0,
			// z0
			-10,
        	// x1
        	__SCREEN_WIDTH,
        	// y1
        	__SCREEN_HEIGHT,
        	// z1
        	__SCREEN_WIDTH * 5
        }
	},

	// streaming
	{
		// load padding
		40,
		// unload padding
		16,
		// streaming amplitude
		24,
		// particle removal delay cycles
		0,
		// deferred
		false
	},

	// rendering
	{
		// number of cycles the texture writing is idle
		__TARGET_FPS / 10,

		// maximum number of texture's rows to write each time the texture writing is active
		12,

		// maximum number of rows to compute on each call to the affine functions
		16,

		// colors config
		{
			// background color
			__COLOR_BLACK,

			// brightness
			// these values times the repeat values specified in the column table (max. 16) make the final
			// brightness values on the respective regions of the screen. maximum brightness is 128.
			{
				// dark red
				8,
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
			__AVAILABLE_CHAR_OBJECTS / __TOTAL_OBJECT_SEGMENTS,
			// __spt1
			__AVAILABLE_CHAR_OBJECTS / __TOTAL_OBJECT_SEGMENTS,
			// __spt2
			__AVAILABLE_CHAR_OBJECTS / __TOTAL_OBJECT_SEGMENTS,
			// __spt3
			__AVAILABLE_CHAR_OBJECTS / __TOTAL_OBJECT_SEGMENTS,
		},

		// OBJECT segments z coordinates
		// note that each spt's z coordinate much be larger than or equal to the previous one's,
		// since the vip renders obj worlds in reverse order (__spt3 to __spt0)
		{
			// __spt0
			LAYER_0_PARTICLES,
			// __spt1
			LAYER_0_PARTICLES,
			// __spt2
			LAYER_0_PARTICLES,
			// __spt3
			LAYER_0_PARTICLES,
		},

		// optical configuration values
		{
			// maximum view distance's power into the horizon
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
		// gravity
		{
			__I_TO_FIX10_6(0),
			__F_TO_FIX10_6(__GRAVITY),
			__I_TO_FIX10_6(0)
		},

		// friction
		__F_TO_FIX10_6(0.1f),
	},

	// assets
	{
		// fonts to preload
		(FontDefinition**)INTRO_STAGE_ST_FONTS,

		// char sets to preload
		(CharSetDefinition**)NULL,

		// textures to preload
		(TextureDefinition**)NULL,

		// background music
		(const u16 (*)[])NULL,
	},

	// entities
	{
		// ui
		{
			INTRO_STAGE_ST_UI_ENTITIES,
			__TYPE(UiContainer),
		},

		// children
		INTRO_STAGE_ST_ENTITIES,
	},

	// post processing effects
	(PostProcessingEffect*)NULL,
};
