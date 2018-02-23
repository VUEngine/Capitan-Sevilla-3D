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

#ifndef SPLASH_SCREEN_STATE_H_
#define SPLASH_SCREEN_STATE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <GameState.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S ENUMS
//---------------------------------------------------------------------------------------------------------

enum SplashScreensMessageTypes
{
	kScreenStarted = kLastEngineMessage + 1,
	kScreenAllowUserInput
};


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define SplashScreenState_METHODS(ClassName)															\
		GameState_METHODS(ClassName)																	\
		__VIRTUAL_DEC(ClassName, void, print);															\
		__VIRTUAL_DEC(ClassName, void, processInput, u32 releasedKey);									\

// declare the virtual methods which are redefined
#define SplashScreenState_SET_VTABLE(ClassName)															\
		GameState_SET_VTABLE(ClassName)																	\
		__VIRTUAL_SET(ClassName, SplashScreenState, enter);												\
		__VIRTUAL_SET(ClassName, SplashScreenState, exit);												\
		__VIRTUAL_SET(ClassName, SplashScreenState, resume);											\
		__VIRTUAL_SET(ClassName, SplashScreenState, processMessage);									\
		__VIRTUAL_SET(ClassName, SplashScreenState, processInput);										\
		__VIRTUAL_SET(ClassName, SplashScreenState, print);												\
		__VIRTUAL_SET(ClassName, SplashScreenState, processUserInput);									\

__CLASS(SplashScreenState);

#define SplashScreenState_ATTRIBUTES																	\
		/* inherits */																					\
		GameState_ATTRIBUTES																			\
		/* state to enter after this one */																\
		GameState nextState;																			\
		/* definition of screen's stage */																\
		StageDefinition* stageDefinition;																\


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

void SplashScreenState_constructor(SplashScreenState this);
void SplashScreenState_destructor(SplashScreenState this);
void SplashScreenState_enter(SplashScreenState this, void* owner);
void SplashScreenState_exit(SplashScreenState this, void* owner);
void SplashScreenState_resume(SplashScreenState this, void* owner);
bool SplashScreenState_processMessage(SplashScreenState this, void* owner, Telegram telegram);
void SplashScreenState_processInput(SplashScreenState this, u32 releasedKey);
void SplashScreenState_print(SplashScreenState this);
void SplashScreenState_setNextState(SplashScreenState this, GameState nextState);
void SplashScreenState_loadNextState(SplashScreenState this);
void SplashScreenState_processUserInput(SplashScreenState this, UserInput userInput);

#endif
