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
#define LAYER_INCREMENT		64
#define SORT_INCREMENT		1
#define LAYER_0 			0
#define LAYER_1 			(LAYER_0 + LAYER_INCREMENT)
#define LAYER_2 			(LAYER_1 + LAYER_INCREMENT)
#define LAYER_3 			(LAYER_2 + LAYER_INCREMENT)
#define LAYER_4 			(LAYER_3 + LAYER_INCREMENT)
#define LAYER_5 			(LAYER_4 + LAYER_INCREMENT)

#define LAYER_0_ENEMIES 		(LAYER_0 + 0)
#define LAYER_0_ITEMS 			(LAYER_0 + 0)
#define LAYER_0_DECORATIONS 	(LAYER_0 + 0)
#define LAYER_0_PARTICLES		(LAYER_0)
#define LAYER_0_BACKGROUND		(LAYER_0 + 24)
#define LAYER_0_FOREGROUND		(LAYER_0)
#define LAYER_0_FOREGROUND_POP	(LAYER_0 - 12)

#define LAYER_0_HERO_DISPLACEMENT		 		-(SORT_INCREMENT * 3)
#define LAYER_0_ENEMIES_DISPLACEMENT	 		(SORT_INCREMENT * 2)
#define LAYER_0_ITEMS_DISPLACEMENT 				(SORT_INCREMENT * 3)
#define LAYER_0_DECORATIONS_DISPLACEMENT 		(SORT_INCREMENT * 3)
#define LAYER_0_PARTICLES_DISPLACEMENT			(SORT_INCREMENT * 1)
#define LAYER_0_BACKGROUND_DISPLACEMENT			(SORT_INCREMENT * 0)
#define LAYER_0_FOREGROUND_DISPLACEMENT			-(SORT_INCREMENT * 0)

#define LAYER_2_ENEMIES 	LAYER_2
#define LAYER_2_ITEMS 		LAYER_2
#define LAYER_2_PARTICLES	LAYER_2
#define LAYER_2_BACKGROUND	LAYER_2
#define LAYER_2_FOREGROUND	LAYER_2

#define LAYER_2_ENEMIES_DISPLACEMENT 	(SORT_INCREMENT * 0)
#define LAYER_2_ITEMS_DISPLACEMENT 		(SORT_INCREMENT * 0)
#define LAYER_2_PARTICLES_DISPLACEMENT	(SORT_INCREMENT * 3)
#define LAYER_2_BACKGROUND_DISPLACEMENT	(SORT_INCREMENT * 4)
#define LAYER_2_FOREGROUND_DISPLACEMENT	(SORT_INCREMENT * 0)

#define HERO_PARALLAX_DISPLACEMENT								1
#define ENEMIES_PARALLAX_DISPLACEMENT 							1
#define ITEMS_PARALLAX_DISPLACEMENT 							1
#define PARTICLES_PARALLAX_DISPLACEMENT							0
#define BACKGROUND_PARALLAX_DISPLACEMENT						0
#define FOREGROUND_PARALLAX_DISPLACEMENT						0
#define DECORATIONS_PARALLAX_DISPLACEMENT						1
#define LAYER_2_FOREGROUND_PARALLAX_DISPLACEMENT				1

// physics
#define NO_FRICTION 		0
#define FLOOR_FRICTION 		0.75f
#define FLOOR_ELASTICITY 	0.0f

// entity collision types
enum PlatformerTypes
{
	kHero = kNoType + 1,
	kShape,
	kTopShape,
	kNotShape,
	kHit,
	kFloor,
	kMovingPlatform,
};

enum CollisionLayers
{
    kSolidLayer		 					= 1 << (kNoLayer + 0), 	// hex 00000001
    kEnemiesLayer						= 1 << (kNoLayer + 1), 	// hex 00000002
    kPlayerLayer						= 1 << (kNoLayer + 2), 	// hex 00000004
    kParticlesLayer						= 1 << (kNoLayer + 3), 	// hex 00000008
    kItemsLayer							= 1 << (kNoLayer + 4), 	// hex 00000010
    kCollectablesLayer					= 1 << (kNoLayer + 5), 	// hex 00000020
    kTriggersLayer						= 1 << (kNoLayer + 6), 	// hex 00000040
    kMovingPlatformsLayer				= 1 << (kNoLayer + 7), 	// hex 00000040
    kAllLayers							= 0xFFFFFFFF,
};


#endif
