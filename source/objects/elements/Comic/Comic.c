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
#include "Comic.h"
#include <PlatformerLevelState.h>
#include <EventManager.h>
#include <Gui.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void Comic::constructor(EntityDefinition* entityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(entityDefinition, id, internalId, name);

	// init members
	this->mode = kComicStill;

	// add event listeners
	Object eventManager = Object::safeCast(EventManager::getInstance());
	Object::addEventListener(Object::safeCast(PlatformerLevelState::getInstance()), Object::safeCast(this), (EventListener)Comic::onUserInput, kEventUserInput);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)Comic::onLevelStarted, kEventLevelStarted);
}

// class's destructor
void Comic::destructor()
{
	// If set right after the user presses the key, a race condition with the other objects listening
	// for the kEventUserInput event will crash the game
	PlatformerLevelState::setModeToPlaying(PlatformerLevelState::getInstance());

	// remove event listeners
	Object eventManager = Object::safeCast(EventManager::getInstance());
	Object::removeEventListener(Object::safeCast(PlatformerLevelState::getInstance()), Object::safeCast(this), (EventListener)Comic::onUserInput, kEventUserInput);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)Comic::onLevelStarted, kEventLevelStarted);

	// discard pending delayed message
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kComicMove);

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void Comic::ready(bool recursive)
{
	// call base
	Base::ready(this, recursive);
}

void Comic::startMovement()
{
	if(this->mode == kComicStill)
	{
		Object::removeEventListener(Object::safeCast(PlatformerLevelState::getInstance()), Object::safeCast(this), (EventListener)Comic::onUserInput, kEventUserInput);
		MessageDispatcher::dispatchMessage(COMIC_MOVE_DELAY, Object::safeCast(this), Object::safeCast(this), kComicMove, NULL);
		this->mode = kComicMoving;
	}
}

// process user input
void Comic::onUserInput(Object eventFirer __attribute__ ((unused)))
{
	UserInput userInput = PlatformerLevelState::getUserInput(PlatformerLevelState::getInstance(), true);

	if((K_STA | K_A) & userInput.releasedKey)
	{
		Comic::startMovement(this);
	}
}

// state's handle message
bool Comic::handleMessage(Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kComicMove:

			Comic::move(this);
			break;
	}

	return false;
}

// move lava up
void Comic::move()
{
	// get local position of comic and modify y value
	Vector3D offset = *Container::getLocalPosition(this);
	offset.y += __PIXELS_TO_METERS(COMIC_MOVE_OFFSET);

	// update position
	Container::setLocalPosition(this, &offset);

	// send delayed message to self to trigger next movement
	MessageDispatcher::dispatchMessage(COMIC_MOVE_DELAY, Object::safeCast(this), Object::safeCast(this), kComicMove, NULL);
}

bool Comic::respawn()
{
	return false;
}

void Comic::onLevelStarted(Object eventFirer __attribute__ ((unused)))
{
	PlatformerLevelState::setModeToPaused(PlatformerLevelState::getInstance());

	Printing::text(Printing::getInstance(), "////////////////////////////////////////////////", GUI_X_POS, GUI_Y_POS, "GuiFont");
}