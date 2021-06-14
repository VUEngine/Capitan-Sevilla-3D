/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
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
#include <Captain.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

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
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onCaptainShot, kEventCaptainShot);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onGumsReloaded, kEventGumsReloaded);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onLevelStarted, kEventLevelStarted);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onCheckpointLoaded, kEventCheckpointLoaded);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onLevelCompleted, kEventLevelCompleted);
}

void ProgressManager::destructor()
{
	// remove event listeners
	Object eventManager = Object::safeCast(EventManager::getInstance());
	Object::removeEventListener(PlatformerLevelState::getClock(PlatformerLevelState::getInstance()), Object::safeCast(this), (EventListener)ProgressManager::onSecondChange, kEventSecondChanged);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onHitTaken, kEventHitTaken);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onCaptainShot, kEventCaptainShot);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onGumsReloaded, kEventGumsReloaded);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onLevelStarted, kEventLevelStarted);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onCheckpointLoaded, kEventCheckpointLoaded);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)ProgressManager::onLevelCompleted, kEventLevelCompleted);

	// destroy base
	Base::destructor();
}

void ProgressManager::resetCaptainState()
{
	this->captainCurrentEnergy = CAPTAIN_INITIAL_ENERGY;
	this->captainCurrentGums = CAPTAIN_MAX_GUMS;
}

void ProgressManager::resetCurrentLevelProgress()
{
	ProgressManager::resetCaptainState(this);

	this->currentLevelTime = 0;

	this->checkpointCurrentLevelTime = 0;
}

void ProgressManager::restoreSettings()
{
	Base::restoreSettings(this);
}

void ProgressManager::setCheckPointData()
{
	this->checkpointCurrentLevelTime = this->currentLevelTime;
}

void ProgressManager::loadCheckPointData()
{
	this->currentLevelTime = this->checkpointCurrentLevelTime;
}

// get captain's current energy
u8 ProgressManager::getCaptainCurrentEnergy()
{
	return this->captainCurrentEnergy;
}

// get captain's current number of gums
u8 ProgressManager::getCaptainCurrentGums()
{
	return this->captainCurrentGums;
}

// get current level time
u32 ProgressManager::getCurrentLevelTime()
{
	return this->currentLevelTime;
}

void ProgressManager::onSecondChange(Object eventFirer __attribute__ ((unused)))
{
	this->currentLevelTime = Clock::getTime(PlatformerLevelState::getClock(PlatformerLevelState::getInstance()));
}

void ProgressManager::onHitTaken(Object eventFirer __attribute__ ((unused)))
{
	this->captainCurrentEnergy = Captain::getEnergy(Captain::getInstance());
}

void ProgressManager::onCaptainShot(Object eventFirer __attribute__ ((unused)))
{
	this->captainCurrentGums = Captain::getGums(Captain::getInstance());
}

void ProgressManager::onGumsReloaded(Object eventFirer __attribute__ ((unused)))
{
	this->captainCurrentGums = Captain::getGums(Captain::getInstance());
}

void ProgressManager::onLevelStarted(Object eventFirer __attribute__ ((unused)))
{
}

void ProgressManager::onCheckpointLoaded(Object eventFirer __attribute__ ((unused)))
{
	ProgressManager::resetCaptainState(this);
	ProgressManager::loadCheckPointData(this);
}

void ProgressManager::onLevelCompleted(Object eventFirer __attribute__ ((unused)))
{
	//PlatformerLevelSpec* platformerLevelSpec = PlatformerLevelState::getCurrentLevelSpec(PlatformerLevelState::getInstance());

	// TODO: write last completed level
}
