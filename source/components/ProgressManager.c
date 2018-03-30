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


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <string.h>
#include <stddef.h>

#include <Game.h>
#include <I18n.h>
#include <Error.h>
#include <GameEvents.h>
#include <ProgressManager.h>
#include <SRAMManager.h>
#include <EventManager.h>
#include <Utilities.h>
#include <macros.h>
#include <AutoPauseScreenState.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(ProgressManager, Object);


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void ProgressManager_constructor(ProgressManager this);
bool ProgressManager_verifySaveStamp(ProgressManager this);
u32 ProgressManager_computeChecksum(ProgressManager this);
void ProgressManager_writeChecksum(ProgressManager this);
bool ProgressManager_verifyChecksum(ProgressManager this);
static void ProgressManager_onSecondChange(ProgressManager this, Object eventFirer);
static void ProgressManager_onHitTaken(ProgressManager this, Object eventFirer);
static void ProgressManager_onLevelStarted(ProgressManager this, Object eventFirer);
static void ProgressManager_onLevelCompleted(ProgressManager this, Object eventFirer);
static void ProgressManager_onCheckpointLoaded(ProgressManager this, Object eventFirer);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// it's a singleton
__SINGLETON(ProgressManager);

// class's constructor
static void __attribute__ ((noinline)) ProgressManager_constructor(ProgressManager this)
{
	ASSERT(this, "ProgressManager::constructor: null this");

	// construct base object
	__CONSTRUCT_BASE(Object);

	// init class variables
	this->sramAvailable = false;
	ProgressManager_resetCurrentLevelProgress(this);

	// add event listeners
	Object eventManager = __SAFE_CAST(Object, EventManager_getInstance());
	Object_addEventListener(__SAFE_CAST(Object, PlatformerLevelState_getClock(PlatformerLevelState_getInstance())), __SAFE_CAST(Object, this), (EventListener)ProgressManager_onSecondChange, kEventSecondChanged);
	Object_addEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager_onHitTaken, kEventHitTaken);
	Object_addEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager_onLevelStarted, kEventLevelStarted);
	Object_addEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager_onCheckpointLoaded, kEventCheckpointLoaded);
	Object_addEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager_onLevelCompleted, kEventLevelCompleted);
}

// class's destructor
void ProgressManager_destructor(ProgressManager this)
{
	ASSERT(this, "ProgressManager::destructor: null this");
	ASSERT(EventManager_getInstance(), "ProgressManager::destructor: null eventManager");

	// remove event listeners
	Object eventManager = __SAFE_CAST(Object, EventManager_getInstance());
	Object_removeEventListener(__SAFE_CAST(Object, PlatformerLevelState_getClock(PlatformerLevelState_getInstance())), __SAFE_CAST(Object, this), (EventListener)ProgressManager_onSecondChange, kEventSecondChanged);
	Object_removeEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager_onHitTaken, kEventHitTaken);
	Object_removeEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager_onLevelStarted, kEventLevelStarted);
	Object_removeEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager_onCheckpointLoaded, kEventCheckpointLoaded);
	Object_removeEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager_onLevelCompleted, kEventLevelCompleted);

	// destroy base
	__SINGLETON_DESTROY;
}

void ProgressManager_resetHeroState(ProgressManager this)
{
	this->heroCurrentEnergy = HERO_INITIAL_ENERGY;
}

void ProgressManager_resetCurrentLevelProgress(ProgressManager this)
{
	ProgressManager_resetHeroState(this);

	this->currentLevelTime = 0;
	this->collectedItems = 0;

	this->checkpointCurrentLevelTime = 0;
	this->checkpointCollectedItems = 0;
}

