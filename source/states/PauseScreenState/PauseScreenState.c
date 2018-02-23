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
#include <MessageDispatcher.h>
#include <I18n.h>
#include <PhysicalWorld.h>
#include <PauseScreenState.h>
#include <Hero.h>
#include <OptionsScreenState.h>
#include <PlatformerLevelState.h>
#include <Languages.h>
#include <KeyPadManager.h>
#include <Utilities.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef PAUSE_SCREEN_STAGE_ST;


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void PauseScreenState_destructor(PauseScreenState this);
static void PauseScreenState_constructor(PauseScreenState this);
static void PauseScreenState_enter(PauseScreenState this, void* owner);
static void PauseScreenState_exit(PauseScreenState this, void* owner);
static void PauseScreenState_onFadeInComplete(PauseScreenState this, Object eventFirer);
static void PauseScreenState_onFadeOutComplete(PauseScreenState this, Object eventFirer);


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(PauseScreenState, GameState);
__SINGLETON(PauseScreenState);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void __attribute__ ((noinline)) PauseScreenState_constructor(PauseScreenState this)
{
	__CONSTRUCT_BASE(GameState);

	// init members
	this->mode = kPauseScreenModeShowOptions;
	this->optionsSelector = __NEW(OptionsSelector, 1, 3, NULL);
}

// class's destructor
static void PauseScreenState_destructor(PauseScreenState this)
{
	__DELETE(this->optionsSelector);

	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
static void PauseScreenState_enter(PauseScreenState this, void* owner __attribute__ ((unused)))
{
	// call base
	__CALL_BASE_METHOD(GameState, enter, this, owner);

	// load stage
	GameState_loadStage(__SAFE_CAST(GameState, this), (StageDefinition*)&PAUSE_SCREEN_STAGE_ST, NULL, true);

	// show up level after a little delay
	MessageDispatcher_dispatchMessage(1, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game_getInstance()), kLevelSetUp, NULL);

	// print pause text
	const char* strPause = I18n_getText(I18n_getInstance(), STR_PAUSE);
	const char* strPauseFont = "LargeFont";
	FontSize strPauseSize = Printing_getTextSize(Printing_getInstance(), strPause, strPauseFont);
	Printing_text(
		Printing_getInstance(),
		Utilities_toUppercase(strPause),
		(((__SCREEN_WIDTH_IN_CHARS) - strPauseSize.x) >> 1),
		14,
		strPauseFont
	);

	// show menu
	VirtualList options = __NEW(VirtualList);
	Option* option = NULL;

	option = __NEW_BASIC(Option);
	option->value = (char*)I18n_getText(I18n_getInstance(), STR_CONTINUE);
	option->type = kString;
	option->callback = NULL;
	option->callbackScope = NULL;
	VirtualList_pushBack(options, option);

	option = __NEW_BASIC(Option);
	option->value = (char*)I18n_getText(I18n_getInstance(), STR_OPTIONS);
	option->type = kString;
	option->callback = NULL;
	option->callbackScope = NULL;
	VirtualList_pushBack(options, option);

	option = __NEW_BASIC(Option);
	option->value = (char*)I18n_getText(I18n_getInstance(), STR_QUIT_LEVEL);
	option->type = kString;
	option->callback = NULL;
	option->callbackScope = NULL;
	VirtualList_pushBack(options, option);

	OptionsSelector_setOptions(this->optionsSelector, options);
	__DELETE(options);

	OptionsSelector_printOptions(
		this->optionsSelector,
		(((__SCREEN_WIDTH_IN_CHARS) - strPauseSize.x) >> 1) - 1,
		17
	);

	// disable user input
	Game_disableKeypad(Game_getInstance());

	// start clocks to start animations
	GameState_startClocks(__SAFE_CAST(GameState, this));

	// fade in screen
	Camera_startEffect(Camera_getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))PauseScreenState_onFadeInComplete, // callback function
		__SAFE_CAST(Object, this) // callback scope
	);

	this->mode = kPauseScreenModeShowOptions;
}

// state's exit
static void PauseScreenState_exit(PauseScreenState this, void* owner __attribute__ ((unused)))
{
	// call base
	__CALL_BASE_METHOD(GameState, exit, this, owner);
}

