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

#include "HeroKneel.h"
#include "HeroMoving.h"
#include "../Hero.h"

#include <PlatformerLevelState.h>
#include <MessageDispatcher.h>
#include <KeypadManager.h>
#include <debugUtilities.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void HeroKneel::constructor()
{
	// construct base
	Base::constructor();
}

// class's destructor
void HeroKneel::destructor()
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
void HeroKneel::enter(void* owner)
{
	// show animation
	AnimatedEntity::playAnimation(AnimatedEntity::safeCast(owner), "Kneel");

	KeypadManager::registerInput(KeypadManager::getInstance(), __KEY_PRESSED | __KEY_RELEASED | __KEY_HOLD);

	// manipulate hero's shape
	HeroState::toggleShapes(this, owner, true);
}

// state's exit
void HeroKneel::exit(void* owner __attribute__ ((unused)))
{
}

// state's handle message
bool HeroKneel::processMessage(void* owner, Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kBodyStartedMoving:

			Hero::startedMovingOnAxis(Hero::safeCast(owner), *(u16*)Telegram::getExtraInfo(telegram));
			break;

		case kBodyStopped:

			return true;
			break;

		case kHeroSleep:

			AnimatedEntity::playAnimation(AnimatedEntity::safeCast(owner), "Sleep");
			return true;
			break;
	}

	return false;
}

void HeroKneel::onKeyPressed(void* owner, const UserInput* userInput)
{
	if(K_A & userInput->pressedKey)
	{
		Hero::jump(Hero::safeCast(owner), true);
	}

	if(K_B & userInput->pressedKey)
	{
		Hero::shoot(Hero::safeCast(owner), true);
	}

	if((K_LL | K_LR) & (userInput->pressedKey | userInput->holdKey))
	{
		Acceleration acceleration =
		{
			K_LL & userInput->pressedKey ? __I_TO_FIX10_6(-1) : K_LR & userInput->pressedKey ? __1I_FIX10_6 : 0,
			K_A & userInput->pressedKey ? __I_TO_FIX10_6(-1) : 0,
			0,
		};

		if(Actor::canMoveTowards(Actor::safeCast(owner), acceleration))
		{
			Hero::checkDirection(Hero::safeCast(owner), userInput->pressedKey, "Idle");
			Hero::startedMovingOnAxis(Hero::safeCast(owner), __X_AXIS);
		}
	}

	if((K_LU) & (userInput->pressedKey | userInput->holdKey))
	{
		//swapstate to idle
	}
}

void HeroKneel::onKeyReleased(void* owner, const UserInput* userInput)
{
	if(K_B & userInput->releasedKey)
	{
		Hero::shoot(Hero::safeCast(owner), false);
	}
}

void HeroKneel::onKeyHold(void* owner, const UserInput* userInput)
{
    if((K_LL | K_LR) & userInput->holdKey)
    {
        Vector3D direction =
        {
            K_LL & userInput->holdKey ? __I_TO_FIX10_6(-1) : K_LR & userInput->holdKey ? __I_TO_FIX10_6(1) : 0,
            K_A & userInput->holdKey ? __I_TO_FIX10_6(-1) : 0,
            0,
        };

		if(Actor::canMoveTowards(Actor::safeCast(owner), direction))
        {
            Hero::checkDirection(Hero::safeCast(owner), userInput->holdKey, "Idle");

            Hero::startedMovingOnAxis(Hero::safeCast(owner), __X_AXIS);
        }
    }
}