// write then immediately read save stamp to validate sram
bool ProgressManager_verifySaveStamp(ProgressManager this __attribute__ ((unused)))
{
	char saveStamp[SAVE_STAMP_LENGTH];

	// write save stamp
	SRAMManager_save(SRAMManager_getInstance(), (BYTE*)SAVE_STAMP, offsetof(struct SaveData, saveStamp), sizeof(saveStamp));

	// read save stamp
	SRAMManager_read(SRAMManager_getInstance(), (BYTE*)&saveStamp, offsetof(struct SaveData, saveStamp), sizeof(saveStamp));

	return !strncmp(saveStamp, SAVE_STAMP, SAVE_STAMP_LENGTH);
}

u32 ProgressManager_computeChecksum(ProgressManager this __attribute__ ((unused)))
{
	u32 crc32 = ~0;

	// iterate over whole save data, starting right after the previously saved checksum
	int i = (offsetof(struct SaveData, checksum) + sizeof(crc32));
	for(; i < (int)sizeof(SaveData); i++)
	{
		// get the current byte
		u8 currentByte;
		SRAMManager_read(SRAMManager_getInstance(), (BYTE*)&currentByte, i, sizeof(currentByte));

		// loop over all bits of the current byte and add to checksum
		u8 bit = 0;
		for(; bit < sizeof(currentByte); bit++)
		{
			if((crc32 & 1) != GET_BIT(currentByte, bit))
			{
				crc32 = (crc32 >> 1) ^ 0xEDB88320;
			}
			else
			{
				crc32 = (crc32 >> 1);
			}
		}
	}

	return ~crc32;
}

void ProgressManager_writeChecksum(ProgressManager this)
{
	u32 checksum = ProgressManager_computeChecksum(this);
	SRAMManager_save(SRAMManager_getInstance(), (BYTE*)&checksum, offsetof(struct SaveData, checksum), sizeof(checksum));
}

bool ProgressManager_verifyChecksum(ProgressManager this)
{
	u32 computedChecksum = ProgressManager_computeChecksum(this);
	u32 savedChecksum = 0;
	SRAMManager_read(SRAMManager_getInstance(), (BYTE*)&savedChecksum, offsetof(struct SaveData, checksum), sizeof(savedChecksum));

	return (computedChecksum == savedChecksum);
}

void ProgressManager_initialize(ProgressManager this)
{
	ASSERT(this, "ProgressManager::initialize: null this");

	// verify sram validity
	if(ProgressManager_verifySaveStamp(this))
	{
		// set sram available flag
		this->sramAvailable = true;

		// verify saved progress presence and integrity
		if(!ProgressManager_verifyChecksum(this))
		{
			// if no previous save could be verified, completely erase sram to start clean
			SRAMManager_clear(SRAMManager_getInstance(), 0, (int)sizeof(SaveData));

			// write checksum
			ProgressManager_writeChecksum(this);
		}

		// load and set active language
		I18n_setActiveLanguage(I18n_getInstance(), ProgressManager_getLanguage(this));

		// load and set auto pause state
		Game_setAutomaticPauseState(Game_getInstance(), ProgressManager_getAutomaticPauseStatus(this)
			? __SAFE_CAST(GameState, AutoPauseScreenState_getInstance())
			: NULL
		);
	}
}

void ProgressManager_setCheckPointData(ProgressManager this)
{
	ASSERT(this, "ProgressManager::setCheckPoint: null this");

	this->checkpointCurrentLevelTime = this->currentLevelTime;
	this->checkpointCollectedItems = this->collectedItems;
}

void ProgressManager_loadCheckPointData(ProgressManager this)
{
	ASSERT(this, "ProgressManager::setCheckPoint: null this");

	this->currentLevelTime = this->checkpointCurrentLevelTime;
	this->collectedItems = this->checkpointCollectedItems;
}

u8 ProgressManager_getLanguage(ProgressManager this)
{
	ASSERT(this, "ProgressManager::getLanguage: null this");

	u8 languageId = 0;
	if(this->sramAvailable)
	{
		SRAMManager_read(SRAMManager_getInstance(), (BYTE*)&languageId, offsetof(struct SaveData, languageId), sizeof(languageId));
	}

	return languageId;
}

