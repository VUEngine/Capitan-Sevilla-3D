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

#ifndef HERO_KNEEL_H_
#define HERO_KNEEL_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <HeroState.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define HeroKneel_METHODS(ClassName)																	\
		HeroState_METHODS(ClassName)																	\

// declare the virtual methods which are redefined
#define HeroKneel_SET_VTABLE(ClassName)																	\
		HeroState_SET_VTABLE(ClassName)																	\
		__VIRTUAL_SET(ClassName, HeroKneel, enter);														\
		__VIRTUAL_SET(ClassName, HeroKneel, exit);														\
		__VIRTUAL_SET(ClassName, HeroKneel, processMessage);											\
		__VIRTUAL_SET(ClassName, HeroKneel, onKeyPressed);												\
		__VIRTUAL_SET(ClassName, HeroKneel, onKeyReleased);												\
		__VIRTUAL_SET(ClassName, HeroKneel, onKeyHold);													\

__CLASS(HeroKneel);

#define HeroKneel_ATTRIBUTES																			\
		/* inherits */																					\
		HeroState_ATTRIBUTES																			\


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

HeroKneel HeroKneel_getInstance();

void HeroKneel_onKeyPressed(HeroKneel this, void* owner, const UserInput* userInput);
void HeroKneel_onKeyReleased(HeroKneel this, void* owner, const UserInput* userInput);
void HeroKneel_onKeyHold(HeroKneel this, void* owner, const UserInput* userInput);


#endif