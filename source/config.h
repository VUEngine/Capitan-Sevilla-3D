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
//											DEBUGGING / PROFILING
//---------------------------------------------------------------------------------------------------------

// print memory pool's status
#undef __PRINT_MEMORY_POOL_STATUS
#undef __PRINT_DETAILED_MEMORY_POOL_STATUS

// print frame rate
#undef __PRINT_FRAMERATE

// alert stack overflows
#undef __ALERT_STACK_OVERFLOW

// enable detailed profiling of each of the game's main processes
// • it is more useful when __TIMER_RESOLUTION approaches 1
#undef __PROFILE_GAME

// enable streaming's profiling
#undef __PROFILE_STREAMING

// show games's profiling during game
#undef __SHOW_GAME_PROFILING

// show streaming's profiling during game
#undef __SHOW_STREAMING_PROFILING

// dimm screen to make it easier to read the profiling output
#undef __DIMM_FOR_PROFILING

// print the game's current process while the VIP's frame start and idle interrupts are fired, but the 
// game frame is still pending processes to complete
#undef __PROFILE_GAME_STATE_DURING_VIP_INTERRUPT

// alert vip's overtime
#define __ALERT_VIP_OVERTIME


//---------------------------------------------------------------------------------------------------------
//											DEBUGGING TOOLS
//---------------------------------------------------------------------------------------------------------

#ifdef __TOOLS

// print frame rate
#define __PRINT_FRAMERATE

// enable detailed profiling of each of the game's main processes
// • it is more useful when __TIMER_RESOLUTION approaches 1
#define __PROFILE_GAME

// enable streaming's profiling
#define __PROFILE_STREAMING

// tools
#define __DEBUG_TOOLS
#define __STAGE_EDITOR
#define __ANIMATION_INSPECTOR

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
#define __MAXIMUM_Y_VIEW_DISTANCE					4096

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
#undef __FORCE_VIP_SYNC

// timer resolution
#define __TIMER_RESOLUTION							10

// __FRAME_CYCLE = 0 means __TARGET_FPS = 50
// __FRAME_CYCLE = 1 means __TARGET_FPS = 25
#define	__FRAME_CYCLE								0

// target frames per second
#define __TARGET_FPS 								(50 >> __FRAME_CYCLE)

// milliseconds that must take to complete a game cycle
#define __GAME_FRAME_DURATION						(__MILLISECONDS_IN_SECOND / __TARGET_FPS)

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
	__BLOCK_DEFINITION(164, 1) \
	__BLOCK_DEFINITION(152, 16) \
	__BLOCK_DEFINITION(144, 16) \
	__BLOCK_DEFINITION(116, 40) \
	__BLOCK_DEFINITION(108, 40) \
	__BLOCK_DEFINITION(80, 50) \
	__BLOCK_DEFINITION(68, 60) \
	__BLOCK_DEFINITION(40, 96) \
	__BLOCK_DEFINITION(28, 550) \
	__BLOCK_DEFINITION(20, 700) \
	__BLOCK_DEFINITION(16, 450) \

#undef __SET_MEMORY_POOL_ARRAYS
#define __SET_MEMORY_POOL_ARRAYS \
	__SET_MEMORY_POOL_ARRAY(164) \
	__SET_MEMORY_POOL_ARRAY(152) \
	__SET_MEMORY_POOL_ARRAY(144) \
	__SET_MEMORY_POOL_ARRAY(116) \
	__SET_MEMORY_POOL_ARRAY(108) \
	__SET_MEMORY_POOL_ARRAY(80) \
	__SET_MEMORY_POOL_ARRAY(68) \
	__SET_MEMORY_POOL_ARRAY(40) \
	__SET_MEMORY_POOL_ARRAY(28) \
	__SET_MEMORY_POOL_ARRAY(20) \
	__SET_MEMORY_POOL_ARRAY(16) \

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


//---------------------------------------------------------------------------------------------------------
//											TEXTURE MANAGEMENT
//---------------------------------------------------------------------------------------------------------

// total number of bgmap segments
#define __TOTAL_NUMBER_OF_BGMAPS_SEGMENTS 			14

// bgmap segments to use (leave 2 to allocate param table, 1 for printing)
#define __MAX_NUMBER_OF_BGMAPS_SEGMENTS 			(__TOTAL_NUMBER_OF_BGMAPS_SEGMENTS - 3)

// number of bgmap specs in each bgmap segment
#define __NUM_BGMAPS_PER_SEGMENT 					16

// printing area
#define __PRINTING_BGMAP_X_OFFSET					0
#define __PRINTING_BGMAP_Y_OFFSET					0
#define __PRINTING_BGMAP_Z_OFFSET					0
#define __PRINTABLE_BGMAP_AREA 						1792


//---------------------------------------------------------------------------------------------------------
//												PARAM TABLE
//---------------------------------------------------------------------------------------------------------

// maximum possible scale: affects param table allocation space
#define __MAXIMUM_SCALE								2

// maximum number of rows to write on each call to affine calculation functions
#define __MAXIMUM_AFFINE_ROWS_PER_CALL				16


//---------------------------------------------------------------------------------------------------------
//												STREAMING
//---------------------------------------------------------------------------------------------------------

// number of total calls to the streaming method which completes a cycle
// there are 4 parts for the streaming algorithm:
// 1) unload entities
// 2) select the next entity to load
// 3) create the selected entity
// 4) initialize the loaded entity
#define __STREAM_CYCLE_DURATION						24

// padding to determine if an entity must be loaded/unloaded
// • load pad must always be lower than unload pad!
// • too close values will put the streaming under heavy usage!
#define __ENTITY_LOAD_PAD 							256
#define __ENTITY_UNLOAD_PAD 						312


//---------------------------------------------------------------------------------------------------------
//												PHYSICS
//---------------------------------------------------------------------------------------------------------

#define __GRAVITY									19.6f

// number of bodies to check for gravity on each cycle
#define __BODIES_TO_CHECK_FOR_GRAVITY				10

// divisor to speed up physics simulations, bigger numbers equal faster computations
#define __PHYSICS_TIME_ELAPSED_DIVISOR				2

// thresholds to stop bodies
#define __STOP_VELOCITY_THRESHOLD					__PIXELS_TO_METERS(4)
#define __STOP_BOUNCING_VELOCITY_THRESHOLD 			__PIXELS_TO_METERS(48)


//---------------------------------------------------------------------------------------------------------
//												SOUND
//---------------------------------------------------------------------------------------------------------

// channels per bgms
#define __BGM_CHANNELS								2

// channels per fx
#define __FX_CHANNELS								1

// simultaneous bgms
#define __BGMS										1

// simultaneous fx
#define __FXS										2

#define __TOTAL_SOUNDS								(__BGMS + __FXS)
#define __LEFT_EAR_CENTER							96
#define __RIGHT_EAR_CENTER							288

// affects the amount of attenuation caused by the distance between the x coordinate and each ear's
// position defined by __LEFT_EAR_CENTER and __RIGHT_EAR_CENTER
#define __SOUND_STEREO_ATTENUATION_FACTOR			__F_TO_FIX10_6(0.75f)


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

// how many times the randomSeed function cycles generate a random seed
#define __RANDOM_SEED_CYCLES						2

#undef __ADD_USER_INPUT_AND_TIME_TO_RANDOM_SEED


//---------------------------------------------------------------------------------------------------------
//												EXCEPTIONS
//---------------------------------------------------------------------------------------------------------

// camera coordinates for the output of exceptions
#define __EXCEPTION_COLUMN							0
#define __EXCEPTION_LINE							0


#endif