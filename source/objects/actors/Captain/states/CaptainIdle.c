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
	Captain::playAnimation(owner, "Idle");

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

			Captain::startedMovingOnAxis(owner, *(uint16*)Telegram::getExtraInfo(telegram));
			break;

		case kMessageBodyStopped:

			return true;
			break;

		case kCaptainSleep:

			Captain::playAnimation(owner, "Sleep");
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
	if((K_SEL|K_RD|K_RU|K_RL|K_RR|K_LT|K_RT) & userInput->pressedKey)
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