void PauseScreenState_processUserInput(PauseScreenState this, UserInput userInput)
{
	if((K_STA & userInput.pressedKey) || (K_A & userInput.pressedKey))
	{
		if(this->mode == kPauseScreenModeShowOptions)
		{
			int selectedOption = OptionsSelector_getSelectedOption(this->optionsSelector);

			switch(selectedOption)
			{
				case kPauseScreenOptionContinue:
				case kPauseScreenOptionOptions:

					// disable user input
					Game_disableKeypad(Game_getInstance());

					// fade out screen
					Brightness brightness = (Brightness){0, 0, 0};
					Camera_startEffect(Camera_getInstance(),
						kFadeTo, // effect type
						0, // initial delay (in ms)
						&brightness, // target brightness
						__FADE_DELAY, // delay between fading steps (in ms)
						(void (*)(Object, Object))PauseScreenState_onFadeOutComplete, // callback function
						__SAFE_CAST(Object, this) // callback scope
					);

					break;

				case kPauseScreenOptionQuitLevel:
				{
					// print confirmation message
					const char* strYes = I18n_getText(I18n_getInstance(), STR_YES);
					FontSize strYesSize = Printing_getTextSize(Printing_getInstance(), strYes, NULL);
					const char* strNo = I18n_getText(I18n_getInstance(), STR_NO);
					const char* strAreYouSure = I18n_getText(I18n_getInstance(), STR_ARE_YOU_SURE);
					const char* strPause = I18n_getText(I18n_getInstance(), STR_PAUSE);
					const char* strPauseFont = "LargeFont";
					FontSize strPauseSize = Printing_getTextSize(Printing_getInstance(), strPause, strPauseFont);

					u8 strXPos = ((__SCREEN_WIDTH_IN_CHARS) - strPauseSize.x) >> 1;
					u8 strNoXPos = strXPos + strYesSize.x + 2;

					Printing_text(Printing_getInstance(), strAreYouSure, strXPos, 21, NULL);
					Printing_text(Printing_getInstance(), __CHAR_A_BUTTON, strXPos, 22, NULL);
					Printing_text(Printing_getInstance(), strYes, strXPos + 1, 22, NULL);
					Printing_text(Printing_getInstance(), __CHAR_B_BUTTON, strNoXPos, 22, NULL);
					Printing_text(Printing_getInstance(), strNo, strNoXPos + 1, 22, NULL);

					// set mode accordingly
					this->mode = kPauseScreenModeShowConfirmQuit;
					break;
				}
			}
		}
		else if(this->mode == kPauseScreenModeShowConfirmQuit)
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
				(void (*)(Object, Object))PauseScreenState_onFadeOutComplete, // callback function
				__SAFE_CAST(Object, this) // callback scope
			);
		}
	}
	else if((this->mode == kPauseScreenModeShowConfirmQuit) && (userInput.pressedKey & K_B))
	{
		// remove confirmation message
		Printing_text(Printing_getInstance(), "                                                ", 0, 21, NULL);
		Printing_text(Printing_getInstance(), "                                                ", 0, 22, NULL);

		// set mode back to main menu
		this->mode = kPauseScreenModeShowOptions;
	}
	else if((this->mode == kPauseScreenModeShowOptions) && ((userInput.pressedKey & K_LU) || (userInput.pressedKey & K_RU)))
	{
		OptionsSelector_selectPrevious(this->optionsSelector);
	}
	else if((this->mode == kPauseScreenModeShowOptions) && ((userInput.pressedKey & K_LD) || (userInput.pressedKey & K_RD)))
	{
		OptionsSelector_selectNext(this->optionsSelector);
	}
}

// handle event
static void PauseScreenState_onFadeInComplete(PauseScreenState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "PauseScreenState::onFadeInComplete: null this");

	Game_enableKeypad(Game_getInstance());
}

// handle event
static void PauseScreenState_onFadeOutComplete(PauseScreenState this, Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "PauseScreenState::onFadeOutComplete: null this");

	// re-enable user input
	Game_enableKeypad(Game_getInstance());

	// switch state according to selection
	int selectedOption = OptionsSelector_getSelectedOption(this->optionsSelector);
	switch(selectedOption)
	{
		case kPauseScreenOptionContinue:

			// resume game
			Game_unpause(Game_getInstance(), __SAFE_CAST(GameState, this));
			break;

		case kPauseScreenOptionOptions:

			// switch to options state
			OptionsScreenState_setNextState(OptionsScreenState_getInstance(), __SAFE_CAST(GameState, this));
			Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, OptionsScreenState_getInstance()));
			break;

		case kPauseScreenOptionQuitLevel:

			// switch to overworld after deleting paused game state
			Game_cleanAndChangeState(Game_getInstance(), __SAFE_CAST(GameState, PlatformerLevelState_getInstance()));

			break;
	}
}