void ProgressManager_setLanguage(ProgressManager this, u8 languageId)
{
	ASSERT(this, "ProgressManager::setLanguage: null this");

	if(this->sramAvailable)
	{
		// write language
		SRAMManager_save(SRAMManager_getInstance(), (BYTE*)&languageId, offsetof(struct SaveData, languageId), sizeof(languageId));

		// write checksum
		ProgressManager_writeChecksum(this);
	}
}

bool ProgressManager_getAutomaticPauseStatus(ProgressManager this)
{
	ASSERT(this, "ProgressManager::getAutomaticPause: null this");

	u8 autoPauseStatus = 0;
	if(this->sramAvailable)
	{
		SRAMManager_read(SRAMManager_getInstance(), (BYTE*)&autoPauseStatus, offsetof(struct SaveData, autoPauseStatus), sizeof(autoPauseStatus));
	}

	return !autoPauseStatus;
}

void ProgressManager_setAutomaticPauseStatus(ProgressManager this, u8 autoPauseStatus)
{
	ASSERT(this, "ProgressManager::setAutomaticPause: null this");

	if(this->sramAvailable)
	{
		// we save the inverted status, so that 0 = enabled, 1 = disabled.
		// that way, a blank value means enabled, which is the standard setting.
		autoPauseStatus = !autoPauseStatus;

		// write auto pause status
		SRAMManager_save(SRAMManager_getInstance(), (BYTE*)&autoPauseStatus, offsetof(struct SaveData, autoPauseStatus), sizeof(autoPauseStatus));

		// write checksum
		ProgressManager_writeChecksum(this);
	}
}

bool ProgressManager_getItemStatus(ProgressManager this, u16 id)
{
	ASSERT(this, "ProgressManager::getItemStatus: null this");

	if(id > 0 && id <= sizeof(this->collectedItems))
	{
		return GET_BIT(this->collectedItems, (id - 1));
	}

	return false;
}

bool ProgressManager_setItemStatus(ProgressManager this, u16 id, bool taken)
{
	ASSERT(this, "ProgressManager::setItemStatus: null this");

	if(id > 0 && id <= sizeof(this->collectedItems))
	{
		if(taken)
		{
			SET_BIT(this->collectedItems, (id - 1));
		}
		else
		{
			CLEAR_BIT(this->collectedItems, (id - 1));
		}

		return true;
	}

	return false;
}

// get hero's current energy
u8 ProgressManager_getHeroCurrentEnergy(ProgressManager this)
{
	return this->heroCurrentEnergy;
}

// get current level time
u32 ProgressManager_getCurrentLevelTime(ProgressManager this)
{
	return this->currentLevelTime;
}

// handle event
static void ProgressManager_onSecondChange(ProgressManager this, Object eventFirer __attribute__ ((unused)))
{
	this->currentLevelTime = Clock_getTime(PlatformerLevelState_getClock(PlatformerLevelState_getInstance()));
}

// handle event
static void ProgressManager_onHitTaken(ProgressManager this, Object eventFirer __attribute__ ((unused)))
{
	this->heroCurrentEnergy = Hero_getEnergy(Hero_getInstance());
}

// handle event
static void ProgressManager_onLevelStarted(ProgressManager this, Object eventFirer __attribute__ ((unused)))
{
}

// handle event
static void ProgressManager_onCheckpointLoaded(ProgressManager this, Object eventFirer __attribute__ ((unused)))
{
	ProgressManager_resetHeroState(this);
	ProgressManager_loadCheckPointData(this);
}

// handle event
static void ProgressManager_onLevelCompleted(ProgressManager this, Object eventFirer __attribute__ ((unused)))
{
	//PlatformerLevelDefinition* platformerLevelDefinition = PlatformerLevelState_getCurrentLevelDefinition(PlatformerLevelState_getInstance());

	// TODO: write last completed level
}
