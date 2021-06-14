/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
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
#include <KeypadManager.h>
#include <Utilities.h>
#include <Captain.h>
#include <Languages.h>
#include <PauseScreenState.h>
#include <OptionsScreenState.h>
#include <PlatformerLevelState.h>
#include <TitleScreenState.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMSpec PAUSE_SCREEN_STAGE_ST;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void PauseScreenState::constructor()
{
	Base::constructor();

	// init members
	this->mode = kPauseScreenModeShowOptions;
	this->optionsSelector = new OptionsSelector(1, 3, "Capitan");
}

void PauseScreenState::destructor()
{
	delete this->optionsSelector;

	// destroy base
	Base::destructor();
}

void PauseScreenState::enter(void* owner __attribute__ ((unused)))
{
	// call base
	Base::enter(this, owner);

	// load stage
	GameState::loadStage(this, (StageSpec*)&PAUSE_SCREEN_STAGE_ST, NULL, true, false);

	// show up level after a little delay
	MessageDispatcher::dispatchMessage(1, Object::safeCast(this), Object::safeCast(Game::getInstance()), kLevelSetUp, NULL);

	// print pause text
	const char* strPause = I18n::getText(I18n::getInstance(), STR_PAUSE);
	FontSize strPauseSize = Printing::getTextSize(Printing::getInstance(), strPause, "Capitan");
	Printing::text(
		Printing::getInstance(),
		Utilities::toUppercase(strPause),
		(((__SCREEN_WIDTH_IN_CHARS) - strPauseSize.x) >> 1),
		14,
		"Capitan"
	);

	// show menu
	VirtualList options = new VirtualList();
	Option* option = NULL;

	option = new Option;
	option->value = (char*)I18n::getText(I18n::getInstance(), STR_CONTINUE);
	option->type = kString;
	option->callback = NULL;
	option->callbackScope = NULL;
	VirtualList::pushBack(options, option);

	option = new Option;
	option->value = (char*)I18n::getText(I18n::getInstance(), STR_OPTIONS);
	option->type = kString;
	option->callback = NULL;
	option->callbackScope = NULL;
	VirtualList::pushBack(options, option);

	option = new Option;
	option->value = (char*)I18n::getText(I18n::getInstance(), STR_QUIT_GAME);
	option->type = kString;
	option->callback = NULL;
	option->callbackScope = NULL;
	VirtualList::pushBack(options, option);

	OptionsSelector::setOptions(this->optionsSelector, options);
	delete options;

	OptionsSelector::printOptions(
		this->optionsSelector,
		(((__SCREEN_WIDTH_IN_CHARS) - strPauseSize.x) >> 1) - 1,
		17
	);

	// disable user input
	Game::disableKeypad(Game::getInstance());

	// start clocks to start animations
	GameState::startClocks(this);

	// fade in screen
	Camera::startEffect(Camera::getInstance(), kHide);
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))PauseScreenState::onFadeInComplete, // callback function
		Object::safeCast(this) // callback scope
	);

	this->mode = kPauseScreenModeShowOptions;
}

void PauseScreenState::exit(void* owner __attribute__ ((unused)))
{
	// call base
	Base::exit(this, owner);
}

