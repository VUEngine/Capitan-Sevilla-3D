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
#include <Utilities.h>
#include <CreditsState.h>
#include <Hero.h>
#include <ParticleSystem.h>
#include <TitleScreenState.h>
#include <OptionsScreenState.h>
#include <ProgressManager.h>
#include <EventManager.h>
#include <KeyPadManager.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef CREDITS_STAGE_ST;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void CreditsState::constructor()
{
	Base::constructor();

	this->entityCredits = NULL;
	this->finishedScrolling = false;
}

// class's destructor
void CreditsState::destructor()
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// state's enter
void CreditsState::enter(void* owner)
{
	// call base
	Base::enter(this, owner);

	// load stage
	GameState::loadStage(this, (StageDefinition*)&CREDITS_STAGE_ST, NULL, true);

	// get entity reference
	this->entityCredits = Actor::safeCast(Container::getChildByName(Game::getStage(Game::getInstance()), "CREDITS", true));

	// disable user input
	Game::disableKeypad(Game::getInstance());

	// start clocks to start animations
	GameState::startClocks(this);

	// scrolling state
	this->finishedScrolling = false;

	// fade in screen
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		1500, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))CreditsState::onFadeInComplete, // callback function
		Object::safeCast(this) // callback scope
	);
}

void CreditsState::processUserInput(UserInput userInput)
{
	if(userInput.pressedKey & K_B)
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
			(void (*)(Object, Object))CreditsState::onFadeOutComplete, // callback function
			Object::safeCast(this) // callback scope
		);
	}
	else if(userInput.holdKey & (K_LD|K_RD|K_A))
	{
		if(!this->finishedScrolling)
		{
			CreditsState::scrollFast(this);
		}
	}
	else if(userInput.releasedKey & (K_LD|K_RD|K_A))
	{
		if(!this->finishedScrolling)
		{
			CreditsState::scrollSlow(this);
		}
	}
}

void CreditsState::execute(void* owner __attribute__ ((unused)))
{
	if(!this->finishedScrolling)
	{
		const Vector3D* position = Actor::getPosition(this->entityCredits);

    	if(__METERS_TO_PIXELS(position->y) < -720)
    	{
    		Actor::stopAllMovement(this->entityCredits);
    		this->finishedScrolling = true;
    	}
	}
}

void CreditsState::scrollSlow()
{
	Velocity velocity = {0, __I_TO_FIX10_6(-1), 0};
	Actor::moveUniformly(this->entityCredits, &velocity);
}

void CreditsState::scrollFast()
{
	Velocity velocity = {0, __I_TO_FIX10_6(-3), 0};
	Actor::moveUniformly(this->entityCredits, &velocity);
}

void CreditsState::onFadeInComplete(Object eventFirer __attribute__ ((unused)))
{
	// enable user input
	Game::enableKeypad(Game::getInstance());

	// start scrolling credits
	CreditsState::scrollSlow(this);
}

// handle event
void CreditsState::onFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	Game::changeState(Game::getInstance(), GameState::safeCast(TitleScreenState::getInstance()));
}
