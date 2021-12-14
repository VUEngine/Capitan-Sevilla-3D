/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
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
#include <Captain.h>
#include <ParticleSystem.h>
#include <TitleScreenState.h>
#include <OptionsScreenState.h>
#include <ProgressManager.h>
#include <EventManager.h>
#include <KeypadManager.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMSpec CreditsStage;


//---------------------------------------------------------------------------------------------------------
//												GLOBALS
//---------------------------------------------------------------------------------------------------------

static Camera _camera = NULL;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void CreditsState::constructor()
{
	Base::constructor();

	this->cameraTranslation.x = 0;
	this->cameraTranslation.y = 0;
	this->cameraTranslation.z = 0;
	this->totalScrolled = 0;
	this->finishedScrolling = true;

	_camera = Camera::getInstance();
}

void CreditsState::destructor()
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void CreditsState::enter(void* owner)
{
	// call base
	Base::enter(this, owner);

	// load stage
	GameState::loadStage(this, (StageSpec*)&CreditsStage, NULL, true, false);

	// disable user input
	Game::disableKeypad(Game::getInstance());

	// start clocks to start animations
	GameState::startClocks(this);

	// scrolling state
	CreditsState::scrollSlow(this);
	this->totalScrolled = 0;
	this->finishedScrolling = true;

	// fade in screen
	Camera::startEffect(Camera::getInstance(), kHide);
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
	if(userInput.pressedKey & (K_A|K_B|K_STA|K_SEL))
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
	else if(userInput.holdKey & (K_LD|K_RD))
	{
		if(!this->finishedScrolling)
		{
			CreditsState::scrollFast(this);
		}
	}
	else if(userInput.releasedKey & (K_LD|K_RD))
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
		Camera::move(_camera, this->cameraTranslation, false);
		this->totalScrolled += this->cameraTranslation.y;

    	if(this->totalScrolled > 6450)
    	{
    		this->finishedScrolling = true;
    	}
	}
}

void CreditsState::startScroll()
{
	this->finishedScrolling = false;
}

void CreditsState::scrollSlow()
{
	this->cameraTranslation.y = 2;
}

void CreditsState::scrollFast()
{
	this->cameraTranslation.y = 8;
}

bool CreditsState::handleMessage(Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kCreditsStart:

			CreditsState::startScroll(this);
			break;
	}

	return false;
}

void CreditsState::onFadeInComplete(Object eventFirer __attribute__ ((unused)))
{
	Game::enableKeypad(Game::getInstance());
	CreditsState::scrollSlow(this);
	MessageDispatcher::dispatchMessage(CREDITS_INITIAL_DELAY, Object::safeCast(this), Object::safeCast(this), kCreditsStart, NULL);
}

void CreditsState::onFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	Game::changeState(Game::getInstance(), GameState::safeCast(TitleScreenState::getInstance()));
}
