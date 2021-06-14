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
#include <I18n.h>
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

extern StageROMSpec EMPTY_STAGE_ST;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void OptionsScreenState::constructor()
{
	Base::constructor();

	// init members
	this->optionsSelector = new OptionsSelector(1, 2, "Capitan");
	OptionsScreenState::setNextState(this, GameState::safeCast(TitleScreenState::getInstance()));
}

void OptionsScreenState::destructor()
{
	delete this->optionsSelector;

	// destroy base
	Base::destructor();
}

void OptionsScreenState::enter(void* owner __attribute__ ((unused)))
{
	// call base
	Base::enter(this, owner);

	// load stage
	GameState::loadStage(this, (StageSpec*)&EMPTY_STAGE_ST, NULL, true, false);

	// print options
	OptionsScreenState::print(this);

	// disable user input
	Game::disableKeypad(Game::getInstance());

	// fade in screen
	Camera::startEffect(Camera::getInstance(), kHide);
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))OptionsScreenState::onFadeInComplete, // callback function
		Object::safeCast(this) // callback scope
	);
}

void OptionsScreenState::exit(void* owner __attribute__ ((unused)))
{
	// call base
	Base::exit(this, owner);
}

// set next state
void OptionsScreenState::setNextState(GameState nextState)
{
	this->nextState = nextState;
}

// print level stats
void OptionsScreenState::print()
{
	// title
	const char* strOptionsTitle = I18n::getText(I18n::getInstance(), STR_OPTIONS);
	FontSize strOptionsTextSize = Printing::getTextSize(Printing::getInstance(), strOptionsTitle, "Capitan");
	Printing::text(
		Printing::getInstance(),
		strOptionsTitle,
		((__SCREEN_WIDTH_IN_CHARS) - strOptionsTextSize.x) >> 1,
		8,
		"Capitan"
	);

	// menu
	VirtualList options = new VirtualList();
	Option* option = NULL;

	option = new Option;
	option->value = (char*)I18n::getText(I18n::getInstance(), STR_AUTOMATIC_PAUSE);
	option->type = kString;
	option->callback = (void (*)(Object))OptionsScreenState::onOptionAutoPauseSelect;
	option->callbackScope = Object::safeCast(this);
	VirtualList::pushBack(options, option);

	option = new Option;
	option->value = (char*)I18n::getText(I18n::getInstance(), STR_LANGUAGE);
	option->type = kString;
	option->callback = (void (*)(Object))OptionsScreenState::onOptionLanguageSelect;
	option->callbackScope = Object::safeCast(this);
	VirtualList::pushBack(options, option);

	OptionsSelector::setOptions(this->optionsSelector, options);
	delete options;

	OptionsSelector::printOptions(
		this->optionsSelector,
		((__SCREEN_WIDTH_IN_CHARS) - strOptionsTextSize.x) >> 1,
		11
	);

	// buttons
	const char* strSelect = I18n::getText(I18n::getInstance(), STR_SELECT);
	FontSize strSelectSize = Printing::getTextSize(Printing::getInstance(), strSelect, "Capitan");
	const char* strBack = I18n::getText(I18n::getInstance(), STR_BACK);

	u8 strSelectXPos = ((__SCREEN_WIDTH_IN_CHARS) - strOptionsTextSize.x) >> 1;
	u8 strBackXPos = strSelectXPos + strSelectSize.x + 2;

	Printing::text(Printing::getInstance(), __CHAR_A_BUTTON, strSelectXPos, 15, "Capitan");
	Printing::text(Printing::getInstance(), strSelect, strSelectXPos + 1, 15, "Capitan");
	Printing::text(Printing::getInstance(), __CHAR_B_BUTTON, strBackXPos, 15, "Capitan");
	Printing::text(Printing::getInstance(), strBack, strBackXPos + 1, 15, "Capitan");
}

void OptionsScreenState::processUserInput(UserInput userInput)
{
	if((userInput.pressedKey & K_A) || (userInput.pressedKey & K_STA))
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
			(void (*)(Object, Object))OptionsScreenState::onOptionSelectedFadeOutComplete, // callback function
			Object::safeCast(this) // callback scope
		);
	}
	else if((userInput.pressedKey & K_B) || (userInput.pressedKey & K_SEL))
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
			(void (*)(Object, Object))OptionsScreenState::onExitFadeOutComplete, // callback function
			Object::safeCast(this) // callback scope
		);
	}
	else if((userInput.pressedKey & K_LU) || (userInput.pressedKey & K_RU))
	{
		OptionsSelector::selectPrevious(this->optionsSelector);
	}
	else if((userInput.pressedKey & K_LD) || (userInput.pressedKey & K_RD))
	{
		OptionsSelector::selectNext(this->optionsSelector);
	}
}

void OptionsScreenState::onFadeInComplete(Object eventFirer __attribute__ ((unused)))
{
	Game::enableKeypad(Game::getInstance());
}

void OptionsScreenState::onExitFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	// switch to next screen
	Game::changeState(Game::getInstance(), this->nextState);
}

void OptionsScreenState::onOptionSelectedFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	OptionsSelector::doCurrentSelectionCallback(this->optionsSelector);
}

void OptionsScreenState::onOptionAutoPauseSelect()
{
	SplashScreenState::setNextState(SplashScreenState::safeCast(AutoPauseSelectScreenState::getInstance()), GameState::safeCast(this));
	Game::changeState(Game::getInstance(), GameState::safeCast(AutoPauseSelectScreenState::getInstance()));
}

void OptionsScreenState::onOptionLanguageSelect()
{
	SplashScreenState::setNextState(SplashScreenState::safeCast(LangSelectScreenState::getInstance()), GameState::safeCast(this));
	Game::changeState(Game::getInstance(), GameState::safeCast(LangSelectScreenState::getInstance()));
}
