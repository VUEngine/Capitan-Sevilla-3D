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
extern EntitySpec GUI_EN;
extern EntitySpec LEVEL_1_STAGE_2_ROOM_EN;
extern EntitySpec LEVEL_1_STAGE_2_LIFT_EN;
extern EntitySpec PUNK_EM;


//---------------------------------------------------------------------------------------------------------
//											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMSpec LEVEL_1_STAGE_2_ST_CHILDREN[] =
{
	{&LEVEL_1_STAGE_2_ROOM_EN,		{ 360,  84,    4,   0},		0, NULL, NULL, NULL, true},
	//{&PUNK_EM,						{ 380, 137,    0,   0},		0, NULL, NULL, (void*)-3, false},
	{&PUNK_EM,						{ 508, 137,    0,   0},		0, NULL, NULL, (void*)-3, false},
	{&LEVEL_1_STAGE_2_LIFT_EN,		{ 693, 130,    0,   0},		0, NULL, NULL, NULL, true},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_STAGE_2_ST_UI_CHILDREN[] =
{
	{&GUI_EN, 						{ 192, 204,  -1,   0}, 		0, NULL, NULL, NULL, true},
	{&LOW_POWER_INDICATOR_LB, 		{  16, 204,  -1,   0}, 		0, NULL, NULL, NULL, true},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
//											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMSpec* const LEVEL_1_STAGE_2_ST_FONTS[] =
{
	NULL
};

CharSetROMSpec* const LEVEL_1_STAGE_2_ST_CHARSETS[] =
{
	NULL
};

TextureSpec* const LEVEL_1_STAGE_2_ST_TEXTURES[] =
{
	NULL
};

const PostProcessingEffect LEVEL_1_STAGE_2_ST_POST_PROCESSING_EFFECTS[] =
{
	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMSpec LEVEL_1_STAGE_2_ST =
{
	// allocator
	__TYPE(Stage),

	// Timer config
	{
		__TIMER_100US,
		10,
		kMS
	},

	// Sound config
	{
		__DEFAULT_PCM_HZ,
	},

	// level
	{
		// size
		{
			// x
			720,
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
		(FontSpec**)LEVEL_1_STAGE_2_ST_FONTS,

		// char sets to preload
		(CharSetSpec**)LEVEL_1_STAGE_2_ST_CHARSETS,

		// textures to preload
		(TextureSpec**)LEVEL_1_STAGE_2_ST_TEXTURES,

		// background sounds
		(Sound**)NULL,
	},

	// entities
	{
		// ui
		{
			LEVEL_1_STAGE_2_ST_UI_CHILDREN,
			__TYPE(UIContainer),
		},

		// children
		LEVEL_1_STAGE_2_ST_CHILDREN,
	},

	// post processing effects
	(PostProcessingEffect*)LEVEL_1_STAGE_2_ST_POST_PROCESSING_EFFECTS,
};


//---------------------------------------------------------------------------------------------------------
//												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMSpec LEVEL_1_STAGE_2_MAIN_EP =
{
	// the stage to load
	(StageSpec*)&LEVEL_1_STAGE_2_ST,

	// starting position (x, y, z)
	{80, 96, CAPTAIN_DSPL},

	// facing direction of the captain
	__RIGHT,

	// whether this entry point acts as a checkpoint
	true,
};
