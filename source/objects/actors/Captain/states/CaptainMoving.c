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

#include "CaptainMoving.h"
#include "CaptainIdle.h"
#include "../Captain.h"

#include <PlatformerLevelState.h>
#include <MessageDispatcher.h>
#include <KeypadManager.h>
#include <debugUtilities.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void CaptainMoving::constructor()
{
	// construct base
	Base::constructor();

	this->bouncing = false;
}

void CaptainMoving::destructor()
{
	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kDisallowJumpOnBouncing);

	// destroy base
	Base::destructor();
}

void CaptainMoving::enter(void* owner)
{
	KeypadManager::registerInput(KeypadManager::getInstance(), __KEY_PRESSED | __KEY_RELEASED);

	// make sure that the captain's body is awaken right now so the check during
	// the execute method doesn't fail
	Captain::addForce(owner, __X_AXIS, false);
}

void CaptainMoving::execute(void* owner)
{
	// keep adding force
	if(((K_LL | K_LR ) & KeypadManager::getHoldKey(KeypadManager::getInstance())) && Body::isAwake(Actor::getBody(owner)))
	{
		Captain::addForce(owner, __X_AXIS, false);
	}
}

bool CaptainMoving::processMessage(void* owner, Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kBodyStopped:

			Captain::stopMovementOnAxis(owner, *(int*)Telegram::getExtraInfo(telegram));
			return true;
			break;

		case kBodyStartedMoving:

			Captain::startedMovingOnAxis(owner, *(int*)Telegram::getExtraInfo(telegram));
			break;
	}

	return false;
}

void CaptainMoving::onKeyPressed(void* owner, const UserInput* userInput)
{
	if(K_RD & userInput->pressedKey)
	{
		Captain::reload(owner);
	}
	else if(K_A & userInput->pressedKey)
	{
		Captain::jump(owner, !this->bouncing);
	}
	else if(K_B & userInput->pressedKey)
	{
		Captain::startShooting(owner);
	}
	else if((K_LL | K_LR ) & (userInput->pressedKey | userInput->holdKey))
	{
		Captain::addForce(owner, __X_AXIS, true);

		Captain::checkDirection(owner, userInput->pressedKey, "Walk");
	}
	else if(K_LD & userInput->pressedKey)
	{
		Captain::kneel(owner);
	}
}

void CaptainMoving::onKeyReleased(void* owner, const UserInput* userInput)
{
	if((K_LL | K_LR) & userInput->releasedKey)
	{
		Captain::stopAddingForce(owner);
	}
}

