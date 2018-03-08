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

#include "HeroIdle.h"
#include "HeroMoving.h"
#include "../Hero.h"

#include <PlatformerLevelState.h>
#include <MessageDispatcher.h>
#include <KeypadManager.h>
#include <debugUtilities.h>


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void HeroIdle_constructor(HeroIdle this);
void HeroIdle_destructor(HeroIdle this);
void HeroIdle_enter(HeroIdle this, void* owner);
void HeroIdle_exit(HeroIdle this, void* owner);
bool HeroIdle_processMessage(HeroIdle this, void* owner, Telegram telegram);


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(HeroIdle, HeroState);
__SINGLETON(HeroIdle);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void __attribute__ ((noinline)) HeroIdle_constructor(HeroIdle this)
{
	// construct base
	__CONSTRUCT_BASE(HeroState);
}

// class's destructor
void HeroIdle_destructor(HeroIdle this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
void HeroIdle_enter(HeroIdle this __attribute__ ((unused)), void* owner)
{
	// show animation
	AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, owner), "Idle");

	// start sleeping after 6 seconds of inactivity
	//MessageDispatcher_dispatchMessage(6000, __SAFE_CAST(Object, this), __SAFE_CAST(Object, owner), kHeroSleep, NULL);

	KeypadManager_registerInput(KeypadManager_getInstance(), __KEY_PRESSED | __KEY_RELEASED | __KEY_HOLD);

	// manipulate hero's shape
	__VIRTUAL_CALL(HeroState, toggleShapes, __SAFE_CAST(HeroState, this), owner, false);
}

// state's exit
void HeroIdle_exit(HeroIdle this, void* owner __attribute__ ((unused)))
{
	// discard pending delayed messages
	MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kHeroSleep);
}

// state's handle message
bool HeroIdle_processMessage(HeroIdle this __attribute__ ((unused)), void* owner, Telegram telegram)
{
	switch(Telegram_getMessage(telegram))
	{
		case kBodyStartedMoving:

			Hero_startedMovingOnAxis(__SAFE_CAST(Hero, owner), *(u16*)Telegram_getExtraInfo(telegram));
			break;

		case kBodyStopped:

			return true;
			break;

		case kHeroSleep:

			AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, owner), "Sleep");
			return true;
			break;
	}

	return false;
}

void HeroIdle_onKeyPressed(HeroIdle this __attribute__ ((unused)), void* owner, const UserInput* userInput)
{
	if(K_A & userInput->pressedKey)
	{
		Hero_jump(__SAFE_CAST(Hero, owner), true);
	}

	if(K_B & userInput->pressedKey)
	{
		Hero_startShooting(__SAFE_CAST(Hero, owner));
	}
	else if(K_B & userInput->releasedKey)
	{
		Hero_stopShooting(__SAFE_CAST(Hero, owner));
	}

	if((K_LL | K_LR) & (userInput->pressedKey | userInput->holdKey))
	{
		Acceleration acceleration =
		{
			K_LL & userInput->pressedKey ? __I_TO_FIX10_6(-1) : K_LR & userInput->pressedKey ? __1I_FIX10_6 : 0,
			K_A & userInput->pressedKey ? __I_TO_FIX10_6(-1) : 0,
			0,
		};

		if(Actor_canMoveTowards(__SAFE_CAST(Actor, owner), acceleration))
		{
			Hero_checkDirection(__SAFE_CAST(Hero, owner), userInput->pressedKey, "Idle");

			Hero_startedMovingOnAxis(__SAFE_CAST(Hero, owner), __X_AXIS);
		}
	}

	if(K_LD & userInput->pressedKey)
	{
		Hero_kneel(__SAFE_CAST(Hero, owner));
	}
}

void HeroIdle_onKeyReleased(HeroIdle this __attribute__ ((unused)), void* owner, const UserInput* userInput)
{
}

void HeroIdle_onKeyHold(HeroIdle this __attribute__ ((unused)), void* owner, const UserInput* userInput)
{
    if((K_LL | K_LR) & userInput->holdKey)
    {
        Vector3D direction =
        {
            K_LL & userInput->holdKey ? __I_TO_FIX10_6(-1) : K_LR & userInput->holdKey ? __I_TO_FIX10_6(1) : 0,
            K_A & userInput->holdKey ? __I_TO_FIX10_6(-1) : 0,
            0,
        };

		if(Actor_canMoveTowards(__SAFE_CAST(Actor, owner), direction))
        {
            Hero_checkDirection(__SAFE_CAST(Hero, owner), userInput->holdKey, "Idle");

            Hero_startedMovingOnAxis(__SAFE_CAST(Hero, owner), __X_AXIS);
        }
    }
}
