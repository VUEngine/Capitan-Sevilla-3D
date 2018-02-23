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
#include <Utilities.h>
#include <I18n.h>
#include <AutoPauseSelectScreenState.h>
#include <LangSelectScreenState.h>
#include <AutoPauseScreenState.h>
#include <Languages.h>
#include <KeyPadManager.h>
#include <ProgressManager.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef EMPTY_STAGE_ST;


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void AutoPauseSelectScreenState_destructor(AutoPauseSelectScreenState this);
static void AutoPauseSelectScreenState_constructor(AutoPauseSelectScreenState this);
static void AutoPauseSelectScreenState_print(AutoPauseSelectScreenState this);
static void AutoPauseSelectScreenState_renderSelection(AutoPauseSelectScreenState this);
static void AutoPauseSelectScreenState_processInput(AutoPauseSelectScreenState this, u32 pressedKey);


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(AutoPauseSelectScreenState, SplashScreenState);
__SINGLETON_DYNAMIC(AutoPauseSelectScreenState);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void __attribute__ ((noinline)) AutoPauseSelectScreenState_constructor(AutoPauseSelectScreenState this)
{
	__CONSTRUCT_BASE(SplashScreenState);

	SplashScreenState_setNextState(__SAFE_CAST(SplashScreenState, this), __SAFE_CAST(GameState, LangSelectScreenState_getInstance()));
	this->stageDefinition = (StageDefinition*)&EMPTY_STAGE_ST;
	this->selection = true;
}

// class's destructor
static void AutoPauseSelectScreenState_destructor(AutoPauseSelectScreenState this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

static void AutoPauseSelectScreenState_print(AutoPauseSelectScreenState this)
{
	this->selection = ProgressManager_getAutomaticPauseStatus(ProgressManager_getInstance());

	const char* strAutomaticPauseTitle = I18n_getText(I18n_getInstance(), STR_AUTOMATIC_PAUSE);
	const char* strAutomaticPauseTitleFont = "LargeFont";
	FontSize strAutomaticPauseSize = Printing_getTextSize(Printing_getInstance(), strAutomaticPauseTitle, strAutomaticPauseTitleFont);

	const char* strAutomaticPauseExplanation = I18n_getText(I18n_getInstance(), STR_AUTO_PAUSE_EXPLANATION);
	FontSize strAutomaticPauseExplanationSize = Printing_getTextSize(Printing_getInstance(), strAutomaticPauseExplanation, NULL);

	u8 strHeaderXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (strAutomaticPauseSize.x >> 1);
	Printing_text(
		Printing_getInstance(),
		Utilities_toUppercase(strAutomaticPauseTitle),
		strHeaderXPos,
		8,
		strAutomaticPauseTitleFont
	);

	u8 strExplanationXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (strAutomaticPauseExplanationSize.x >> 1);
	Printing_text(Printing_getInstance(), strAutomaticPauseExplanation, strExplanationXPos, 9 + strAutomaticPauseSize.y, NULL);

	AutoPauseSelectScreenState_renderSelection(this);
}

static void AutoPauseSelectScreenState_renderSelection(AutoPauseSelectScreenState this)
{
	const char* strOn = I18n_getText(I18n_getInstance(), STR_ON);
	const char* strOff = I18n_getText(I18n_getInstance(), STR_OFF);

	// get strings and determine sizes
	FontSize strOnSize = Printing_getTextSize(Printing_getInstance(), strOn, NULL);
	FontSize strOffSize = Printing_getTextSize(Printing_getInstance(), strOff, NULL);
	u8 selectionStart = (48 - (strOnSize.x + __OPTIONS_GAP + strOffSize.x)) >> 1;

	// clear options area
	Printing_text(Printing_getInstance(), "                                                ", 0, __OPTIONS_Y_POS, NULL);
	Printing_text(Printing_getInstance(), "                                                ", 0, __OPTIONS_Y_POS + 1, NULL);
	Printing_text(Printing_getInstance(), "                                                ", 0, __OPTIONS_Y_POS + 2, NULL);
	if(strOnSize.y > 1) {
		Printing_text(Printing_getInstance(), "                                                ", 0, __OPTIONS_Y_POS + 3, NULL);
		if(strOnSize.y > 2) {
			Printing_text(Printing_getInstance(), "                                                ", 0, __OPTIONS_Y_POS + 4, NULL);
			if(strOnSize.y > 3) {
				Printing_text(Printing_getInstance(), "                                                ", 0, __OPTIONS_Y_POS + 5, NULL);
			}
		}
	}

	// print options
	Printing_text(Printing_getInstance(), strOn, selectionStart, __OPTIONS_Y_POS + 1, NULL);
	Printing_text(Printing_getInstance(), strOff, selectionStart + 3 + strOnSize.x, __OPTIONS_Y_POS + 1, NULL);

	// print selector
	u8 optionStart = this->selection ? selectionStart : selectionStart + __OPTIONS_GAP + strOnSize.x;
	u8 optionEnd = this->selection ? optionStart + strOnSize.x : optionStart + strOffSize.x;
	optionStart--;
	Printing_text(Printing_getInstance(), "\x03\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08", optionStart, __OPTIONS_Y_POS, NULL);
	Printing_text(Printing_getInstance(), "\x04               ", optionEnd, __OPTIONS_Y_POS, NULL);
	Printing_text(Printing_getInstance(), "\x07", optionStart, __OPTIONS_Y_POS + 1, NULL);
	Printing_text(Printing_getInstance(), "\x07", optionEnd, __OPTIONS_Y_POS + 1, NULL);
	if(strOnSize.y > 1) {
		Printing_text(Printing_getInstance(), "\x07", optionStart, __OPTIONS_Y_POS + 2, NULL);
		Printing_text(Printing_getInstance(), "\x07", optionEnd, __OPTIONS_Y_POS + 2, NULL);
		if(strOnSize.y > 2) {
			Printing_text(Printing_getInstance(), "\x07", optionStart, __OPTIONS_Y_POS + 3, NULL);
			Printing_text(Printing_getInstance(), "\x07", optionEnd, __OPTIONS_Y_POS + 3, NULL);
			if(strOnSize.y > 3) {
				Printing_text(Printing_getInstance(), "\x07", optionStart, __OPTIONS_Y_POS + 4, NULL);
				Printing_text(Printing_getInstance(), "\x07", optionEnd, __OPTIONS_Y_POS + 4, NULL);
			}
		}
	}
	Printing_text(Printing_getInstance(), "\x05\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08", optionStart, __OPTIONS_Y_POS + 1 + strOnSize.y, NULL);
	Printing_text(Printing_getInstance(), "\x06               ", optionEnd, __OPTIONS_Y_POS + 1 + strOnSize.y, NULL);
}

void AutoPauseSelectScreenState_processInput(AutoPauseSelectScreenState this, u32 pressedKey)
{
	if((pressedKey & K_LL) || (pressedKey & K_LR))
	{
		this->selection = !this->selection;
		AutoPauseSelectScreenState_renderSelection(this);
	}
	else if((pressedKey & K_A) || (pressedKey & K_STA))
	{
		Game_setAutomaticPauseState(Game_getInstance(), this->selection
			? __SAFE_CAST(GameState, AutoPauseScreenState_getInstance())
			: NULL
		);
		ProgressManager_setAutomaticPauseStatus(ProgressManager_getInstance(), (bool)this->selection);
		SplashScreenState_loadNextState(__SAFE_CAST(SplashScreenState, this));
	}
}
