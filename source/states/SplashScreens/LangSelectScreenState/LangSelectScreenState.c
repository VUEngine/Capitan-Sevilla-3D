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
#include <TitleScreenState.h>
#include <Languages.h>
#include <KeyPadManager.h>
#include <Utilities.h>
#include <ProgressManager.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef EMPTY_STAGE_ST;
extern LangROMDef* __LANGUAGES[];


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void LangSelectScreenState_destructor(LangSelectScreenState this);
static void LangSelectScreenState_constructor(LangSelectScreenState this);
static void LangSelectScreenState_processInput(LangSelectScreenState this, u32 pressedKey);
static void LangSelectScreenState_print(LangSelectScreenState this);


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(LangSelectScreenState, SplashScreenState);
__SINGLETON_DYNAMIC(LangSelectScreenState);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

static void __attribute__ ((noinline)) LangSelectScreenState_constructor(LangSelectScreenState this)
{
	__CONSTRUCT_BASE(SplashScreenState);

	SplashScreenState_setNextState(__SAFE_CAST(SplashScreenState, this), __SAFE_CAST(GameState, TitleScreenState_getInstance()));
	this->stageDefinition = (StageDefinition*)&EMPTY_STAGE_ST;

	// create options selector and populate with language names
	this->languageSelector = __NEW(OptionsSelector, 1, 8, NULL);
	VirtualList languageNames = __NEW(VirtualList);

	u8 activeLanguage = ProgressManager_getLanguage(ProgressManager_getInstance());

	int i = 0;
	for(; __LANGUAGES[i]; i++)
	{
		I18n_setActiveLanguage(I18n_getInstance(), i);

		Option* option = __NEW_BASIC(Option);
		option->value = (char*)I18n_getActiveLanguageName(I18n_getInstance());
		option->type = kString;
		VirtualList_pushBack(languageNames, option);
	}

	OptionsSelector_setOptions(this->languageSelector, languageNames);
	__DELETE(languageNames);

	I18n_setActiveLanguage(I18n_getInstance(), activeLanguage);
	OptionsSelector_setSelectedOption(this->languageSelector, activeLanguage);
}

static void LangSelectScreenState_destructor(LangSelectScreenState this)
{
	__DELETE(this->languageSelector);

	// destroy base
	__SINGLETON_DESTROY;
}

void LangSelectScreenState_processInput(LangSelectScreenState this, u32 pressedKey)
{
	if((pressedKey & K_LU) || (pressedKey & K_RU))
	{
		OptionsSelector_selectPrevious(this->languageSelector);
	}
	else if((pressedKey & K_LD) || (pressedKey & K_RD))
	{
		OptionsSelector_selectNext(this->languageSelector);
	}
	else if((pressedKey & K_A) || (pressedKey & K_STA))
	{
		int selectedLanguage = OptionsSelector_getSelectedOption(this->languageSelector);
		I18n_setActiveLanguage(I18n_getInstance(), selectedLanguage);
		ProgressManager_setLanguage(ProgressManager_getInstance(), selectedLanguage);
		SplashScreenState_loadNextState(__SAFE_CAST(SplashScreenState, this));
	}
}

static void LangSelectScreenState_print(LangSelectScreenState this)
{
	// print header
	const char* strLanguageSelectTitle = I18n_getText(I18n_getInstance(), STR_LANGUAGE);
	const char* strLanguageSelectTitleFont = "LargeFont";
	FontSize size = Printing_getTextSize(Printing_getInstance(), strLanguageSelectTitle, strLanguageSelectTitleFont);
	u8 strHeaderXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (size.x >> 1);
	Printing_text(
		Printing_getInstance(),
		Utilities_toUppercase(strLanguageSelectTitle),
		strHeaderXPos,
		8,
		strLanguageSelectTitleFont
	);

	// print options
	OptionsSelector_printOptions(this->languageSelector, strHeaderXPos, 9 + size.y);
}

