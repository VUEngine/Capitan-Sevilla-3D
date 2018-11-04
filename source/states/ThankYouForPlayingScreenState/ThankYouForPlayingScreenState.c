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
#include <ThankYouForPlayingScreenState.h>
#include <TitleScreenState.h>
#include <I18n.h>
#include <Languages.h>
#include <DirectDraw.h>
#include <PlatformerLevelState.h>
#include <ProgressManager.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef EMPTY_STAGE_ST;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void ThankYouForPlayingScreenState::constructor()
{
	Base::constructor();

	SplashScreenState::setNextState(SplashScreenState::safeCast(this), GameState::safeCast(TitleScreenState::getInstance()));
	this->stageDefinition = (StageDefinition*)&EMPTY_STAGE_ST;
}

// class's destructor
void ThankYouForPlayingScreenState::destructor()
{
	// destroy base
	Base::destructor();
}

// state's enter
void ThankYouForPlayingScreenState::enter(void* owner)
{
	// call base
	Base::enter(this, owner);

	// reset game progress for next round
	PlatformerLevelState::resetProgress(PlatformerLevelState::getInstance());
	ProgressManager::resetCurrentLevelProgress(ProgressManager::getInstance());

	// print "thank you for playing"
	const char* strPresents = I18n::getText(I18n::getInstance(), STR_THANK_YOU_FOR_PLAYING);
	FontSize strPresentsSize = Printing::getTextSize(Printing::getInstance(), strPresents, "DefaultFont");
	u8 strPresentsXPos = __HALF_SCREEN_WIDTH_IN_CHARS - (strPresentsSize.x >> 1);
	Printing::text(Printing::getInstance(), strPresents, strPresentsXPos, 14, "DefaultFont");
}