void PauseScreenState::processUserInput(UserInput userInput)
{
	if((K_STA & userInput.pressedKey) || (K_A & userInput.pressedKey))
	{
		if(this->mode == kPauseScreenModeShowOptions)
		{
			int selectedOption = OptionsSelector::getSelectedOption(this->optionsSelector);

			switch(selectedOption)
			{
				case kPauseScreenOptionContinue:
				case kPauseScreenOptionOptions:

					// disable user input
					Game::disableKeypad(Game::getInstance());

					// fade out screen
					Brightness brightness = (Brightness){0, 0, 0};
					Camera::startEffect(Camera::getInstance(),
						kFadeTo, // effect type
						0, // initial delay (in ms)
						&brightness, // target brightness
						__FADE_DELAY, // delay between fading steps (in ms)
						(void (*)(Object, Object))PauseScreenState::onFadeOutComplete, // callback function
						Object::safeCast(this) // callback scope
					);

					break;

				case kPauseScreenOptionQuitLevel:
				{
					// print confirmation message
					const char* strYes = I18n::getText(I18n::getInstance(), STR_YES);
					FontSize strYesSize = Printing::getTextSize(Printing::getInstance(), strYes, "Capitan");
					const char* strNo = I18n::getText(I18n::getInstance(), STR_NO);
					const char* strAreYouSure = I18n::getText(I18n::getInstance(), STR_ARE_YOU_SURE);
					const char* strPause = I18n::getText(I18n::getInstance(), STR_PAUSE);
					FontSize strPauseSize = Printing::getTextSize(Printing::getInstance(), strPause, "Capitan");

					u8 strXPos = ((__SCREEN_WIDTH_IN_CHARS) - strPauseSize.x) >> 1;
					u8 strNoXPos = strXPos + strYesSize.x + 2;

					Printing::text(Printing::getInstance(), strAreYouSure, strXPos, 21, "Capitan");
					Printing::text(Printing::getInstance(), __CHAR_A_BUTTON, strXPos, 22, "Capitan");
					Printing::text(Printing::getInstance(), strYes, strXPos + 1, 22, "Capitan");
					Printing::text(Printing::getInstance(), __CHAR_B_BUTTON, strNoXPos, 22, "Capitan");
					Printing::text(Printing::getInstance(), strNo, strNoXPos + 1, 22, "Capitan");

					// set mode accordingly
					this->mode = kPauseScreenModeShowConfirmQuit;
					break;
				}
			}
		}
		else if(this->mode == kPauseScreenModeShowConfirmQuit)
		{
			// disable user input
			Game::disableKeypad(Game::getInstance());

			// fade out screen
			Brightness brightness = (Brightness){0, 0, 0};
			Camera::startEffect(Camera::getInstance(),
				kFadeTo, // effect type
				0, // initial delay (in ms)
				&brightness, // target brightness
				__FADE_DELAY, // delay between fading steps (in ms)
				(void (*)(Object, Object))PauseScreenState::onFadeOutComplete, // callback function
				Object::safeCast(this) // callback scope
			);
		}
	}
	else if((this->mode == kPauseScreenModeShowConfirmQuit) && (userInput.pressedKey & K_B))
	{
		// remove confirmation message
		Printing::text(Printing::getInstance(), "                                                ", 0, 21, "Capitan");
		Printing::text(Printing::getInstance(), "                                                ", 0, 22, "Capitan");

		// set mode back to main menu
		this->mode = kPauseScreenModeShowOptions;
	}
	else if((this->mode == kPauseScreenModeShowOptions) && ((userInput.pressedKey & K_LU) || (userInput.pressedKey & K_RU)))
	{
		OptionsSelector::selectPrevious(this->optionsSelector);
	}
	else if((this->mode == kPauseScreenModeShowOptions) && ((userInput.pressedKey & K_LD) || (userInput.pressedKey & K_RD)))
	{
		OptionsSelector::selectNext(this->optionsSelector);
	}
}

void PauseScreenState::onFadeInComplete(Object eventFirer __attribute__ ((unused)))
{
	Game::enableKeypad(Game::getInstance());
}

void PauseScreenState::onFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	// re-enable user input
	Game::enableKeypad(Game::getInstance());

	// switch state according to selection
	int selectedOption = OptionsSelector::getSelectedOption(this->optionsSelector);
	switch(selectedOption)
	{
		case kPauseScreenOptionContinue:

			// resume game
			Game::unpause(Game::getInstance(), GameState::safeCast(this));
			break;

		case kPauseScreenOptionOptions:

			// switch to options state
			OptionsScreenState::setNextState(OptionsScreenState::getInstance(), GameState::safeCast(this));
			Game::changeState(Game::getInstance(), GameState::safeCast(OptionsScreenState::getInstance()));
			break;

		case kPauseScreenOptionQuitLevel:

			// switch to overworld after deleting paused game state
			Game::cleanAndChangeState(Game::getInstance(), GameState::safeCast(TitleScreenState::getInstance()));

			break;
	}
}
