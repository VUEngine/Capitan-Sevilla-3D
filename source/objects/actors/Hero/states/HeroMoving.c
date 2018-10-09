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

#include "HeroMoving.h"
#include "HeroIdle.h"
#include "../Hero.h"

#include <PlatformerLevelState.h>
#include <MessageDispatcher.h>
#include <KeypadManager.h>
#include <debugUtilities.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void HeroMoving::constructor()
{
	// construct base
	Base::constructor();

	this->bouncing = false;
}

// class's destructor
void HeroMoving::destructor()
{
	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kDisallowJumpOnBouncing);

	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
void HeroMoving::enter(void* owner)
{
	KeypadManager::registerInput(KeypadManager::getInstance(), __KEY_PRESSED | __KEY_RELEASED);

	// make sure that the hero's body is awaken right now so the check during
	// the execute method doesn't fail
	Hero::addForce(Hero::safeCast(owner), __X_AXIS, false);

	// manipulate hero's shape
	HeroState::toggleShapes(this, owner, false);
}

void HeroMoving::execute(void* owner)
{
	// keep adding force
	if(((K_LL | K_LR ) & KeypadManager::getHoldKey(KeypadManager::getInstance())) && Body::isAwake(Actor::getBody(Actor::safeCast(owner))))
	{
		Hero::addForce(Hero::safeCast(owner), __X_AXIS, false);
	}
}

// state's handle message
bool HeroMoving::processMessage(void* owner, Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kBodyStopped:

			Hero::stopMovementOnAxis(Hero::safeCast(owner), *(int*)Telegram::getExtraInfo(telegram));
			return true;
			break;

		case kBodyStartedMoving:

			Hero::startedMovingOnAxis(Hero::safeCast(owner), *(int*)Telegram::getExtraInfo(telegram));
			break;
	}

	return false;
}

void HeroMoving::onKeyPressed(void* owner, const UserInput* userInput)
{
	if(K_A & userInput->pressedKey)
	{
		Hero::jump(Hero::safeCast(owner), !this->bouncing);
	}

	if(K_B & userInput->pressedKey)
	{
		Hero::startShooting(Hero::safeCast(owner));
	}

	// check direction
	if((K_LL | K_LR ) & (userInput->pressedKey | userInput->holdKey))
	{
		Hero::addForce(Hero::safeCast(owner), __X_AXIS, true);

		Hero::checkDirection(Hero::safeCast(owner), userInput->pressedKey, "Walk");
	}
	else if(K_LD & userInput->pressedKey)
	{
		Hero::kneel(Hero::safeCast(owner));
	}
}

void HeroMoving::onKeyReleased(void* owner, const UserInput* userInput)
{
	if((K_LL | K_LR) & userInput->releasedKey)
	{
		Hero::stopAddingForce(Hero::safeCast(owner));
	}
}

