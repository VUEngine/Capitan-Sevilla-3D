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

extern EntitySpec AttackDogEm;
extern EntitySpec HighwaymenEntity;
extern EntitySpec StopYouCannotPassEntity;
extern EntitySpec Level1Stage1MainExitXp;
extern EntitySpec BenchEntity;
extern EntitySpec BikeEntity;
extern EntitySpec PunkEm;
extern EntitySpec BushBg1Entity;
extern EntitySpec BushBg2Entity;
extern EntitySpec Car1Entity;
extern EntitySpec CarBg1Entity;
extern EntitySpec CarBg2Entity;
extern EntitySpec CityBg1Entity;
extern EntitySpec CityFloor3dEntity;
extern EntitySpec CITY_FLOOR_CollisionCl;
extern EntitySpec CityFloorEntity;
extern EntitySpec CloudsBackEntity;
extern EntitySpec CloudsFrontEntity;
extern EntitySpec Clothes1Entity;
extern EntitySpec CollisionCl;
extern EntitySpec ComicNivel1Entity;
extern EntitySpec Level1MissionEntity;
extern EntitySpec FenceEntity;
extern EntitySpec FoldingStandEntity;
extern EntitySpec GarageCarEntity;
extern EntitySpec GarageSignEntity;
extern EntitySpec GrannyPe;
extern EntitySpec GuiEntity;
extern EntitySpec HoverCarEm;
extern EntitySpec Lantern1Entity;
extern EntitySpec Level1Stage1Building1Entity;
extern EntitySpec Level1Stage1Building2Entity;
extern EntitySpec Level1Stage1Building3Entity;
extern EntitySpec Level1Stage1Building4Entity;
extern EntitySpec Level1Stage1Building6Entity;
extern EntitySpec Level1Stage1Building7Entity;
extern EntitySpec Level1Stage1Building8Entity;
extern EntitySpec Level1Stage1Building9AEntity;
extern EntitySpec Level1Stage1Building9BEntity;
extern EntitySpec Level1Stage1Building10Entity;
extern EntitySpec Level1Stage1Building11Entity;
extern EntitySpec ManoloEm;
extern EntitySpec PlaygroundEntity;
extern EntitySpec PlaygroundSignEntity;
extern EntitySpec Statue1Entity;
extern EntitySpec Tree1Entity;
extern EntitySpec TreeBg1Entity;

extern CharSetSpec PunkCharset;
extern CharSetSpec PunkBlackCharset;
extern CharSetSpec PunkDyingCharset;
extern CharSetSpec PunkDyingBlackCharset;
extern CharSetSpec Car1Charset;
extern CharSetSpec FlowerPotCharset;
extern CharSetSpec GuiCharset;
extern CharSetSpec CaptainCharset;
extern CharSetSpec CaptainBlackCharset;
extern CharSetSpec HoverCarCharset;
extern CharSetSpec CityBg1Charset;

extern TextureSpec CityBg1ATexture;
extern TextureSpec CityBg1BTexture;
extern TextureSpec PunkTexture;
extern TextureSpec Car1Texture;
extern TextureSpec GuiTexture;
extern TextureSpec FlowerPotTexture;
extern TextureSpec CaptainTexture;
extern TextureSpec CaptainBlackTexture;
extern TextureSpec HoverCarTexture;
extern TextureSpec PunkBlackTexture;
extern TextureSpec PunkDyingBlackTexture;

extern Size collision_16_224_64;
extern Size collision_384_16_64;
extern Size collision_3608_16_64;

extern Sound CapitanoSong;


