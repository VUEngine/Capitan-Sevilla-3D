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
#include <PlatformerLevelState.h>
#include <Hero.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods

//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define SAVE_STAMP			"VUEngine"
#define SAVE_STAMP_LENGTH	8

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

} SaveData;


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------





singleton class ProgressManager : Object
{
	/* time in current level */
	u32 currentLevelTime;
	/* time in current level at last checkpoint */
	u32 checkpointCurrentLevelTime;
	/* bitstring that holds collected item flags */
	u16 collectedItems;
	/* bitstring that holds collected item flags at last checkpoint */
	u16 checkpointCollectedItems;
	/* flag that tells if sram is available on the current cartridge */
	bool sramAvailable;
	/* hero's current energy */
	u8 heroCurrentEnergy;

	static ProgressManager getInstance();
	bool getAutomaticPauseStatus();
	u32  getCurrentLevelTime();
	u8   getHeroCurrentEnergy();
	bool getItemStatus(u16 itemNumber);
	u8   getLanguage();
	void initialize();
	void loadCheckPointData();
	void setAutomaticPauseStatus(u8 automaticPause);
	void setCheckPointData();
	bool setItemStatus(u16 itemNumber, bool taken);
	void setLanguage(u8 languageId);
	void resetCurrentLevelProgress();
}


#endif
