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
#include <macros.h>
#include <PlatformerLevelState.h>
#include <Languages.h>
#include <VIPManager.h>
#include <Fonts.h>
#include <Captain.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern EntitySpec Level1Stage4MainExitXp;

extern EntitySpec AttackDogEm;
extern EntitySpec BenchEntity;
extern EntitySpec CloudsBackEntity;
extern EntitySpec CloudsFrontEntity;
extern EntitySpec CollisionCl;
extern EntitySpec DogPoo1Entity;
extern EntitySpec GuiEntity;
extern EntitySpec Lantern1Entity;
extern EntitySpec Level1Stage4BackgroundAEntity;
extern EntitySpec Level1Stage4BackgroundBEntity;
extern EntitySpec Level1Stage4Building1Entity;
extern EntitySpec Level1Stage4LiftEntity;
extern EntitySpec Level1Stage4Park1Entity;
extern EntitySpec LowPowerIndicatorEntity;
extern EntitySpec Tree1Entity;

extern CharSetSpec PunkCharset;
extern CharSetSpec PunkBlackCharset;

extern Size collision_16_224_64;


//---------------------------------------------------------------------------------------------------------
//											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMSpec Level1Stage4StChildren[] =
{
	{&CollisionCl,						{  -8,  96,    0,   0},		0, NULL, NULL, (void*)&collision_16_224_64, false}, // left border

	{&CloudsBackEntity,					{  32,   8,  352,   0},		0, NULL, NULL, NULL, true},
	{&CloudsFrontEntity,					{   0,   0,  320,   0},		0, NULL, NULL, NULL, true},
	{&Level1Stage4BackgroundAEntity,	{-112, 112,  256,   0},		0, NULL, NULL, NULL, true},
	{&Level1Stage4BackgroundBEntity,	{ 590, 112,  256,   0},		0, NULL, NULL, NULL, true},

	{&Level1Stage4Building1Entity,	{ 248,  92,    0,   0},		0, NULL, NULL, NULL, true},
	{&Level1Stage4LiftEntity,			{ 236,  76,    0,   0},		0, NULL, NULL, NULL, true},
	{&Tree1Entity,						{ 320, 128,    0,   0},		0, NULL, NULL, NULL, false},
	{&DogPoo1Entity,						{ 416, 166,    0,   0},		0, NULL, NULL, NULL, false},
	{&Level1Stage4Park1Entity,		{ 604,  92,    0,   0},		0, NULL, NULL, NULL, false},
	{&Lantern1Entity,						{ 476, 132,    0,   0},		0, NULL, NULL, NULL, false},
	{&BenchEntity,							{ 624, 159,    0,   0},		0, NULL, NULL, NULL, false},
	{&AttackDogEm,					{ 632, 159,    0,   0},		0, NULL, NULL, NULL, false},

	{&Level1Stage4MainExitXp,		{ 760, 128,    0,   0},		0, NULL, NULL, NULL, false},
	{&CollisionCl,						{ 774,  96,    0,   0},		0, NULL, NULL, (void*)&collision_16_224_64, false}, // right border

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1Stage4StUiChildren[] =
{
	{&GuiEntity, 							{ 332, 204,  -1,   0}, 		0, NULL, NULL, NULL, true},
	{&LowPowerIndicatorEntity, 			{ 265, 215,  -2,   0}, 		0, NULL, NULL, NULL, true},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
//											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMSpec* const Level1Stage4StFonts[] =
{
	NULL
};

CharSetROMSpec* const Level1Stage4StCharsets[] =
{
	&PunkCharset,
	&PunkBlackCharset,
	NULL
};

TextureSpec* const Level1Stage4StTextures[] =
{
	NULL
};

const PostProcessingEffect Level1Stage4St_POST_PROCESSING_EFFECTS[] =
{
	NULL
};

SoundROM* const Level1Stage4St_BGM[] =
{
	NULL,
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMSpec Level1Stage4St =
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
		false
	},

	// level
	{
		// size
		{
			// x
			767,
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
		64,
		// unload padding
		16,
		// streaming amplitude
		16,
		// particle removal delay cycles
		4,
		// deferred
		false
	},

	// rendering
	{
		// maximum number of texture's rows to write each time the texture writing is active
		48,

		// maximum number of rows to compute on each call to the affine functions
		48,

		// colors config
		{
			// background color
			__COLOR_BRIGHT_RED,

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
		(FontSpec**)Level1Stage4StFonts,

		// char sets to preload
		(CharSetSpec**)Level1Stage4StCharsets,

		// textures to preload
		(TextureSpec**)Level1Stage4StTextures,

		// background sounds
		(Sound**)Level1Stage4St_BGM,
	},

	// entities
	{
		// ui
		{
			(PositionedEntity*)Level1Stage4StUiChildren,
			__TYPE(UIContainer),
		},

		// children
		(PositionedEntity*)Level1Stage4StChildren,
	},

	// post processing effects
	(PostProcessingEffect*)Level1Stage4St_POST_PROCESSING_EFFECTS,
};


//---------------------------------------------------------------------------------------------------------
//												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMSpec Level1Stage4MainEntryPoint =
{
	// the stage to load
	(StageSpec*)&Level1Stage4St,

	// starting position (x, y, z)
	{236,  0, CAPTAIN_DSPL},

	// facing direction of the captain
	__RIGHT,

	// whether this entry point acts as a checkpoint
	true,
};
