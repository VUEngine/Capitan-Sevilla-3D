///////////////////////////////////////////////////////////////////////////////////////////////////////////
//                              THIS FILE WAS AUTO-GENERATED - DO NOT EDIT                               //
///////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CONFIG_H_
#define CONFIG_H_


//---------------------------------------------------------------------------------------------------------
//												PLUGINS
//---------------------------------------------------------------------------------------------------------

#include "pluginsConfig.h"


//---------------------------------------------------------------------------------------------------------
//											COMMUNICATIONS
//---------------------------------------------------------------------------------------------------------

// Enable communications at the start of the game
#undef __ENABLE_COMMUNICATIONS


//---------------------------------------------------------------------------------------------------------
//											DEBUGGING / PROFILING
//---------------------------------------------------------------------------------------------------------

// print memory pool's status
#undef __SHOW_MEMORY_POOL_STATUS
#undef __SHOW_DETAILED_MEMORY_POOL_STATUS

// Enable profiler
#undef __ENABLE_PROFILER

// print frame rate
#undef __PRINT_FRAMERATE

// alert stack overflows
#undef __SHOW_STACK_OVERFLOW_ALERT

// enable streaming's profiling
#undef __PROFILE_STREAMING

// show streaming's profiling during game
#undef __SHOW_STREAMING_PROFILING

// dimm screen to make it easier to read the profiling output
#undef __DIMM_FOR_PROFILING

// alert vip's overtime
#undef __SHOW_VIP_OVERTIME_COUNT

// stack headroom
#define __STACK_HEADROOM								500


//---------------------------------------------------------------------------------------------------------
//											DEBUGGING TOOLS
//---------------------------------------------------------------------------------------------------------

// If tools already defined, enable all
#ifdef __TOOLS

// tools
#ifndef __DEBUG_TOOLS
#define __DEBUG_TOOLS
#endif

#ifndef __STAGE_EDITOR
#define __STAGE_EDITOR
#endif

#ifndef __ANIMATION_INSPECTOR
#define __ANIMATION_INSPECTOR
#endif

#ifndef __SOUND_TEST
#define __SOUND_TEST
#endif

#endif

// Enable different settings for each tool
#ifdef __DEBUG_TOOLS
#ifndef __TOOLS
#define __TOOLS
#endif

#endif

#ifdef __STAGE_EDITOR
#ifndef __TOOLS
#define __TOOLS
#endif
#endif

#ifdef __ANIMATION_INSPECTOR
#ifndef __TOOLS
#define __TOOLS
#endif
#endif

#ifdef __SOUND_TEST
#ifndef __TOOLS
#define __TOOLS
#endif
#endif


//---------------------------------------------------------------------------------------------------------
//											ROM HEADER INFO
//---------------------------------------------------------------------------------------------------------

// game title (20 chars) 	 ####################
#define __GAME_TITLE		"Capitan Sevilla 3D  "
// maker code (2 chars)		 ##
#define __MAKER_CODE		"TV"
// game code (4 chars)		 ####
#define __GAME_CODE			"VCSM"
// revision (1.x)			 #
#define __ROM_VERSION		 0


//---------------------------------------------------------------------------------------------------------
//											OPTICS / PROJECTION
//---------------------------------------------------------------------------------------------------------

// screen width in pixels
#define __SCREEN_WIDTH								384

// screen height in pixels
#define __SCREEN_HEIGHT								224

// screen depth in pixels
#define __SCREEN_DEPTH								2048

// distance from player's eyes to the virtual screen
#define __DISTANCE_EYE_SCREEN						384

// maximum x view distance (depth) (power of two)
#define __MAXIMUM_X_VIEW_DISTANCE					2048

// maximum y view distance (depth) (power of two)
#define __MAXIMUM_Y_VIEW_DISTANCE					16384

// distance between eyes
#define __BASE_FACTOR								32

// player's eyes' horizontal position
#define __HORIZONTAL_VIEW_POINT_CENTER				192

// player's eyes' vertical position
#define __VERTICAL_VIEW_POINT_CENTER				112

// parallax values are divide by this factor to control their strength
#define __PARALLAX_CORRECTION_FACTOR				4

// affects the strength of the scaling
#define __SCALING_MODIFIER_FACTOR					0.2f

// minimum number of pixels that the camera can move
#define __CAMERA_MINIMUM_DISPLACEMENT_PIXELS_POWER	1


//---------------------------------------------------------------------------------------------------------
//											FRAME RATE CONTROL
//---------------------------------------------------------------------------------------------------------

