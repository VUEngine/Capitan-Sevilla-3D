/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef MACROS_H_
#define MACROS_H_


//---------------------------------------------------------------------------------------------------------
//												DEFINES
//---------------------------------------------------------------------------------------------------------

// general
#define COINS_PER_LEVEL		64
#define LEVELS_IN_GAME		1

// layers
#define CAPTAIN_DSPL			1

// physics
#define NO_FRICTION 		0
#define FLOOR_FRICTION 		0.75f
#define FLOOR_BOUNCINESS 	0.0f

// entity collision types
enum PlatformerTypes
{
	kCaptain = kTypeNone + 1,
	kShape,
	kTopShape,
	kKillShape,
	kLift,
	kItemDuck,
	kEnemy,
	kMessage,
	kFloor,
	kEnemyWall,
	kGumProjectile,
	kEnemyProjectile,
	kMovingPlatform,
	kStageExitPoint,
};

// entity collision layers
enum CollisionLayers
{
    kSolidLayer		 					= 1 << (kLayerNone + 0),
    kEnemiesLayer						= 1 << (kLayerNone + 1),
    kPlayerLayer						= 1 << (kLayerNone + 2),
    kParticlesLayer						= 1 << (kLayerNone + 3),
    kItemsLayer							= 1 << (kLayerNone + 4),
    kCollectablesLayer					= 1 << (kLayerNone + 5),
    kTriggersLayer						= 1 << (kLayerNone + 6),
    kMovingPlatformsLayer				= 1 << (kLayerNone + 7),
    kMessageLayer						= 1 << (kLayerNone + 8),
	kEnemiesWallsLayer					= 1 << (kLayerNone + 9),
    kAllLayers							= 0xFFFFFFFF,
};


#endif
