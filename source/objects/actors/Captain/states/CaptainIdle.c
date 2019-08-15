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

#include "CaptainIdle.h"
#include "CaptainMoving.h"
#include "../Captain.h"

#include <PlatformerLevelState.h>
#include <MessageDispatcher.h>
#include <KeypadManager.h>
#include <debugUtilities.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void CaptainIdle::constructor()
{
	// construct base
	Base::constructor();
}

void CaptainIdle::destructor()
{
	// destroy base
	Base::destructor();
}

void CaptainIdle::enter(void* owner)
{
	// show animation
	AnimatedEntity::playAnimation(owner, "Idle");

	KeypadManager::registerInput(KeypadManager::getInstance(), __KEY_PRESSED | __KEY_RELEASED | __KEY_HOLD);
}

void CaptainIdle::exit(void* owner __attribute__ ((unused)))
{
	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kCaptainSleep);
}

bool CaptainIdle::processMessage(void* owner, Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kMessageBodyStartedMoving:

			Captain::startedMovingOnAxis(owner, *(u16*)Telegram::getExtraInfo(telegram));
			break;

		case kMessageBodyStopped:

			return true;
			break;

		case kCaptainSleep:

			AnimatedEntity::playAnimation(owner, "Sleep");
			return true;
			break;
	}

	return false;
}

void CaptainIdle::onKeyHold(void* owner, const UserInput* userInput)
{
    if((K_LL | K_LR) & userInput->holdKey)
    {
        Vector3D direction =
        {
            K_LL & userInput->holdKey ? __I_TO_FIX10_6(-1) : K_LR & userInput->holdKey ? __I_TO_FIX10_6(1) : 0,
            K_A & userInput->holdKey ? __I_TO_FIX10_6(-1) : 0,
            0,
        };

		if(Actor::canMoveTowards(owner, direction))
        {
            Captain::checkDirection(owner, userInput->holdKey, "Idle");

            Captain::startedMovingOnAxis(owner, __X_AXIS);
        }
    }
}

void CaptainIdle::onKeyPressed(void* owner, const UserInput* userInput)
{
	if(K_RD & userInput->pressedKey)
	{
		Captain::reload(owner);
	}
	else if(K_LD & userInput->pressedKey)
	{
		Captain::kneel(owner);
	}
	else if(K_A & userInput->pressedKey)
	{
		Captain::jump(owner, true);
	}
	else if(K_B & userInput->pressedKey)
	{
		Captain::startShooting(owner);
	}
	else if((K_LL | K_LR) & (userInput->pressedKey | userInput->holdKey))
	{
		Acceleration acceleration =
		{
			K_LL & userInput->pressedKey ? __I_TO_FIX10_6(-1) : K_LR & userInput->pressedKey ? __1I_FIX10_6 : 0,
			K_A & userInput->pressedKey ? __I_TO_FIX10_6(-1) : 0,
			0,
		};

		if(Actor::canMoveTowards(owner, acceleration))
		{
			Captain::checkDirection(owner, userInput->pressedKey, "Idle");

			Captain::startedMovingOnAxis(owner, __X_AXIS);
		}
	}
}
