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
	kCaptain = kNoType + 1,
	kShape,
	kTopShape,
	kKillShape,
	kLift,
	kItemSausage,
	kEnemy,
	kMessage,
	kFloor,
	kGumProjectile,
	kEnemyProjectile,
	kMovingPlatform,
	kStageExitPoint,
};

// entity collision layers
enum CollisionLayers
{
    kSolidLayer		 					= 1 << (kNoLayer + 0),
    kEnemiesLayer						= 1 << (kNoLayer + 1),
    kPlayerLayer						= 1 << (kNoLayer + 2),
    kParticlesLayer						= 1 << (kNoLayer + 3),
    kItemsLayer							= 1 << (kNoLayer + 4),
    kCollectablesLayer					= 1 << (kNoLayer + 5),
    kTriggersLayer						= 1 << (kNoLayer + 6),
    kMovingPlatformsLayer				= 1 << (kNoLayer + 7),
    kMessageLayer						= 1 << (kNoLayer + 8),
    kAllLayers							= 0xFFFFFFFF,
};


#endif
