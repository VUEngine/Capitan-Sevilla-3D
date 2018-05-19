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
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------


// class's constructor
void ProgressManager::constructor()
{


	// construct base object
	Base::constructor();

	// init class variables
	this->sramAvailable = false;
	ProgressManager::resetCurrentLevelProgress(this);

	// add event listeners
	Object eventManager = Object::safeCast(EventManager::getInstance());
	Object::addEventListener(Object::safeCast(PlatformerLevelState::getClock(PlatformerLevelState::getInstance())), Object::safeCast(this), (EventListener)ProgressManager::onSecondChange, kEventSecondChanged);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onHitTaken, kEventHitTaken);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onLevelStarted, kEventLevelStarted);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onCheckpointLoaded, kEventCheckpointLoaded);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onLevelCompleted, kEventLevelCompleted);
}

// class's destructor
void ProgressManager::destructor()
{

	ASSERT(EventManager::getInstance(), "ProgressManager::destructor: null eventManager");

	// remove event listeners
	Object eventManager = Object::safeCast(EventManager::getInstance());
	Object::removeEventListener(Object::safeCast(PlatformerLevelState::getClock(PlatformerLevelState::getInstance())), Object::safeCast(this), (EventListener)ProgressManager::onSecondChange, kEventSecondChanged);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onHitTaken, kEventHitTaken);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onLevelStarted, kEventLevelStarted);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onCheckpointLoaded, kEventCheckpointLoaded);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onLevelCompleted, kEventLevelCompleted);

	// destroy base
	__SINGLETON_DESTROY;
}

void ProgressManager::resetHeroState()
{
	this->heroCurrentEnergy = HERO_INITIAL_ENERGY;
}

void ProgressManager::resetCurrentLevelProgress()
{
	ProgressManager::resetHeroState(this);

	this->currentLevelTime = 0;
	this->collectedItems = 0;

	this->checkpointCurrentLevelTime = 0;
	this->checkpointCollectedItems = 0;
}

// write then immediately read save stamp to validate sram
bool ProgressManager::verifySaveStamp()
{
	char saveStamp[SAVE_STAMP_LENGTH];

	// write save stamp
	SRAMManager::save(SRAMManager::getInstance(), (BYTE*)SAVE_STAMP, offsetof(struct SaveData, saveStamp), sizeof(saveStamp));

	// read save stamp
	SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&saveStamp, offsetof(struct SaveData, saveStamp), sizeof(saveStamp));

	return !strncmp(saveStamp, SAVE_STAMP, SAVE_STAMP_LENGTH);
}

u32 ProgressManager::computeChecksum()
{
	u32 crc32 = ~0;

	// iterate over whole save data, starting right after the previously saved checksum
	int i = (offsetof(struct SaveData, checksum) + sizeof(crc32));
	for(; i < (int)sizeof(SaveData); i++)
	{
		// get the current byte
		u8 currentByte;
		SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&currentByte, i, sizeof(currentByte));

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

void ProgressManager::writeChecksum()
{
	u32 checksum = ProgressManager::computeChecksum(this);
	SRAMManager::save(SRAMManager::getInstance(), (BYTE*)&checksum, offsetof(struct SaveData, checksum), sizeof(checksum));
}

bool ProgressManager::verifyChecksum()
{
	u32 computedChecksum = ProgressManager::computeChecksum(this);
	u32 savedChecksum = 0;
	SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&savedChecksum, offsetof(struct SaveData, checksum), sizeof(savedChecksum));

	return (computedChecksum == savedChecksum);
}

