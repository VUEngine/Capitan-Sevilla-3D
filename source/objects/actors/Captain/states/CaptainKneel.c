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

#include "CaptainKneel.h"
#include "CaptainMoving.h"
#include "../Captain.h"

#include <PlatformerLevelState.h>
#include <MessageDispatcher.h>
#include <KeypadManager.h>
#include <debugUtilities.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void CaptainKneel::constructor()
{
	// construct base
	Base::constructor();
}

void CaptainKneel::destructor()
{
	// destroy base
	Base::destructor();
}

void CaptainKneel::enter(void* owner)
{
	// show animation
	Captain::playAnimation(owner, "KneelDown");

	KeypadManager::registerInput(KeypadManager::getInstance(), __KEY_RELEASED | __KEY_PRESSED);

	// manipulate captain's shape
	Captain::toggleShapes(owner, true);
}

void CaptainKneel::exit(void* owner)
{
	// manipulate captain's shape
	Captain::toggleShapes(owner, false);
}

void CaptainKneel::onKeyReleased(void* owner, const UserInput* userInput)
{
    if(K_LD & userInput->releasedKey)
    {
        Captain::standUp(owner);
    }
}

void CaptainKneel::onKeyPressed(void* owner, const UserInput* userInput)
{
	if((K_SEL|K_RD|K_RU|K_RL|K_RR|K_LT|K_RT) & userInput->pressedKey)
	{
		Captain::reload(owner);
	}
	else if(K_A & userInput->pressedKey)
	{
		Captain::jump(owner, true);
	}
	else if(K_B & userInput->pressedKey)
	{
		Captain::startShooting(owner);
	}
}

