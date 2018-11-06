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
#include <Languages.h>
#include <PhysicalWorld.h>
#include <TitleScreenState.h>
#include <Hero.h>
#include <ParticleSystem.h>
#include <IntroState.h>
#include <OptionsScreenState.h>
#include <ProgressManager.h>
#include <EventManager.h>
#include <KeyPadManager.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef TITLE_SCREEN_STAGE_ST;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void TitleScreenState::constructor()
{
	Base::constructor();
}

// class's destructor
void TitleScreenState::destructor()
{
	// destroy base
	Base::destructor();
}

// state's enter
void TitleScreenState::enter(void* owner)
{
	// call base
	Base::enter(this, owner);

	// disable user input
	Game::disableKeypad(Game::getInstance());

	// start clocks to start animations
	GameState::startClocks(this);

	// load stage
	GameState::loadStage(this, (StageDefinition*)&TITLE_SCREEN_STAGE_ST, NULL, true);

	// fade in screen
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))TitleScreenState::onFadeInComplete, // callback function
		Object::safeCast(this) // callback scope
	);
}

// state's exit
void TitleScreenState::exit(void* owner)
{
	// call base
	Base::exit(this, owner);
}

// state's resume
void TitleScreenState::resume(void* owner)
{
	Base::resume(this, owner);

	Camera::startEffect(Camera::getInstance(), kFadeIn, __FADE_DELAY);
}

// state's suspend
void TitleScreenState::suspend(void* owner)
{
	Camera::startEffect(Camera::getInstance(), kFadeOut, __FADE_DELAY);

	Base::suspend(this, owner);
}

void TitleScreenState::processUserInput(UserInput userInput)
{
	if(userInput.pressedKey & ~K_PWR)
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
			(void (*)(Object, Object))TitleScreenState::onFadeOutComplete, // callback function
			Object::safeCast(this) // callback scope
		);
	}
}

// handle event
void TitleScreenState::onFadeInComplete(Object eventFirer __attribute__ ((unused)))
{
	// enable user input
	Game::enableKeypad(Game::getInstance());
}

// handle event
void TitleScreenState::onFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	Game::changeState(Game::getInstance(), GameState::safeCast(IntroState::getInstance()));
}
