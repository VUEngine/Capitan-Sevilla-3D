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

#ifndef INTRO_STATE_H_
#define INTRO_STATE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <GameState.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define IntroState_METHODS(ClassName)																	\
 		GameState_METHODS(ClassName)											 						\

// declare the virtual methods which are redefined
#define IntroState_SET_VTABLE(ClassName)																\
		GameState_SET_VTABLE(ClassName)								 									\
		__VIRTUAL_SET(ClassName, IntroState, enter);													\
		__VIRTUAL_SET(ClassName, IntroState, exit);														\
		__VIRTUAL_SET(ClassName, IntroState, resume);													\
		__VIRTUAL_SET(ClassName, IntroState, suspend);													\
		__VIRTUAL_SET(ClassName, IntroState, processUserInput);											\

__CLASS(IntroState);

#define IntroState_ATTRIBUTES								 											\
		GameState_ATTRIBUTES																			\
		/* image entity references */																	\
		Entity entityImage1;																			\
		Entity entityImage2;																			\
		Entity entityImage3;																			\
		Entity entityImage4;																			\
		Entity entityImage5;																			\
		Entity entityImage6;																			\
		Entity entityImage7;																			\
		Entity entityImage8;																			\
		/* text entity references */																	\
		Entity entityText1;																				\
		Entity entityText2;																				\
		Entity entityText3;																				\
		Entity entityText4;																				\
		Entity entityText5;																				\
		Entity entityText6;																				\
		Entity entityText7;																				\
		Entity entityText8;																				\
		Entity entityText9;																				\
		/* current intro step */																		\
		u8 currentStep;																					\


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

IntroState IntroState_getInstance(void);
void IntroState_processUserInput(IntroState this, UserInput userInput);


#endif