// when defined, the engine skips to the next game frame when the VIP's GAMESTART interrupt is fired
// beforethe current game frame is done
#define __FORCE_VIP_SYNC

// timer resolution
#define __TIMER_RESOLUTION							10

// __FRAME_CYCLE = 0 means __TARGET_FPS = 50
// __FRAME_CYCLE = 1 means __TARGET_FPS = 25
#define	__FRAME_CYCLE								0

// target frames per second
#define __TARGET_FPS 								(50 >> __FRAME_CYCLE)

// milliseconds that must take to complete a game cycle
#define __GAME_FRAME_DURATION						(__MILLISECONDS_PER_SECOND / __TARGET_FPS)

// target frames per second
#define __OPTIMUM_FPS 								(__TARGET_FPS >> __FRAME_CYCLE)

// define to dispatch the delayed messages every other game frame cycle
#undef __RUN_DELAYED_MESSAGES_DISPATCHING_AT_HALF_FRAME_RATE


//---------------------------------------------------------------------------------------------------------
//												ANIMATION
//---------------------------------------------------------------------------------------------------------

// maximum length of an animation function's name
#define __MAX_ANIMATION_FUNCTION_NAME_LENGTH		16

// maximum number of frames per animation function
#define __MAX_FRAMES_PER_ANIMATION_FUNCTION			48

// maximum number of animation functions per description
#define __MAX_ANIMATION_FUNCTIONS					32


//---------------------------------------------------------------------------------------------------------
//												MEMORY POOL
//---------------------------------------------------------------------------------------------------------

// reset to 0 each byte of each free block on resetting game
// only use for debugging, proper object's initialization must make this macro unnecessary
#undef __MEMORY_POOL_CLEAN_UP

#undef __MEMORY_POOLS
#define __MEMORY_POOLS								11

#undef __MEMORY_POOL_ARRAYS
#define __MEMORY_POOL_ARRAYS \
	__BLOCK_DEFINITION(168, 5) \
	__BLOCK_DEFINITION(156, 12) \
	__BLOCK_DEFINITION(148, 52) \
	__BLOCK_DEFINITION(120, 40) \
	__BLOCK_DEFINITION(112, 40) \
	__BLOCK_DEFINITION(88, 60) \
	__BLOCK_DEFINITION(76, 40) \
	__BLOCK_DEFINITION(44, 20) \
	__BLOCK_DEFINITION(32, 340) \
	__BLOCK_DEFINITION(24, 600) \
	__BLOCK_DEFINITION(20, 400) \

#undef __SET_MEMORY_POOL_ARRAYS
#define __SET_MEMORY_POOL_ARRAYS \
	__SET_MEMORY_POOL_ARRAY(168) \
	__SET_MEMORY_POOL_ARRAY(156) \
	__SET_MEMORY_POOL_ARRAY(148) \
	__SET_MEMORY_POOL_ARRAY(120) \
	__SET_MEMORY_POOL_ARRAY(112) \
	__SET_MEMORY_POOL_ARRAY(88) \
	__SET_MEMORY_POOL_ARRAY(76) \
	__SET_MEMORY_POOL_ARRAY(44) \
	__SET_MEMORY_POOL_ARRAY(32) \
	__SET_MEMORY_POOL_ARRAY(24) \
	__SET_MEMORY_POOL_ARRAY(20) \

// percentage (0-100) above which the memory pool's status shows the pool usage
#define __MEMORY_POOL_WARNING_THRESHOLD				85


//---------------------------------------------------------------------------------------------------------
//												SRAM
//---------------------------------------------------------------------------------------------------------

// amount of available sram space, in bytes
// • the vb allows up to 16 mb, but all known carts support only 8 kb of sram
#define __TOTAL_SAVE_RAM 							8192


//---------------------------------------------------------------------------------------------------------
//											CHAR MANAGEMENT
//---------------------------------------------------------------------------------------------------------

// total number of available chars in char memory
#define __CHAR_MEMORY_TOTAL_CHARS 					2048


//---------------------------------------------------------------------------------------------------------
//											SPRITE MANAGEMENT
//---------------------------------------------------------------------------------------------------------

// total number of layers (basically the number of worlds)
#define __TOTAL_LAYERS								32

// Account for VIP's design to draw 8 pixel when BGMAP WORLD's height is less than 8
#define __HACK_BGMAP_SPRITE_HEIGHT


//---------------------------------------------------------------------------------------------------------
//											TEXTURE MANAGEMENT
//---------------------------------------------------------------------------------------------------------

// total number of bgmap segments
#define __TOTAL_NUMBER_OF_BGMAPS_SEGMENTS 			11

