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

#ifndef HERO_MOVING_H_
#define HERO_MOVING_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <HeroState.h>
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define HeroMoving_METHODS(ClassName)																	\
		HeroState_METHODS(ClassName)																	\

// declare the virtual methods which are redefined
#define HeroMoving_SET_VTABLE(ClassName)																\
		HeroState_SET_VTABLE(ClassName)																	\
		__VIRTUAL_SET(ClassName, HeroMoving, enter);													\
		__VIRTUAL_SET(ClassName, HeroMoving, execute);													\
		__VIRTUAL_SET(ClassName, HeroMoving, processMessage);											\
		__VIRTUAL_SET(ClassName, HeroMoving, onKeyPressed);												\
		__VIRTUAL_SET(ClassName, HeroMoving, onKeyReleased);											\

#define HeroMoving_ATTRIBUTES																			\
		/* inherits */																					\
		HeroState_ATTRIBUTES																			\
		/* flag to allow jump on bouncing */															\
		bool bouncing;																					\

 __CLASS(HeroMoving);


enum HeroMovingMessages
{
	 kDisallowJumpOnBouncing = kLastPlatformerMessage + 1,
};


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

HeroMoving HeroMoving_getInstance();

void HeroMoving_onKeyPressed(HeroMoving this, void* owner, const UserInput* userInput);
void HeroMoving_onKeyReleased(HeroMoving this, void* owner, const UserInput* userInput);


#endif
