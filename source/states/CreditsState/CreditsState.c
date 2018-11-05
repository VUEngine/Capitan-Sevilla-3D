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

extern StageROMDef EMPTY_STAGE_ST;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void CreditsState::constructor()
{
	Base::constructor();

	// init members
	this->currentStep = 0;
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
	GameState::loadStage(GameState::safeCast(this), (StageDefinition*)&EMPTY_STAGE_ST, NULL, true);

	// init members
	this->currentStep = 0;

	// disable user input
	Game::disableKeypad(Game::getInstance());

	// print first screen
	CreditsState::print(this);

	// fade in screen
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
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
		this->currentStep = 99;
		CreditsState::print(this);
	}
	else if(userInput.pressedKey & K_A)
	{
		this->currentStep++;
		CreditsState::print(this);
	}
}

void CreditsState::print()
{
	Printing printing = Printing::getInstance();
	Printing::clear(printing);

	switch(this->currentStep)
	{
		case 0:
		{
			Printing::text(printing, __CHAR_A_BUTTON, 45, 1, "DefaultFont");
			Printing::text(printing, __CHAR_ARROW_RIGHT, 46, 1, "DefaultFont");

			Printing::text(printing, "--- CAPITAN SEVILLA 3D ---", 11, 3, "DefaultFont");
			Printing::text(printing, "BASED ON DINAMIC SOFTWARE'S \"CAPITAN SEVILLA\"", 2, 6, "DefaultFont");
			Printing::text(printing, "(1988) FOR ZX SPECTRUM.", 12, 7, "DefaultFont");
			Printing::text(printing, "- ARTWORK & DESIGN -", 14, 9, "DefaultFont");
			Printing::text(printing, "RUBÉN GARCERA SOTO", 15, 10, "DefaultFont");
			break;
		}
		case 1:
		{
			Printing::text(printing, __CHAR_A_BUTTON, 45, 1, "DefaultFont");
			Printing::text(printing, __CHAR_ARROW_RIGHT, 46, 1, "DefaultFont");
			break;
		}
		case 2:
		{
			Printing::text(printing, __CHAR_A_BUTTON, 45, 1, "DefaultFont");
			Printing::text(printing, __CHAR_ARROW_RIGHT, 46, 1, "DefaultFont");
			break;
		}
		default:
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
	}
}

// handle event
void CreditsState::onFadeInComplete(Object eventFirer __attribute__ ((unused)))
{
	// enable user input
	Game::enableKeypad(Game::getInstance());
}

// handle event
void CreditsState::onFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	Game::changeState(Game::getInstance(), GameState::safeCast(TitleScreenState::getInstance()));
}

/*
DEVELOPMENT:

CHRISTIAN RADKE
JORGE EREMIEV


THANK YOU:

A HUGE THANK YOU TO OUR BACKERS ON PATREON
HTTPS://WWW.PATREON.COM/VUENGINE

BENJAMIN STEVENS
BNJMN MRPH
ERIC FREEMAN
KEVIN L MELLOTT
PATRICK FENTON
RANDY JEFFERY

ADAM EMMONS
ADAM NELSON
AMOS BIELER
ANDRES GAETAN
BERNARDO COMPAGNONI
BRAXTON MOTT
BRIE HEBERT
CANDI'S CLASSIC GAME SHRINE
CESAR HENZELIN
CHRIS
DANIEL LHOTA
DAVE SHELDON
DAVID BAISLEY
DAVID GREEN
ECKART SAUERBREY
ERIC LUKE
GRAHAM DAWES
JESSE LEVINE
JON ZROSTLIK
JORDAN CARRIERE
JOSE ZAGAL
LARRY ANDERSON
MARTEN REISS
MICHAEL ORTEGA
MIKE BOODLE
NEKTARIOS MOULIANAKIS
NORTY
SEAN MACHAN
STEVEN HAGELGANS
TERO PIIROINEN
TONY
VECTREXROLI
*/