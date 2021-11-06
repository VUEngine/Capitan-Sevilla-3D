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

extern EntitySpec LowPowerIndicatorEntity;

extern EntitySpec PunkEm;
extern EntitySpec ManoloEm;
extern EntitySpec CityBg2Entity;
extern EntitySpec CloudsBackEntity;
extern EntitySpec CloudsFrontEntity;
extern EntitySpec HoverCarEm;
extern EntitySpec Level1Stage3Building1Entity;
extern EntitySpec Level1Stage3Building2aEntity;
extern EntitySpec Level1Stage3Building2bEntity;
extern EntitySpec Level1Stage3Building3aEntity;
extern EntitySpec Level1Stage3Building3bEntity;
extern EntitySpec Level1Stage3EtEntity;
extern EntitySpec Level1Stage3FenceEntity;
extern EntitySpec Level1Stage3HotelSignEntity;
extern EntitySpec Level1Stage3LiftEntity;
extern EntitySpec Level1Stage3PlankEntity;
extern EntitySpec Level1Stage3SignEntity;
extern EntitySpec Level1Stage3Box1Entity;
extern EntitySpec Level1Stage3Clothes1Entity;
extern EntitySpec CITY_FLOOR_CollisionCl;
extern EntitySpec CollisionCl;
extern EntitySpec CollisionTopCl;
extern EntitySpec GuiEntity;
extern EntitySpec KillCollisionCl;
extern EntitySpec EnemyWallCl;

extern CharSetSpec CityBg2Charset;
extern CharSetSpec GuiCharset;
extern CharSetSpec PunkCharset;
extern CharSetSpec PunkBlackCharset;

extern TextureSpec CityBg2ATexture;
extern TextureSpec CityBg2BTexture;
extern TextureSpec GuiTexture;

extern Size collision_16_224_64;
extern Size collision_48_56_64;
extern Size collision_384_16_64;

extern Sound CaptainSong;


//---------------------------------------------------------------------------------------------------------
//											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMSpec Level1Stage3StChildren[] =
{
	{&CollisionCl,						{  -8,  96,    0,   0},		0, NULL, NULL, (void*)&collision_16_224_64, false}, // left border

	{&EnemyWallCl,					{ 435, 143,    0,   0},		0, NULL, NULL, NULL, false}, // left border

	{&CloudsBackEntity,					{  32,   8,  352,   0},		0, NULL, NULL, NULL, true},
	{&CloudsFrontEntity,					{   0,   0,  320,   0},		0, NULL, NULL, NULL, true},
	{&CityBg2Entity,						{ 128,  53,  256,   0},		0, NULL, NULL, NULL, true},
	{&Level1Stage3EtEntity,			{ -62,  31,  255,   0},		0, NULL, NULL, NULL, false},

	{&Level1Stage3FenceEntity,			{  56, 159,    0,   0},		0, NULL, NULL, NULL, false},
	{&CollisionTopCl,					{ 160, 146,    0,   0},		0, NULL, NULL, (void*)&collision_48_56_64, false}, // box
	{&Level1Stage3Building1Entity,	{ 172,  96,    0,   0},		0, NULL, NULL, NULL, false},
	{&Level1Stage3Clothes1Entity,		{  48, 131,    1,   0},		0, NULL, NULL, NULL, false},
	{&Level1Stage3Box1Entity,			{ 156, 142,    1,   0},		0, NULL, NULL, NULL, false},
	{&Level1Stage3PlankEntity,			{ 397, 164,    0,   0},		0, NULL, NULL, NULL, false},

	{&Level1Stage3SignEntity,			{ 624,  77,   32,   0},		0, NULL, NULL, NULL, false},
	{&HoverCarEm,						{ 716, 108,    0,   0},		0, NULL, NULL, NULL, false},
	{&Level1Stage3Building2aEntity,	{ 626, 114,    0,   0},		0, NULL, NULL, NULL, false},
	{&Level1Stage3FenceEntity,			{ 658, 159,    0,   0},		0, NULL, NULL, NULL, false},
	{&Level1Stage3Building2bEntity,	{1014, 114,    0,   0},		0, NULL, NULL, NULL, false},
	{&PunkEm,							{900, 143,    0,   0},		0, NULL, NULL, NULL, false},
	{&Level1Stage3FenceEntity,			{1034, 159,    0,   0},		0, NULL, NULL, NULL, false},
	{&Level1Stage3HotelSignEntity,	{1040,  72,   32,   0},		0, NULL, NULL, NULL, false},
	{&PunkEm,							{1100, 143,    0,   0},		0, NULL, NULL, NULL, false},

	{&EnemyWallCl,					{1240, 143,    0,   0},		0, NULL, NULL, NULL, false}, // right border
	{&KillCollisionCl,				{1260, 248,    0,   0},		0, NULL, NULL, (void*)&collision_384_16_64, true},

	{&Level1Stage3Building3aEntity,	{1450, 116,    0,   0},		0, NULL, NULL, NULL, false},
	{&Level1Stage3Building3bEntity,	{1734,  96,    0,   0},		0, NULL, NULL, NULL, false},
	{&Level1Stage3LiftEntity,			{1783, 136,    0,   0},		0, NULL, NULL, NULL, false},

	{&CollisionCl,						{1808,  96,    0,   0},		0, NULL, NULL, (void*)&collision_16_224_64, false}, // right border

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1Stage3StUiChildren[] =
{
	{&GuiEntity, 							{ 332, 204,  -1,   0}, 		0, NULL, NULL, NULL, true},
	{&LowPowerIndicatorEntity, 			{ 265, 215,  -2,   0}, 		0, NULL, NULL, NULL, true},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
//											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMSpec* const Level1Stage3StFonts[] =
{
	NULL
};

CharSetROMSpec* const Level1Stage3StCharsets[] =
{
	&GuiCharset,
	&CityBg2Charset,
	&PunkCharset,
	&PunkBlackCharset,

	NULL
};

TextureSpec* const Level1Stage3StTextures[] =
{
	&GuiTexture,

	NULL
};

const PostProcessingEffect Level1Stage3St_POST_PROCESSING_EFFECTS[] =
{
	NULL
};

SoundROM* const Level1Stage3St_BGM[] =
{
	&CaptainSong,
	NULL,
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMSpec Level1Stage3St =
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
			1928,
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
			0,
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
		false,
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
		(FontSpec**)Level1Stage3StFonts,

		// char sets to preload
		(CharSetSpec**)Level1Stage3StCharsets,

		// textures to preload
		(TextureSpec**)Level1Stage3StTextures,

		// background sounds
		(Sound**)Level1Stage3St_BGM,
	},

	// entities
	{
		// ui
		{
			(PositionedEntity*)Level1Stage3StUiChildren,
			__TYPE(UIContainer),
		},

		// children
		(PositionedEntity*)Level1Stage3StChildren,
	},

	// post processing effects
	(PostProcessingEffect*)Level1Stage3St_POST_PROCESSING_EFFECTS,
};


//---------------------------------------------------------------------------------------------------------
//												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMSpec Level1Stage3MainEntryPoint =
{
	// the stage to load
	(StageSpec*)&Level1Stage3St,

	// starting position (x, y, z)
	{280, 148, CAPTAIN_DSPL},

	// facing direction of the captain
	//__RIGHT,
	__LEFT,

	// whether this entry point acts as a checkpoint
	true,
};
