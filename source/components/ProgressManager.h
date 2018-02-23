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

#ifndef PROGRESS_MANAGER_H_
#define PROGRESS_MANAGER_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Object.h>
#include <Hero.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define ProgressManager_METHODS(ClassName)																\
		Object_METHODS(ClassName)																		\

// declare the virtual methods which are redefined
#define ProgressManager_SET_VTABLE(ClassName)															\
		Object_SET_VTABLE(ClassName)																	\

// declare class
__CLASS(ProgressManager);

// declare class attributes
#define ProgressManager_ATTRIBUTES																		\
		/* super's attributes */																		\
		Object_ATTRIBUTES																				\
		/* time in current level */																		\
		u32 currentLevelTime;																			\
		/* time in current level at last checkpoint */													\
		u32 checkpointCurrentLevelTime;																	\
		/* best time in current level */																\
		u32 currentLevelBestTime;																		\
		/* bitstrings that hold collected coin flags */													\
		u32 collectedCoins[2];																			\
		/* bitstrings that hold collected coin flags at last checkpoint */								\
		u32 checkpointCollectedCoins[2];																\
		/* bitstring that holds collected item flags */													\
		u16 collectedItems;																				\
		/* bitstring that holds collected item flags at last checkpoint */								\
		u16 checkpointCollectedItems;																	\
		/* flag that tells if the hero has collected the current level's key */							\
		bool heroHasKey;																				\
		/* flag that tells if the hero has collected the current level's key at last checkpoint */		\
		bool checkpointHeroHasKey;																		\
		/* flag that tells if sram is available on the current cartridge */								\
		bool sramAvailable;																				\
		/* hero's current energy */																		\
		u8 heroCurrentEnergy;																			\
		/* hero's currently active power-up */															\
		u8 heroCurrentPowerUp;																			\


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define SAVE_STAMP								"VUEngine"
#define SAVE_STAMP_LENGTH						8

typedef struct LevelStatus
{
	// flag that tells whether the level was ever completed
	u8 levelCompleted;

	// number of collected coins in this level
	u8 numberOfCollectedCoins;

	// the best time the level was ever completed in
	u32 bestTime;

	// bitstrings that hold collected coin flags
	// 0 = not collected, 1 = collected
	u32 collectedCoins[2];

} LevelStatus;

// this struct is never instantiated, its sole purpose is to determine offsets of its members.
// therefore it acts as kind of like a map of sram content.
typedef struct SaveData
{
	// flag to know if there is data saved
	u8 saveStamp[SAVE_STAMP_LENGTH];

	// checksum over sram content to prevent save data manipulation
	u32 checksum;

	// active language id
	u8 languageId;

	// auto pause status (0: on, 1: off)
	u8 autoPauseStatus;

	// total number of completed levels
	u8 numberOfCompletedLevels;

	// total number of collected coins
	u16 numberOfCollectedCoins;

	// completion statuses for every level in the game
	LevelStatus levelStatuses[LEVELS_IN_GAME];

} SaveData;


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

ProgressManager ProgressManager_getInstance();

void ProgressManager_clearProgress(ProgressManager this);
void ProgressManager_destructor(ProgressManager this);
bool ProgressManager_getAutomaticPauseStatus(ProgressManager this);
bool ProgressManager_getCoinStatus(ProgressManager this, u16 itemNumber);
u32  ProgressManager_getCurrentLevelBestTime(ProgressManager this);
u8   ProgressManager_getCurrentLevelNumberOfCollectedCoins(ProgressManager this);
u32  ProgressManager_getCurrentLevelTime(ProgressManager this);
u8   ProgressManager_getHeroCurrentEnergy(ProgressManager this);
u8   ProgressManager_getHeroCurrentPowerUp(ProgressManager this);
bool ProgressManager_getItemStatus(ProgressManager this, u16 itemNumber);
u8   ProgressManager_getLanguage(ProgressManager this);
u16  ProgressManager_getTotalNumberOfCollectedCoins(ProgressManager this);
bool ProgressManager_hasProgress(ProgressManager this);
bool ProgressManager_heroHasKey(ProgressManager this);
void ProgressManager_loadCheckPointData(ProgressManager this);
void ProgressManager_setAutomaticPauseStatus(ProgressManager this, u8 automaticPause);
void ProgressManager_setCheckPointData(ProgressManager this);
bool ProgressManager_setCoinStatus(ProgressManager this, u16 itemNumber, bool taken);
bool ProgressManager_setItemStatus(ProgressManager this, u16 itemNumber, bool taken);
void ProgressManager_setLanguage(ProgressManager this, u8 language);
void ProgressManager_resetCurrentLevelProgress(ProgressManager this);


#endif
