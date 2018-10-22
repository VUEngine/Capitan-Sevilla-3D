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
#include <Hero.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void ProgressManager::constructor()
{
	// construct base object
	Base::constructor();

	// init class variables
	ProgressManager::resetCurrentLevelProgress(this);

	// add event listeners
	Object eventManager = Object::safeCast(EventManager::getInstance());
	Object::addEventListener(PlatformerLevelState::getClock(PlatformerLevelState::getInstance()), Object::safeCast(this), (EventListener)ProgressManager::onSecondChange, kEventSecondChanged);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onHitTaken, kEventHitTaken);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onHeroShot, kEventHeroShot);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onLevelStarted, kEventLevelStarted);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onCheckpointLoaded, kEventCheckpointLoaded);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onLevelCompleted, kEventLevelCompleted);
}

// class's destructor
void ProgressManager::destructor()
{
	// remove event listeners
	Object eventManager = Object::safeCast(EventManager::getInstance());
	Object::removeEventListener(PlatformerLevelState::getClock(PlatformerLevelState::getInstance()), Object::safeCast(this), (EventListener)ProgressManager::onSecondChange, kEventSecondChanged);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onHitTaken, kEventHitTaken);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onHeroShot, kEventHeroShot);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onLevelStarted, kEventLevelStarted);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onCheckpointLoaded, kEventCheckpointLoaded);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onLevelCompleted, kEventLevelCompleted);

	// destroy base
	__SINGLETON_DESTROY;
}

void ProgressManager::resetHeroState()
{
	this->heroCurrentEnergy = HERO_INITIAL_ENERGY;
	this->heroCurrentSausages = HERO_INITIAL_SAUSAGES;
}

void ProgressManager::resetCurrentLevelProgress()
{
	ProgressManager::resetHeroState(this);

	this->currentLevelTime = 0;
	this->collectedItems = 0;

	this->checkpointCurrentLevelTime = 0;
	this->checkpointCollectedItems = 0;
}

void ProgressManager::restoreSettings()
{
	Base::restoreSettings(this);
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

// get hero's current number of sausages
u8 ProgressManager::getHeroCurrentSausages()
{
	return this->heroCurrentSausages;
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
void ProgressManager::onHeroShot(Object eventFirer __attribute__ ((unused)))
{
	this->heroCurrentSausages = Hero::getSausages(Hero::getInstance());
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
