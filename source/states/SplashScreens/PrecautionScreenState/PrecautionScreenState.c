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
#include <KeypadManager.h>
#include <I18n.h>
#include <SoundManager.h>
#include <ProgressManager.h>
#include <PrecautionScreenState.h>
#include <AdjustmentScreenState.h>
#include <Utilities.h>
#include <Languages.h>
#include <debugUtilities.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef EMPTY_STAGE_ST;
extern const u16 COLLECT_SND[];


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void PrecautionScreenState::constructor()
{
	Base::constructor();

	SplashScreenState::setNextState(SplashScreenState::safeCast(this), GameState::safeCast(AdjustmentScreenState::getInstance()));
	this->stageDefinition = (StageDefinition*)&EMPTY_STAGE_ST;
}

// class's destructor
void PrecautionScreenState::destructor()
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's handle message
bool PrecautionScreenState::processMessage(void* owner __attribute__ ((unused)), Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kScreenStarted:
			{
				// play start-up sound
				Vector3D position = {0, 0, 0};
				SoundManager::playFxSound(SoundManager::getInstance(), COLLECT_SND, position);

				// wait some seconds for the screen to stabilize, as defined by Nintendo in the official development manual
				Game::wait(Game::getInstance(), 1500);

				// show this screen for at least 2 seconds, as defined by Nintendo in the official development manual (Appendix 1)
				MessageDispatcher::dispatchMessage(2000, Object::safeCast(this), Object::safeCast(Game::getInstance()), kScreenAllowUserInput, NULL);

				// call base class' method
				Base::processMessage(this, owner, telegram);

				// make sure that keypad is not yet enabled
				Game::disableKeypad(Game::getInstance());
			}
			break;

		case kScreenAllowUserInput:
			{
				Game::enableKeypad(Game::getInstance());
			}
			break;
	}

	return false;
}

void PrecautionScreenState::enter(void* owner)
{
	// init progress manager
	ProgressManager::initialize(ProgressManager::getInstance());

	// call base
	Base::enter(this, owner);
}

void PrecautionScreenState::print()
{
	const char* strPrecautionTitle = I18n::getText(I18n::getInstance(), STR_IMPORTANT);
	FontSize titleSize = Printing::getTextSize(Printing::getInstance(), strPrecautionTitle, NULL);

	const char* strPrecautionText = I18n::getText(I18n::getInstance(), STR_PRECAUTION_SCREEN_TEXT);
	FontSize textSize = Printing::getTextSize(Printing::getInstance(), strPrecautionText, NULL);

	u8 totalHeight = titleSize.y + textSize.y;

	Printing::text(
		Printing::getInstance(),
		Utilities::toUppercase(strPrecautionTitle),
		__HALF_SCREEN_WIDTH_IN_CHARS - (titleSize.x >> 1),
		(__HALF_SCREEN_HEIGHT_IN_CHARS) - (totalHeight >> 1) - 1,
		NULL
	);

	Printing::text(
		Printing::getInstance(),
		Utilities::toUppercase(strPrecautionText),
		__HALF_SCREEN_WIDTH_IN_CHARS - (textSize.x >> 1),
		(__HALF_SCREEN_HEIGHT_IN_CHARS) - (totalHeight >> 1) + titleSize.y,
		NULL
	);
}
