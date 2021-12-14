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

#include <Stage.h>
#include <CsAdjustmentScreenState.h>


//---------------------------------------------------------------------------------------------------------
//											DECLARATIONS
//---------------------------------------------------------------------------------------------------------


extern EntitySpec CsAdjustmentScreenSplatEntity;
extern EntitySpec CsAdjustmentScreenIconLEntity;
extern EntitySpec CsAdjustmentScreenIconREntity;
extern EntitySpec CsAdjustmentScreenLogoEntity;
extern EntitySpec CsAdjustmentScreenMadeWithEntity;

extern EntitySpec LowPowerIndicatorEntity;


//---------------------------------------------------------------------------------------------------------
// 											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMSpec CsAdjustmentScreenStageEntities[] =
{

	{&CsAdjustmentScreenIconREntity, 		{ 16, 202,  0, 0}, 0, NULL, NULL, NULL, false},
	{&CsAdjustmentScreenIconLEntity, 		{ 16,  22,  0, 0}, 0, NULL, NULL, NULL, false},
	{&CsAdjustmentScreenSplatEntity, 		{192, 112,  1, 0}, 0, NULL, NULL, NULL, false},
	//{&CsAdjustmentScreenMadeWithEntity, 	{130,  90,  0, 0}, 0, NULL, NULL, NULL, false},
	{&CsAdjustmentScreenLogoEntity, 		{192, 110,  0, 0}, 0, NULL, NULL, NULL, false},
	{&CsAdjustmentScreenIconLEntity, 		{368, 202,  0, 0}, 0, NULL, NULL, NULL, false},
	{&CsAdjustmentScreenIconREntity, 		{368,  22,  0, 0}, 0, NULL, NULL, NULL, false},

	{&LowPowerIndicatorEntity, 				{ 40,  12,  0, 0}, 0, NULL, NULL, NULL, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec CsAdjustmentScreenStageUiEntities[] =
{
	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

SoundROM* const CsAdjustmentScreenStage_SOUNDS[] =
{
	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMSpec CsAdjustmentScreenStage =
{
	// allocator
	__TYPE(Stage),

	// Timer config
	{
		__TIMER_100US,
		1000,
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
			0,
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
        	__SCREEN_WIDTH * 5,
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
		false,
	},

	// rendering
	{
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

		// object segments sizes (up to 1024 in total)
		// can impact performance, make sure to configure only as large as maximally needed
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

		// object segments z coordinates
		// note that each spt's z coordinate much be larger than or equal to the previous one's,
		// since the vip renders obj worlds in reverse order (__spt3 to __spt0)
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
			__F_TO_FIX10_6(0),
			__I_TO_FIX10_6(0),
		},

		// friction
		__F_TO_FIX10_6(0.1f),
	},

	// assets
	{
		// fonts to preload
		(FontSpec**)NULL,

		// char sets to preload
		(CharSetSpec**)NULL,

		// textures to preload
		(TextureSpec**)NULL,

		// background sounds
		(Sound**)CsAdjustmentScreenStage_SOUNDS,
	},

	// entities
	{
		// ui
		{
			(PositionedEntity*)CsAdjustmentScreenStageUiEntities,
			__TYPE(UIContainer),
		},

		// children
		(PositionedEntity*)CsAdjustmentScreenStageEntities,
	},

	// post processing effects
	(PostProcessingEffect*)NULL,
};