void ProgressManager::initialize()
{


	// verify sram validity
	if(ProgressManager::verifySaveStamp(this))
	{
		// set sram available flag
		this->sramAvailable = true;

		// verify saved progress presence and integrity
		if(!ProgressManager::verifyChecksum(this))
		{
			// if no previous save could be verified, completely erase sram to start clean
			SRAMManager::clear(SRAMManager::getInstance(), 0, (int)sizeof(SaveData));

			// write checksum
			ProgressManager::writeChecksum(this);
		}

		// load and set active language
		I18n::setActiveLanguage(I18n::getInstance(), ProgressManager::getLanguage(this));

		// load and set auto pause state
		Game::setAutomaticPauseState(Game::getInstance(), ProgressManager::getAutomaticPauseStatus(this)
			? GameState::safeCast(AutoPauseScreenState::getInstance())
			: NULL
		);
	}
}

void ProgressManager::setCheckPointData()
{


	this->checkpointCurrentLevelTime = this->currentLevelTime;
	this->checkpointCollectedItems = this->collectedItems;
}

void ProgressManager::loadCheckPointData()
{


	this->currentLevelTime = this->checkpointCurrentLevelTime;
	this->collectedItems = this->checkpointCollectedItems;
}

u8 ProgressManager::getLanguage()
{


	u8 languageId = 0;
	if(this->sramAvailable)
	{
		SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&languageId, offsetof(struct SaveData, languageId), sizeof(languageId));
	}

	return languageId;
}

void ProgressManager::setLanguage(u8 languageId)
{


	if(this->sramAvailable)
	{
		// write language
		SRAMManager::save(SRAMManager::getInstance(), (BYTE*)&languageId, offsetof(struct SaveData, languageId), sizeof(languageId));

		// write checksum
		ProgressManager::writeChecksum(this);
	}
}

bool ProgressManager::getAutomaticPauseStatus()
{


	u8 autoPauseStatus = 0;
	if(this->sramAvailable)
	{
		SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&autoPauseStatus, offsetof(struct SaveData, autoPauseStatus), sizeof(autoPauseStatus));
	}

	return !autoPauseStatus;
}

void ProgressManager::setAutomaticPauseStatus(u8 autoPauseStatus)
{


	if(this->sramAvailable)
	{
		// we save the inverted status, so that 0 = enabled, 1 = disabled.
		// that way, a blank value means enabled, which is the standard setting.
		autoPauseStatus = !autoPauseStatus;

		// write auto pause status
		SRAMManager::save(SRAMManager::getInstance(), (BYTE*)&autoPauseStatus, offsetof(struct SaveData, autoPauseStatus), sizeof(autoPauseStatus));

		// write checksum
		ProgressManager::writeChecksum(this);
	}
}

bool ProgressManager::getItemStatus(u16 id)
{


	if(id > 0 && id <= sizeof(this->collectedItems))
	{
		return GET_BIT(this->collectedItems, (id - 1));
	}

	return false;
}

bool ProgressManager::setItemStatus(u16 id, bool taken)
{


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
u8 ProgressManager::getHeroCurrentEnergy()
{
	return this->heroCurrentEnergy;
}

// get current level time
u32 ProgressManager::getCurrentLevelTime()
{
	return this->currentLevelTime;
}

// handle event
void ProgressManager::onSecondChange(Object eventFirer __attribute__ ((unused)))
{
	this->currentLevelTime = Clock::getTime(PlatformerLevelState::getClock(PlatformerLevelState::getInstance()));
}

// handle event
void ProgressManager::onHitTaken(Object eventFirer __attribute__ ((unused)))
{
	this->heroCurrentEnergy = Hero::getEnergy(Hero::getInstance());
}

// handle event
void ProgressManager::onLevelStarted(Object eventFirer __attribute__ ((unused)))
{
}

// handle event
void ProgressManager::onCheckpointLoaded(Object eventFirer __attribute__ ((unused)))
{
	ProgressManager::resetHeroState(this);
	ProgressManager::loadCheckPointData(this);
}

// handle event
void ProgressManager::onLevelCompleted(Object eventFirer __attribute__ ((unused)))
{
	//PlatformerLevelDefinition* platformerLevelDefinition = PlatformerLevelState::getCurrentLevelDefinition(PlatformerLevelState::getInstance());

	// TODO: write last completed level
}
