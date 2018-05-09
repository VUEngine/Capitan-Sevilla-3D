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

#include <Game.h>
#include <Camera.h>
#include <MessageDispatcher.h>
#include <SplashScreenState.h>
#include <KeypadManager.h>


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void SplashScreenState_onFadeInComplete(SplashScreenState this, Object eventFirer);
static void SplashScreenState_onFadeOutComplete(SplashScreenState this, Object eventFirer);


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(SplashScreenState, GameState);



//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void SplashScreenState_constructor(SplashScreenState this)
{
	__CONSTRUCT_BASE(GameState);

	this->stageDefinition = NULL;
}

// class's destructor
void SplashScreenState_destructor(SplashScreenState this)
{
	// destroy the super object
	// must always be called at the end of the destructor
	Base_destructor();
}

// state's enter
void SplashScreenState_enter(SplashScreenState this, void* owner)
{
	// call base
	Base_enter(this, owner);

	if(this->stageDefinition)
	{
		GameState_loadStage(__SAFE_CAST(GameState, this), this->stageDefinition, NULL, true);
	}

	SplashScreenState_print(this);

	// start fade in effect in 1 ms, because a full render cycle is needed to put everything in place
	MessageDispatcher_dispatchMessage(1, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game_getInstance()), kScreenStarted, NULL);

	Game_disableKeypad(Game_getInstance());
}

// state's exit
void SplashScreenState_exit(SplashScreenState this, void* owner)
{
	// call base
	Base_exit(this, owner);

	// destroy the state
	__DELETE(this);
}

// state's resume
void SplashScreenState_resume(SplashScreenState this, void* owner)
{
	Base_resume(this, owner);

	SplashScreenState_print(this);

#ifdef __DEBUG_TOOLS
	if(!Game_isExitingSpecialMode(Game_getInstance()))
	{
#endif
#ifdef __STAGE_EDITOR
	if(!Game_isExitingSpecialMode(Game_getInstance()))
	{
#endif
#ifdef __ANIMATION_INSPECTOR
	if(!Game_isExitingSpecialMode(Game_getInstance()))
	{
#endif

	// start a fade in effect
	Camera_startEffect(Camera_getInstance(), kFadeIn, __FADE_DELAY);

#ifdef __DEBUG_TOOLS
	}
#endif
#ifdef __STAGE_EDITOR
	}
#endif
#ifdef __ANIMATION_INSPECTOR
	}
#endif
}

void SplashScreenState_processUserInput(SplashScreenState this, UserInput userInput)
{
	if(userInput.pressedKey & ~K_PWR)
	{
		SplashScreenState_processInput(this, userInput.pressedKey);
	}
}

// state's handle message
bool SplashScreenState_processMessage(SplashScreenState this, void* owner __attribute__ ((unused)), Telegram telegram)
{
	switch(Telegram_getMessage(telegram))
	{
		case kScreenStarted:

			// start fade in effect
			Camera_startEffect(Camera_getInstance(),
				kFadeTo, // effect type
				0, // initial delay (in ms)
				NULL, // target brightness
				__FADE_DELAY, // delay between fading steps (in ms)
				(void (*)(Object, Object))SplashScreenState_onFadeInComplete, // callback function
				__SAFE_CAST(Object, this) // callback scope
			);

			break;
	}

	return false;
}

void SplashScreenState_processInput(SplashScreenState this, u32 pressedKey __attribute__ ((unused)))
{
	SplashScreenState_loadNextState(this);
}

void SplashScreenState_print(SplashScreenState this __attribute__ ((unused)))
{
}

void SplashScreenState_setNextState(SplashScreenState this, GameState nextState)
{
	this->nextState = nextState;
}

void SplashScreenState_loadNextState(SplashScreenState this)
{
	// disable user input
	Game_disableKeypad(Game_getInstance());

	// start fade out effect
	Brightness brightness = (Brightness){0, 0, 0};
	Camera_startEffect(Camera_getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		&brightness, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))SplashScreenState_onFadeOutComplete, // callback function
		__SAFE_CAST(Object, this) // callback scope
	);
}

// handle event
static void SplashScreenState_onFadeInComplete(SplashScreenState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "SplashScreenState::onFadeInComplete: null this");

	// enable user input
	Game_enableKeypad(Game_getInstance());
}

// handle event
static void SplashScreenState_onFadeOutComplete(SplashScreenState this, Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "SplashScreenState::onFadeOutComplete: null this");

	// change to next stage
	Game_changeState(Game_getInstance(), this->nextState);
}
