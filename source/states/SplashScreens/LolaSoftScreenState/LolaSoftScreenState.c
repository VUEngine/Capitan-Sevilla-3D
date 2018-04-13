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
#include <LolaSoftScreenState.h>
#include <IntroState.h>
#include <I18n.h>
#include <Utilities.h>
#include <Languages.h>
#include <DirectDraw.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef LOLA_SOFT_SCREEN_STAGE_ST;


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void LolaSoftScreenState_destructor(LolaSoftScreenState this);
static void LolaSoftScreenState_constructor(LolaSoftScreenState this);


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(LolaSoftScreenState, SplashScreenState);
__SINGLETON_DYNAMIC(LolaSoftScreenState);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void __attribute__ ((noinline)) LolaSoftScreenState_constructor(LolaSoftScreenState this)
{
	__CONSTRUCT_BASE(SplashScreenState);

	SplashScreenState_setNextState(__SAFE_CAST(SplashScreenState, this), __SAFE_CAST(GameState, IntroState_getInstance()));
	this->stageDefinition = (StageDefinition*)&LOLA_SOFT_SCREEN_STAGE_ST;
}

// class's destructor
static void LolaSoftScreenState_destructor(LolaSoftScreenState this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
void LolaSoftScreenState_enter(LolaSoftScreenState this, void* owner)
{
	// call base
	__CALL_BASE_METHOD(SplashScreenState, enter, this, owner);

	// print "presents"
	const char* strPresents = I18n_getText(I18n_getInstance(), STR_PRESENTS);
	FontSize strPresentsSize = Printing_getTextSize(Printing_getInstance(), strPresents, NULL);
	u8 strPresentsXPos = __HALF_SCREEN_WIDTH_IN_CHARS - (strPresentsSize.x >> 1);
	Printing_text(Printing_getInstance(), Utilities_toUppercase(strPresents), strPresentsXPos, 18, NULL);
}
