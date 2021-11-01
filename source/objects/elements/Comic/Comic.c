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

void Comic::constructor(LocalizedEntitySpec* localizedEntitySpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor(localizedEntitySpec, internalId, name);

	// init members
	this->mode = kComicStill;

	// add event listeners
	Object eventManager = Object::safeCast(EventManager::getInstance());
	Object::addEventListener(PlatformerLevelState::getInstance(), Object::safeCast(this), (EventListener)Comic::onUserInput, kEventUserInput);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)Comic::onLevelStarted, kEventLevelStarted);
}

void Comic::destructor()
{
	// If set right after the user presses the key, a race condition with the other objects listening
	// for the kEventUserInput event will crash the game
	Object::fireEvent(EventManager::getInstance(), kEventComicDeleted);

	// remove event listeners
	Object eventManager = Object::safeCast(EventManager::getInstance());
	Object::removeEventListener(PlatformerLevelState::getInstance(), Object::safeCast(this), (EventListener)Comic::onUserInput, kEventUserInput);
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

// move comic down
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
}
