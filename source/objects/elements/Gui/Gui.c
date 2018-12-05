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

#include <GameEvents.h>
#include <Game.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Box.h>
#include <PhysicalWorld.h>
#include "Gui.h"
#include <PlatformerLevelState.h>
#include <ProgressManager.h>
#include <EventManager.h>
#include <SoundManager.h>
#include <Captain.h>


//---------------------------------------------------------------------------------------------------------
//											DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern const u16 JUMP_SND[];
extern EntitySpec GAME_OVER_EN;
extern CharSetSpec GUI_CH;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void Gui::constructor(EntitySpec* animatedEntitySpec, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(animatedEntitySpec, id, internalId, name);

	// init members
	this->active = false;
	this->timeRemaining = LEVEL_INITIAL_TIME;

	// add event listeners
	Object eventManager = Object::safeCast(EventManager::getInstance());
	Object::addEventListener(PlatformerLevelState::getClock(PlatformerLevelState::getInstance()), Object::safeCast(this), (EventListener)Gui::onSecondChange, kEventSecondChanged);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onHitTaken, kEventHitTaken);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onCaptainDied, kEventCaptainDied);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onSetModeToPaused, kEventSetModeToPaused);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onSetModeToPlaying, kEventSetModeToPlaying);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onCaptainShot, kEventCaptainShot);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onSausageCollected, kEventSausageCollected);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onCheckpointLoaded, kEventCheckpointLoaded);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onLiftActivated, kEventLiftActivated);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onExitPointReached, kEventExitPointReached);
}

void Gui::destructor()
{
	// clear printing layer
	Printing::text(Printing::getInstance(), "////////////////////////////////////////////////", GUI_X_POS, GUI_Y_POS, "GuiFont");

	// remove event listeners
	Object eventManager = Object::safeCast(EventManager::getInstance());
	Object::removeEventListener(PlatformerLevelState::getClock(PlatformerLevelState::getInstance()), Object::safeCast(this), (EventListener)Gui::onSecondChange, kEventSecondChanged);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onHitTaken, kEventHitTaken);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onCaptainDied, kEventCaptainDied);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onSetModeToPaused, kEventSetModeToPaused);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onSetModeToPlaying, kEventSetModeToPlaying);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onCaptainShot, kEventCaptainShot);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onSausageCollected, kEventSausageCollected);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onCheckpointLoaded, kEventCheckpointLoaded);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onLiftActivated, kEventLiftActivated);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onExitPointReached, kEventExitPointReached);

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void Gui::resume()
{
	Base::resume(this);

	Gui::printAll(this);
}

void Gui::printClock()
{
	if(this->timeRemaining < 10)
	{
		Printing::int(Printing::getInstance(), 0, GUI_X_POS + 37, GUI_Y_POS, "GuiFont");
		Printing::int(Printing::getInstance(), this->timeRemaining, GUI_X_POS + 38, GUI_Y_POS, "GuiFont");

		if(this->timeRemaining <= 5)
		{
			// play warn sound
			SoundManager::playFxSound(SoundManager::getInstance(), JUMP_SND, this->transformation.globalPosition);
		}
	}
	else
	{
		Printing::int(Printing::getInstance(), this->timeRemaining, GUI_X_POS + 37, GUI_Y_POS, "GuiFont");
	}
}

void Gui::printSausages()
{
	Printing::text(Printing::getInstance(), "///", GUI_X_POS + 28, GUI_Y_POS, "GuiFont");
	Printing::int(Printing::getInstance(), Captain::getSausages(Captain::getInstance()), GUI_X_POS + 28, GUI_Y_POS, "GuiFont");
}

void Gui::printLives()
{
	Printing::text(Printing::getInstance(), "///", GUI_X_POS + 44, GUI_Y_POS, "GuiFont");
	Printing::int(Printing::getInstance(), Captain::getEnergy(Captain::getInstance()), GUI_X_POS + 44, GUI_Y_POS, "GuiFont");
}

void Gui::printAll()
{
	Gui::printClock(this);
	Gui::printLives(this);
	Gui::printSausages(this);
}

void Gui::onSecondChange(Object eventFirer __attribute__ ((unused)))
{
	if(!this->active)
	{
		return;
	}

	if(this->timeRemaining > 0)
	{
		this->timeRemaining--;
		Gui::printClock(this);
	}
	else
	{
		Captain::die(Captain::getInstance());
	}
}

void Gui::onHitTaken(Object eventFirer __attribute__ ((unused)))
{
	Gui::printLives(this);
}

void Gui::onCaptainDied(Object eventFirer __attribute__ ((unused)))
{
	Container::deleteMyself(this);

	// add "game over"
	Vector3D cameraPosition = Camera::getPosition(Camera::getInstance());
	PositionedEntity gameOverPositionedEntity = {&GAME_OVER_EN, {__METERS_TO_PIXELS(cameraPosition.x) + 192, 112, 0, 0}, 0, NULL, NULL, NULL, false};
	Stage::addChildEntity(Game::getStage(Game::getInstance()), &gameOverPositionedEntity, true);
}

void Gui::onSetModeToPaused(Object eventFirer __attribute__ ((unused)))
{
	this->active = false;
}

void Gui::onSetModeToPlaying(Object eventFirer __attribute__ ((unused)))
{
	this->active = true;

	Gui::printAll(this);
}

void Gui::onCaptainShot(Object eventFirer __attribute__ ((unused)))
{
	Gui::printSausages(this);
}

void Gui::onSausageCollected(Object eventFirer __attribute__ ((unused)))
{
	Gui::printSausages(this);
}

void Gui::onCheckpointLoaded(Object eventFirer __attribute__ ((unused)))
{
	// override with progress from progress manager
	ProgressManager progressManager = ProgressManager::getInstance();
	if(progressManager)
	{
		this->timeRemaining = LEVEL_INITIAL_TIME;//ProgressManager::getCurrentLevelTime(ProgressManager::getInstance());
	}
}

void Gui::onLiftActivated(Object eventFirer __attribute__ ((unused)))
{
	this->active = false;
}

void Gui::onExitPointReached(Object eventFirer __attribute__ ((unused)))
{
	this->active = false;
}
