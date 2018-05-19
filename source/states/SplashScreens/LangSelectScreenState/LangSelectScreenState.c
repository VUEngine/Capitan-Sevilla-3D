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
#include <I18n.h>
#include <LangSelectScreenState.h>
#include <AutoPauseSelectScreenState.h>
#include <Languages.h>
#include <KeyPadManager.h>
#include <Utilities.h>
#include <ProgressManager.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef LANG_SELECT_SCREEN_STAGE_ST;
extern LangROMDef* __LANGUAGES[];


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void LangSelectScreenState::constructor()
{


	Base::constructor();

	// init members
	this->language = 0;
	SplashScreenState::setNextState(SplashScreenState::safeCast(this), GameState::safeCast(AutoPauseSelectScreenState::getInstance()));
	this->stageDefinition = (StageDefinition*)&LANG_SELECT_SCREEN_STAGE_ST;
}

void LangSelectScreenState::destructor()
{


	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
void LangSelectScreenState::enter(void* owner)
{
	// call base
	Base::enter(this, owner);

	this->language = I18n::getActiveLanguage(I18n::getInstance());
	LangSelectScreenState::print(this);
}

void LangSelectScreenState::changeLanguage(bool increase)
{
	int numLangs = sizeof(*__LANGUAGES);
	this->language = increase
		? (this->language < (numLangs - 1)) ? this->language + 1 : 0
		: (this->language > 0) ? this->language - 1 : numLangs - 1;
	I18n::setActiveLanguage(I18n::getInstance(), this->language);
	ProgressManager::setLanguage(ProgressManager::getInstance(), this->language);
	LangSelectScreenState::print(this);
}

void LangSelectScreenState::processInput(u32 pressedKey)
{
	if((pressedKey & K_LL) || (pressedKey & K_RL))
	{
		LangSelectScreenState::changeLanguage(this, false);
	}
	else if((pressedKey & K_LR) || (pressedKey & K_RR))
	{
		LangSelectScreenState::changeLanguage(this, true);
	}
	else if((pressedKey & K_A) || (pressedKey & K_STA))
	{
		SplashScreenState::loadNextState(SplashScreenState::safeCast(this));
	}
}

void LangSelectScreenState::print()
{
	// move cursor entity
	Entity cursorEntity = Entity::safeCast(Container::getChildByName(
		Container::safeCast(Game::getStage(Game::getInstance())),
		"Cursor",
		false
	));
	Vector3D position = {__PIXELS_TO_METERS(120 + this->language * 48), __PIXELS_TO_METERS(96), 0};
	Entity::setLocalPosition(cursorEntity, &position);

	/*
	// print header
	const char* strLanguageSelectTitle = I18n::getText(I18n::getInstance(), STR_LANGUAGE);
	FontSize strLanguageSelectTitleSize = Printing::getTextSize(Printing::getInstance(), strLanguageSelectTitle, NULL);
	Printing::text(Printing::getInstance(), "                                                ", 0, 8, NULL);
	Printing::text(
		Printing::getInstance(),
		Utilities::toUppercase(strLanguageSelectTitle),
		(__SCREEN_WIDTH_IN_CHARS - strLanguageSelectTitleSize.x) >> 1,
		8,
		NULL
	);
	*/

	// print current language
	const char* strActiveLanguageName = (char*)I18n::getActiveLanguageName(I18n::getInstance());
	FontSize strActiveLanguageNameSize = Printing::getTextSize(Printing::getInstance(), strActiveLanguageName, NULL);
	Printing::text(Printing::getInstance(), "                                                ", 0, 15, NULL);
	Printing::text(
		Printing::getInstance(),
		Utilities::toUppercase(strActiveLanguageName),
		(__SCREEN_WIDTH_IN_CHARS - strActiveLanguageNameSize.x) >> 1,
		15,
		NULL
	);
}

