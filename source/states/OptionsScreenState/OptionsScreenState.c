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

#include <string.h>

#include <Game.h>
#include <Camera.h>
#include <I18n.h>
#include <Utilities.h>
#include <Languages.h>
#include <SplashScreenState.h>
#include <AutoPauseSelectScreenState.h>
#include <LangSelectScreenState.h>
#include <TitleScreenState.h>
#include <KeypadManager.h>
#include "OptionsScreenState.h"


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef EMPTY_STAGE_ST;


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void OptionsScreenState_destructor(OptionsScreenState this);
static void OptionsScreenState_constructor(OptionsScreenState this);
static void OptionsScreenState_enter(OptionsScreenState this, void* owner);
static void OptionsScreenState_print(OptionsScreenState this);
static void OptionsScreenState_exit(OptionsScreenState this, void* owner);
static void OptionsScreenState_onFadeInComplete(OptionsScreenState this, Object eventFirer);
static void OptionsScreenState_onExitFadeOutComplete(OptionsScreenState this, Object eventFirer);
static void OptionsScreenState_onOptionSelectedFadeOutComplete(OptionsScreenState this, Object eventFirer);
static void OptionsScreenState_onOptionAutoPauseSelect(OptionsScreenState this);
static void OptionsScreenState_onOptionLanguageSelect(OptionsScreenState this);


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(OptionsScreenState, GameState);
__SINGLETON(OptionsScreenState);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void __attribute__ ((noinline)) OptionsScreenState_constructor(OptionsScreenState this)
{
	__CONSTRUCT_BASE(GameState);

	// init members
	this->optionsSelector = __NEW(OptionsSelector, 1, 2, NULL);
	OptionsScreenState_setNextState(this, __SAFE_CAST(GameState, TitleScreenState_getInstance()));
}

// class's destructor
static void OptionsScreenState_destructor(OptionsScreenState this)
{
	__DELETE(this->optionsSelector);

	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
static void OptionsScreenState_enter(OptionsScreenState this, void* owner __attribute__ ((unused)))
{
	// call base
	Base_enter(this, owner);

	// load stage
	GameState_loadStage(__SAFE_CAST(GameState, this), (StageDefinition*)&EMPTY_STAGE_ST, NULL, true);

	// print options
	OptionsScreenState_print(this);

	// disable user input
	Game_disableKeypad(Game_getInstance());

	// fade in screen
	Camera_startEffect(Camera_getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))OptionsScreenState_onFadeInComplete, // callback function
		__SAFE_CAST(Object, this) // callback scope
	);
}

// state's exit
static void OptionsScreenState_exit(OptionsScreenState this, void* owner __attribute__ ((unused)))
{
	// call base
	Base_exit(this, owner);
}

// set next state
void OptionsScreenState_setNextState(OptionsScreenState this, GameState nextState)
{
	this->nextState = nextState;
}

// print level stats
static void OptionsScreenState_print(OptionsScreenState this __attribute__ ((unused)))
{
	ASSERT(this, "OptionsScreenState::print: null this");

	// title
	const char* strOptionsTitle = I18n_getText(I18n_getInstance(), STR_OPTIONS);
	FontSize strOptionsTextSize = Printing_getTextSize(Printing_getInstance(), strOptionsTitle, NULL);
	Printing_text(
		Printing_getInstance(),
		Utilities_toUppercase(strOptionsTitle),
		((__SCREEN_WIDTH_IN_CHARS) - strOptionsTextSize.x) >> 1,
		8,
		NULL
	);

	// menu
	VirtualList options = __NEW(VirtualList);
	Option* option = NULL;

	option = __NEW_BASIC(Option);
	option->value = (char*)I18n_getText(I18n_getInstance(), STR_AUTOMATIC_PAUSE);
	option->type = kString;
	option->callback = (void (*)(Object))OptionsScreenState_onOptionAutoPauseSelect;
	option->callbackScope = __SAFE_CAST(Object, this);
	VirtualList_pushBack(options, option);

	option = __NEW_BASIC(Option);
	option->value = (char*)I18n_getText(I18n_getInstance(), STR_LANGUAGE);
	option->type = kString;
	option->callback = (void (*)(Object))OptionsScreenState_onOptionLanguageSelect;
	option->callbackScope = __SAFE_CAST(Object, this);
	VirtualList_pushBack(options, option);

	OptionsSelector_setOptions(this->optionsSelector, options);
	__DELETE(options);

	OptionsSelector_printOptions(
		this->optionsSelector,
		((__SCREEN_WIDTH_IN_CHARS) - strOptionsTextSize.x) >> 1,
		11
	);

	// buttons
	const char* strSelect = I18n_getText(I18n_getInstance(), STR_SELECT);
	FontSize strSelectSize = Printing_getTextSize(Printing_getInstance(), strSelect, NULL);
	const char* strBack = I18n_getText(I18n_getInstance(), STR_BACK);

	u8 strSelectXPos = ((__SCREEN_WIDTH_IN_CHARS) - strOptionsTextSize.x) >> 1;
	u8 strBackXPos = strSelectXPos + strSelectSize.x + 2;

	Printing_text(Printing_getInstance(), __CHAR_A_BUTTON, strSelectXPos, 15, NULL);
	Printing_text(Printing_getInstance(), strSelect, strSelectXPos + 1, 15, NULL);
	Printing_text(Printing_getInstance(), __CHAR_B_BUTTON, strBackXPos, 15, NULL);
	Printing_text(Printing_getInstance(), strBack, strBackXPos + 1, 15, NULL);
}

