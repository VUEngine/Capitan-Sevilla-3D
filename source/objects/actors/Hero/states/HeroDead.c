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

#include "HeroDead.h"
#include "HeroMoving.h"
#include "../Hero.h"

#include <PlatformerLevelState.h>
#include <MessageDispatcher.h>
#include <KeypadManager.h>
#include <debugUtilities.h>


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void HeroDead_constructor(HeroDead this);
void HeroDead_destructor(HeroDead this);
void HeroDead_enter(HeroDead this, void* owner);
void HeroDead_exit(HeroDead this, void* owner);
bool HeroDead_processMessage(HeroDead this, void* owner, Telegram telegram);


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(HeroDead, HeroState);
__SINGLETON(HeroDead);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void __attribute__ ((noinline)) HeroDead_constructor(HeroDead this)
{
	// construct base
	__CONSTRUCT_BASE(HeroState);
}

// class's destructor
void HeroDead_destructor(HeroDead this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
void HeroDead_enter(HeroDead this __attribute__ ((unused)), void* owner __attribute__ ((unused)))
{
	KeypadManager_registerInput(KeypadManager_getInstance(), __KEY_PRESSED);
}

// state's exit
void HeroDead_exit(HeroDead this __attribute__ ((unused)), void* owner __attribute__ ((unused)))
{
}

void HeroDead_onKeyPressed(HeroDead this __attribute__ ((unused)), void* owner __attribute__ ((unused)), const UserInput* userInput)
{
	if((K_LL | K_LR | K_A) & userInput->pressedKey)
	{
		//Container_deleteMyself(__SAFE_CAST(Container, &owner));
		return;
	}
}