//---------------------------------------------------------------------------------------------------------
//											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMSpec Level1Stage1StChildren[] =
{
	{&CollisionCl,						{  -8,  96,    0,   0},		0, NULL, NULL, (void*)&collision_16_224_64, false}, // left border

	{&CloudsBackEntity,					{  32,   8,  352,   0},		0, NULL, NULL, NULL, true},
	{&CloudsFrontEntity,					{   0,   0,  320,   0},		0, NULL, NULL, NULL, true},
	{&CityBg1Entity,						{-256,  35,  256,   0},		0, NULL, NULL, NULL, true},

	{&CityFloorEntity,					{   0, 172,    0,   0},		0, NULL, NULL, NULL, true},

	{&CITY_FLOOR_CollisionCl,			{1804, 200,    0,   0},		0, NULL, NULL, (void*)&collision_3608_16_64, true},

	{&PunkEm,							{ 586, 147,    0,   0},		0, NULL, NULL, (void*)-2, false},
	{&AttackDogEm,					{830, 152,    0,   0},		0, NULL, NULL, (void*)-5, false},
	{&PunkEm,							{1130, 147,    0,   0},		0, NULL, NULL, (void*)-3, false},
	{&PunkEm,							{1330, 147,    0,   0},		0, NULL, NULL, (void*)-3, false},
	{&AttackDogEm,					{1530, 152,    0,   0},		0, NULL, NULL, (void*)-4, false},
	{&PunkEm,							{1670, 147,    0,   0},		0, NULL, NULL, (void*)-3, false},
	{&PunkEm,							{2280, 147,    0,   0},		0, NULL, NULL, (void*)-4, false},
	{&PunkEm,							{2460, 147,    0,   0},		0, NULL, NULL, (void*)-3, false},

	{&HoverCarEm,						{2160, 114,    0,   0},		0, NULL, NULL, NULL, false},

	{&Car1Entity,							{ 500, 166,    0,   0},		0, NULL, NULL, NULL, false},
	{&Car1Entity,							{1040, 166,    0,   0},		0, NULL, NULL, NULL, false},
	{&Car1Entity,							{3608, 166,    0,   0},		0, NULL, NULL, NULL, false},
	{&Car1Entity,							{4810, 166,    0,   0},		0, NULL, NULL, NULL, false},

	{&ComicNivel1Entity,					{ 192,  92,   -2,   0},		0, NULL, NULL, NULL, false},

	{&Tree1Entity,						{  24, 108,   24,   0},		0, NULL, NULL, NULL, false},

	{&Lantern1Entity,						{  32, 137,    0,   0},		0, NULL, NULL, NULL, false},
	{&Level1Stage1Building1Entity,	{ 200,  80,    0,   0},		0, NULL, NULL, NULL, false},

	{&Tree1Entity,						{ 350, 108,   24,   0},		0, NULL, NULL, NULL, false},

	{&Level1Stage1Building2Entity,	{ 518, 126,    0,   0},		0, NULL, NULL, NULL, false},
	{&Lantern1Entity,						{ 616, 137,    0,   0},		0, NULL, NULL, NULL, false},
	{&CarBg1Entity,						{ 664, 136,   16,   0},		0, NULL, NULL, NULL, false},
	{&TreeBg1Entity,						{ 698, 112,   32,   0},		0, NULL, NULL, NULL, false},

	{&Level1Stage1Building3Entity,	{ 808,  80,    0,   0},		0, NULL, NULL, NULL, false},
	{&GrannyPe,						{ 765,  50,    0,   0},		0, NULL, NULL, NULL, false},
	//{&GrannyPe,						{ 852,  50,    0,   0},		0, NULL, NULL, NULL, false},

	{&Level1Stage1Building4Entity,	{ 996, 102,    0,   0},		0, NULL, NULL, NULL, false},

	{&BushBg1Entity,						{1138, 112,   64,   0},		0, NULL, NULL, NULL, false},
	{&Lantern1Entity,						{1166, 137,    0,   0},		0, NULL, NULL, NULL, false},

	{&Tree1Entity,						{1256, 104,    0,   0},		0, NULL, NULL, NULL, false},
	{&PlaygroundSignEntity,				{1288,  76,    0,   0},		0, NULL, NULL, NULL, false},
	{&Tree1Entity,						{1312,  94,    0,   0},		0, NULL, NULL, NULL, false},
	{&FenceEntity,							{1376, 135,    0,   0},		0, NULL, NULL, NULL, false},
	{&PlaygroundEntity,					{1390,  92,    0,   0},		0, NULL, NULL, NULL, false},
	{&Statue1Entity,						{1486,  80,    0,   0},		0, NULL, NULL, NULL, false},
	{&BushBg2Entity,						{1572, 112,   64,   0},		0, NULL, NULL, NULL, false},

	{&Lantern1Entity,						{1570, 137,    0,   0},		0, NULL, NULL, NULL, false},

	{&Level1Stage1Building6Entity,	{1746,  79,    0,   0},		0, NULL, NULL, NULL, false},
	{&GrannyPe,						{1784,  31,    0,   0},		0, NULL, NULL, NULL, false},

	{&Level1Stage1Building7Entity,	{1920, 100,    0,   0},		0, NULL, NULL, NULL, false},

	{&Level1Stage1Building8Entity,	{2106,  80,    0,   0},		0, NULL, NULL, NULL, false},
	{&Clothes1Entity,						{2253,  39,    0,   0},		0, NULL, NULL, NULL, false},
	{&BikeEntity,							{2288, 144,    0,   0},		0, NULL, NULL, NULL, false},

	{&Level1Stage1Building9AEntity,	{2406,  80,    0,   0},		0, NULL, NULL, NULL, false},
	{&Level1Stage1Building9BEntity,	{2662,  80,    0,   0},		0, NULL, NULL, NULL, false},
	{&GrannyPe,						{2340,  46,    0,   0},		0, NULL, NULL, NULL, false},

	{&GrannyPe,						{2552,  18,    0,   0},		0, NULL, NULL, NULL, false},

	{&Level1Stage1Building10Entity,	{2978,  80,    0,   0},		0, NULL, NULL, NULL, false},
	{&GarageCarEntity,					{2914, 140,    0,   0},		0, NULL, NULL, NULL, false},
	{&FoldingStandEntity,					{3024, 147,    0,   0},		0, NULL, NULL, NULL, false},
	{&GarageSignEntity,					{3152,  63,    0,   0},		0, NULL, NULL, NULL, false},

	{&ManoloEm,						{3136, 142,    0,   0},		0, NULL, NULL, NULL, false},

	{&Lantern1Entity,						{3238, 137,    0,   0},		0, NULL, NULL, NULL, false},
	{&Tree1Entity,						{3254, 109,   24,   0},		0, NULL, NULL, NULL, false},
	{&BenchEntity,							{3318, 143,    0,   0},		0, NULL, NULL, NULL, false},

	{&Tree1Entity,						{3356, 109,   24,   0},		0, NULL, NULL, NULL, false},

	{&HighwaymenEntity,					{3440, 144,    0,   0},		0, NULL, NULL, NULL, false},
	{&StopYouCannotPassEntity,			{3444,  96,    0,   0},		0, NULL, NULL, NULL, false},

	{&BushBg1Entity,						{3486, 128,   64,   0},		0, NULL, NULL, NULL, false},

	{&CarBg2Entity,						{3579, 141,    0,   0},		0, NULL, NULL, NULL, false},
	{&Level1Stage1Building11Entity,	{3583,  68,    0,   0},		0, NULL, NULL, NULL, false},
	{&Level1Stage1MainExitXp,		{3600,  40,    0,   0},		0, NULL, NULL, NULL, false},

	{&CollisionCl,						{3616,  96,    0,   0},		0, NULL, NULL, (void*)&collision_16_224_64, false}, // right border

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1Stage1StUiChildren[] =
{
	//{&CityFloor3dEntity, 				{ 192, 172,  16,   0}, 		0, NULL, NULL, NULL, true},
	{&Level1MissionEntity,				{  60, 204,  -2,   0},		0, NULL, NULL, NULL, false},
	{&GuiEntity, 							{ 332, 204,  -1,   0}, 		0, NULL, NULL, NULL, true},
	{&LowPowerIndicatorEntity, 			{ 265, 215,  -2,   0}, 		0, NULL, NULL, NULL, true},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
//											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMSpec* const Level1Stage1StFonts[] =
{
	NULL
};

CharSetROMSpec* const Level1Stage1StCharsets[] =
{
	&PunkCharset,
	&PunkBlackCharset,
	NULL
};

TextureSpec* const Level1Stage1StTextures[] =
{
	NULL
};

const PostProcessingEffect Level1Stage1St_POST_PROCESSING_EFFECTS[] =
{
	NULL
};

SoundROM* const Level1Stage1St_BGM[] =
{
	&CapitanoSong,
	NULL,
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMSpec Level1Stage1St =
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
		32,
		// unload padding
		12,
		// streaming amplitude
		8,
		// particle removal delay cycles
		4,
		// deferred
		false,
	},

	// rendering
	{
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
		(FontSpec**)Level1Stage1StFonts,

		// char sets to preload
		(CharSetSpec**)Level1Stage1StCharsets,

		// textures to preload
		(TextureSpec**)Level1Stage1StTextures,

		// background sounds
		(Sound**)Level1Stage1St_BGM,
	},

	// entities
	{
		// ui
		{
			(PositionedEntity*)Level1Stage1StUiChildren,
			__TYPE(UIContainer),
		},

		// children
		(PositionedEntity*)Level1Stage1StChildren,
	},

	// post processing effects
	(PostProcessingEffect*)Level1Stage1St_POST_PROCESSING_EFFECTS,
};


//---------------------------------------------------------------------------------------------------------
//												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMSpec Level1Stage1MainEntryPoint =
{
	// the stage to load
	(StageSpec*)&Level1Stage1St,

	// starting position (x, y, z)
	{64, 133, CAPTAIN_DSPL},

	// facing direction of the captain
	__RIGHT,

	// whether this entry point acts as a checkpoint
	true,
};