void OptionsScreenState_processUserInput(OptionsScreenState this, UserInput userInput)
{
	if((userInput.pressedKey & K_A) || (userInput.pressedKey & K_STA))
	{
		// disable user input
		Game_disableKeypad(Game_getInstance());

		// fade out screen
		Brightness brightness = (Brightness){0, 0, 0};
		Camera_startEffect(Camera_getInstance(),
			kFadeTo, // effect type
			0, // initial delay (in ms)
			&brightness, // target brightness
			__FADE_DELAY, // delay between fading steps (in ms)
			(void (*)(Object, Object))OptionsScreenState_onOptionSelectedFadeOutComplete, // callback function
			__SAFE_CAST(Object, this) // callback scope
		);
	}
	else if((userInput.pressedKey & K_B) || (userInput.pressedKey & K_SEL))
	{
		// disable user input
		Game_disableKeypad(Game_getInstance());

		// fade out screen
		Brightness brightness = (Brightness){0, 0, 0};
		Camera_startEffect(Camera_getInstance(),
			kFadeTo, // effect type
			0, // initial delay (in ms)
			&brightness, // target brightness
			__FADE_DELAY, // delay between fading steps (in ms)
			(void (*)(Object, Object))OptionsScreenState_onExitFadeOutComplete, // callback function
			__SAFE_CAST(Object, this) // callback scope
		);
	}
	else if((userInput.pressedKey & K_LU) || (userInput.pressedKey & K_RU))
	{
		OptionsSelector_selectPrevious(this->optionsSelector);
	}
	else if((userInput.pressedKey & K_LD) || (userInput.pressedKey & K_RD))
	{
		OptionsSelector_selectNext(this->optionsSelector);
	}
}

// handle event
static void OptionsScreenState_onFadeInComplete(OptionsScreenState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "OptionsScreenState::onOptionSelectedFadeOutComplete: null this");

	Game_enableKeypad(Game_getInstance());
}

static void OptionsScreenState_onExitFadeOutComplete(OptionsScreenState this, Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "OptionsScreenState::onExitFadeOutComplete: null this");

	// switch to next screen
	Game_changeState(Game_getInstance(), this->nextState);
}

static void OptionsScreenState_onOptionSelectedFadeOutComplete(OptionsScreenState this, Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "OptionsScreenState::onOptionSelectedFadeOutComplete: null this");

	OptionsSelector_doCurrentSelectionCallback(this->optionsSelector);
}

static void OptionsScreenState_onOptionAutoPauseSelect(OptionsScreenState this)
{
	ASSERT(this, "OptionsScreenState::onOptionAutoPauseSelect: null this");

	SplashScreenState_setNextState(__SAFE_CAST(SplashScreenState, AutoPauseSelectScreenState_getInstance()), __SAFE_CAST(GameState, this));
	Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, AutoPauseSelectScreenState_getInstance()));
}

static void OptionsScreenState_onOptionLanguageSelect(OptionsScreenState this)
{
	ASSERT(this, "OptionsScreenState::onOptionLanguageSelect: null this");

	SplashScreenState_setNextState(__SAFE_CAST(SplashScreenState, LangSelectScreenState_getInstance()), __SAFE_CAST(GameState, this));
	Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, LangSelectScreenState_getInstance()));
}
