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
#include <LolaSoftScreenState.h>
#include <AutoPauseScreenState.h>
#include <Languages.h>
#include <KeyPadManager.h>
#include <ProgressManager.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef EMPTY_STAGE_ST;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void AutoPauseSelectScreenState::constructor()
{
	Base::constructor();

	SplashScreenState::setNextState(SplashScreenState::safeCast(this), GameState::safeCast(LolaSoftScreenState::getInstance()));
	this->stageDefinition = (StageDefinition*)&EMPTY_STAGE_ST;
	this->selection = true;
}

// class's destructor
void AutoPauseSelectScreenState::destructor()
{
	// destroy base
	__SINGLETON_DESTROY;
}

void AutoPauseSelectScreenState::print()
{
	this->selection = ProgressManager::getAutomaticPauseStatus(ProgressManager::getInstance());

	const char* strAutomaticPauseTitle = I18n::getText(I18n::getInstance(), STR_AUTOMATIC_PAUSE);
	FontSize strAutomaticPauseSize = Printing::getTextSize(Printing::getInstance(), strAutomaticPauseTitle, NULL);

	const char* strAutomaticPauseExplanation = I18n::getText(I18n::getInstance(), STR_AUTO_PAUSE_EXPLANATION);
	FontSize strAutomaticPauseExplanationSize = Printing::getTextSize(Printing::getInstance(), strAutomaticPauseExplanation, NULL);

	u8 strHeaderXPos = __HALF_SCREEN_WIDTH_IN_CHARS - (strAutomaticPauseSize.x >> 1);
	Printing::text(
		Printing::getInstance(),
		Utilities::toUppercase(strAutomaticPauseTitle),
		strHeaderXPos,
		8,
		NULL
	);

	u8 strExplanationXPos = __HALF_SCREEN_WIDTH_IN_CHARS - (strAutomaticPauseExplanationSize.x >> 1);
	Printing::text(
		Printing::getInstance(),
		strAutomaticPauseExplanation,
		strExplanationXPos,
		9 + strAutomaticPauseSize.y,
		NULL
	);

	AutoPauseSelectScreenState::renderSelection(this);
}

void AutoPauseSelectScreenState::renderSelection()
{
	const char* strOn = I18n::getText(I18n::getInstance(), STR_ON);
	const char* strOff = I18n::getText(I18n::getInstance(), STR_OFF);

	// get strings and determine sizes
	FontSize strOnSize = Printing::getTextSize(Printing::getInstance(), strOn, NULL);
	FontSize strOffSize = Printing::getTextSize(Printing::getInstance(), strOff, NULL);
	u8 selectionStart = (48 - (strOnSize.x + __OPTIONS_GAP + strOffSize.x)) >> 1;

	// clear options area
	Printing::text(Printing::getInstance(), "                                                ", 0, __OPTIONS_Y_POS, NULL);
	Printing::text(Printing::getInstance(), "                                                ", 0, __OPTIONS_Y_POS + 1, NULL);
	Printing::text(Printing::getInstance(), "                                                ", 0, __OPTIONS_Y_POS + 2, NULL);

	// print options
	Printing::text(Printing::getInstance(), Utilities::toUppercase(strOn), selectionStart, __OPTIONS_Y_POS + 1, NULL);
	Printing::text(Printing::getInstance(), Utilities::toUppercase(strOff), selectionStart + 3 + strOnSize.x, __OPTIONS_Y_POS + 1, NULL);

	// print selector
	u8 optionStart = this->selection ? selectionStart : selectionStart + __OPTIONS_GAP + strOnSize.x;
	u8 optionEnd = this->selection ? optionStart + strOnSize.x : optionStart + strOffSize.x;
	optionStart--;
	Printing::text(Printing::getInstance(), "\x03\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08", optionStart, __OPTIONS_Y_POS, NULL);
	Printing::text(Printing::getInstance(), "\x04               ", optionEnd, __OPTIONS_Y_POS, NULL);
	Printing::text(Printing::getInstance(), "\x07", optionStart, __OPTIONS_Y_POS + 1, NULL);
	Printing::text(Printing::getInstance(), "\x07", optionEnd, __OPTIONS_Y_POS + 1, NULL);
	Printing::text(Printing::getInstance(), "\x05\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08", optionStart, __OPTIONS_Y_POS + 1 + strOnSize.y, NULL);
	Printing::text(Printing::getInstance(), "\x06               ", optionEnd, __OPTIONS_Y_POS + 1 + strOnSize.y, NULL);
}

void AutoPauseSelectScreenState::processInput(u32 pressedKey)
{
	if((pressedKey & K_LL) || (pressedKey & K_LR))
	{
		this->selection = !this->selection;
		AutoPauseSelectScreenState::renderSelection(this);
	}
	else if((pressedKey & K_A) || (pressedKey & K_STA))
	{
		Game::setAutomaticPauseState(Game::getInstance(), this->selection
			? GameState::safeCast(AutoPauseScreenState::getInstance())
			: NULL
		);
		ProgressManager::setAutomaticPauseStatus(ProgressManager::getInstance(), (bool)this->selection);
		SplashScreenState::loadNextState(SplashScreenState::safeCast(this));
	}
}
