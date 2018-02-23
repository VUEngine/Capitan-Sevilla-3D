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

#ifndef HERO_IDLE_H_
#define HERO_IDLE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <HeroState.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define HeroIdle_METHODS(ClassName)																		\
		HeroState_METHODS(ClassName)																	\

// declare the virtual methods which are redefined
#define HeroIdle_SET_VTABLE(ClassName)																	\
		HeroState_SET_VTABLE(ClassName)																	\
		__VIRTUAL_SET(ClassName, HeroIdle, enter);														\
		__VIRTUAL_SET(ClassName, HeroIdle, exit);														\
		__VIRTUAL_SET(ClassName, HeroIdle, processMessage);												\
		__VIRTUAL_SET(ClassName, HeroIdle, onKeyPressed);												\
		__VIRTUAL_SET(ClassName, HeroIdle, onKeyReleased);												\
		__VIRTUAL_SET(ClassName, HeroIdle, onKeyHold);													\

__CLASS(HeroIdle);

#define HeroIdle_ATTRIBUTES																				\
		/* inherits */																					\
		HeroState_ATTRIBUTES																			\


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

HeroIdle HeroIdle_getInstance();

void HeroIdle_onKeyPressed(HeroIdle this, void* owner, const UserInput* userInput);
void HeroIdle_onKeyReleased(HeroIdle this, void* owner, const UserInput* userInput);
void HeroIdle_onKeyHold(HeroIdle this, void* owner, const UserInput* userInput);


#endif