// number of segments for param tables
#define __PARAM_TABLE_SEGMENTS						1

// bgmap segments to use (1 for printing)
#define __MAX_NUMBER_OF_BGMAPS_SEGMENTS 			(__TOTAL_NUMBER_OF_BGMAPS_SEGMENTS - __PARAM_TABLE_SEGMENTS)

// number of bgmap specs in each bgmap segment
#define __NUM_BGMAPS_PER_SEGMENT 					16

// printing area
#define __PRINTING_BGMAP_X_OFFSET					0
#define __PRINTING_BGMAP_Y_OFFSET					(64 * 8 - __SCREEN_HEIGHT)
#define __PRINTING_BGMAP_PARALLAX_OFFSET			0
#define __PRINTABLE_BGMAP_AREA 						1792


//---------------------------------------------------------------------------------------------------------
//												PARAM TABLE
//---------------------------------------------------------------------------------------------------------

// maximum possible scale: affects param table allocation space
#define __MAXIMUM_SCALE								2

// maximum number of rows to write on each call to affine calculation functions
#define __MAXIMUM_AFFINE_ROWS_PER_CALL				16


//---------------------------------------------------------------------------------------------------------
//												PHYSICS
//---------------------------------------------------------------------------------------------------------

#define __GRAVITY									19.6f

// number of bodies to check for gravity on each cycle
#define __BODIES_TO_CHECK_FOR_GRAVITY				10

// divisor to speed up physics simulations, bigger numbers equal faster computations
#define __PHYSICS_TIME_ELAPSED_DIVISOR				2

// thresholds to stop bodies
#define __STOP_VELOCITY_THRESHOLD					__PIXELS_TO_METERS(8)
#define __STOP_BOUNCING_VELOCITY_THRESHOLD 			__PIXELS_TO_METERS(48)

// maximum bounciness coefficient allowed
#define __MAXIMUM_BOUNCINESS_COEFFICIENT			1.0f

#define __FRICTION_FORCE_FACTOR_POWER				2


//---------------------------------------------------------------------------------------------------------
//												SOUND
//---------------------------------------------------------------------------------------------------------

#define __LEFT_EAR_CENTER							144
#define __RIGHT_EAR_CENTER							240

// affects the amount of attenuation caused by the distance between the x coordinate and each ear's
// position defined by __LEFT_EAR_CENTER and __RIGHT_EAR_CENTER
#define __SOUND_STEREO_HORIZONTAL_ATTENUATION_FACTOR		50
#define __SOUND_STEREO_VERTICAL_ATTENUATION_FACTOR			50


//---------------------------------------------------------------------------------------------------------
//											BRIGHTNESS
//---------------------------------------------------------------------------------------------------------

// default brightness settings, actual values are set in stage specs
// • for a nice progression, each shade should be about twice as big as the previous one
// • _BRIGHT_RED must be larger than _DARK_RED + _MEDIUM_RED
#define __BRIGHTNESS_DARK_RED						32
#define __BRIGHTNESS_MEDIUM_RED						64
#define __BRIGHTNESS_BRIGHT_RED						128

// default delay between steps in fade effect
#define __FADE_DELAY								8

// defaul step increment in fade transitions
#define __CAMERA_EFFECT_FADE_INCREMENT				8

//---------------------------------------------------------------------------------------------------------
//											COLOR PALETTES
//---------------------------------------------------------------------------------------------------------

#define __PRINTING_PALETTE							0

// default palette values, actual values are set in stage specs
#define __BGMAP_PALETTE_0							0b11100100
#define __BGMAP_PALETTE_1							0b11100000
#define __BGMAP_PALETTE_2							0b10010000
#define __BGMAP_PALETTE_3							0b01010000

#define __OBJECT_PALETTE_0							0b11100100
#define __OBJECT_PALETTE_1							0b11100000
#define __OBJECT_PALETTE_2							0b10010000
#define __OBJECT_PALETTE_3							0b01010000


//---------------------------------------------------------------------------------------------------------
//										RANDOM NUMBER GENERATION
//---------------------------------------------------------------------------------------------------------

#undef __ADD_USER_INPUT_AND_TIME_TO_RANDOM_SEED


//---------------------------------------------------------------------------------------------------------
//												EXCEPTIONS
//---------------------------------------------------------------------------------------------------------

// camera coordinates for the output of exceptions
#define __EXCEPTION_COLUMN							0
#define __EXCEPTION_LINE							0


//---------------------------------------------------------------------------------------------------------
//												  HACKS
//---------------------------------------------------------------------------------------------------------



#endif