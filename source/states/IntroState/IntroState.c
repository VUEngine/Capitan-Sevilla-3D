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
#include <IntroState.h>
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

extern StageROMDef INTRO_STAGE_ST;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void IntroState::constructor()
{
	Base::constructor();

	// init members
	this->currentStep = 0;
	this->entityImage1 = NULL;
	this->entityImage2 = NULL;
	this->entityImage3 = NULL;
	this->entityImage4 = NULL;
	this->entityImage5 = NULL;
	this->entityImage6 = NULL;
	this->entityImage7 = NULL;
	this->entityImage8 = NULL;
	this->entityText1 = NULL;
	this->entityText2 = NULL;
	this->entityText3 = NULL;
	this->entityText4 = NULL;
	this->entityText5 = NULL;
	this->entityText6 = NULL;
	this->entityText7 = NULL;
	this->entityText8 = NULL;
	this->entityText9 = NULL;
}

// class's destructor
void IntroState::destructor()
{
	// discard pending messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kIntroNextImage);

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// state's enter
void IntroState::enter(void* owner)
{
	// call base
	Base::enter(this, owner);

	// load stage
	GameState::loadStage(this, (StageDefinition*)&INTRO_STAGE_ST, NULL, true);

	// init members
	this->currentStep = 0;

	// get entity references
	this->entityImage1 = Entity::safeCast(Container::getChildByName(Game::getStage(Game::getInstance()), "IMAGE1", true));
	this->entityImage2 = Entity::safeCast(Container::getChildByName(Game::getStage(Game::getInstance()), "IMAGE2", true));
	this->entityImage3 = Entity::safeCast(Container::getChildByName(Game::getStage(Game::getInstance()), "IMAGE3", true));
	this->entityImage4 = Entity::safeCast(Container::getChildByName(Game::getStage(Game::getInstance()), "IMAGE4", true));
	this->entityImage5 = Entity::safeCast(Container::getChildByName(Game::getStage(Game::getInstance()), "IMAGE5", true));
	this->entityImage6 = Entity::safeCast(Container::getChildByName(Game::getStage(Game::getInstance()), "IMAGE6", true));
	this->entityImage7 = Entity::safeCast(Container::getChildByName(Game::getStage(Game::getInstance()), "IMAGE7", true));
	this->entityImage8 = Entity::safeCast(Container::getChildByName(Game::getStage(Game::getInstance()), "IMAGE8", true));
	this->entityText1 = Entity::safeCast(Container::getChildByName(Game::getStage(Game::getInstance()), "TEXT1", true));
	this->entityText2 = Entity::safeCast(Container::getChildByName(Game::getStage(Game::getInstance()), "TEXT2", true));
	this->entityText3 = Entity::safeCast(Container::getChildByName(Game::getStage(Game::getInstance()), "TEXT3", true));
	this->entityText4 = Entity::safeCast(Container::getChildByName(Game::getStage(Game::getInstance()), "TEXT4", true));
	this->entityText5 = Entity::safeCast(Container::getChildByName(Game::getStage(Game::getInstance()), "TEXT5", true));
	this->entityText6 = Entity::safeCast(Container::getChildByName(Game::getStage(Game::getInstance()), "TEXT6", true));
	this->entityText7 = Entity::safeCast(Container::getChildByName(Game::getStage(Game::getInstance()), "TEXT7", true));
	this->entityText8 = Entity::safeCast(Container::getChildByName(Game::getStage(Game::getInstance()), "TEXT8", true));
	this->entityText9 = Entity::safeCast(Container::getChildByName(Game::getStage(Game::getInstance()), "TEXT9", true));

	// hide most entities initially
	Entity::hide(this->entityImage2);
    Entity::hide(this->entityImage3);
    Entity::hide(this->entityImage4);
    Entity::hide(this->entityImage5);
    Entity::hide(this->entityImage6);
    Entity::hide(this->entityImage7);
    Entity::hide(this->entityImage8);
    Entity::hide(this->entityText1);
    Entity::hide(this->entityText2);
    Entity::hide(this->entityText3);
    Entity::hide(this->entityText4);
    Entity::hide(this->entityText5);
    Entity::hide(this->entityText6);
    Entity::hide(this->entityText7);
    Entity::hide(this->entityText8);
    Entity::hide(this->entityText9);

	// translate text boxes
	IntroState::translateTextEntities(this);

	// disable user input
	Game::disableKeypad(Game::getInstance());

	// start clocks to start animations
	GameState::startClocks(this);

	// send delayed message to self to trigger next image
	MessageDispatcher::dispatchMessage(INTRO_IMAGE_DURATION, Object::safeCast(this), Object::safeCast(this), kIntroNextImage, NULL);

	// fade in screen
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))IntroState::onFadeInComplete, // callback function
		Object::safeCast(this) // callback scope
	);
}

// state's exit
void IntroState::exit(void* owner)
{
	// call base
	Base::exit(this, owner);
}

// state's resume
void IntroState::resume(void* owner)
{
	Base::resume(this, owner);

	Camera::startEffect(Camera::getInstance(), kFadeIn, __FADE_DELAY);
}

// state's suspend
void IntroState::suspend(void* owner)
{
	Camera::startEffect(Camera::getInstance(), kFadeOut, __FADE_DELAY);

	Base::suspend(this, owner);
}

void IntroState::processUserInput(UserInput userInput)
{
	if(userInput.pressedKey & ~K_PWR)
	{
		if(userInput.pressedKey & K_SEL)
		{
			this->currentStep = 128;
		}

		IntroState::nextImageStep(this);
	}
}

bool IntroState::handleMessage(Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kIntroNextImage:

			IntroState::nextImageStep(this);
			break;
	}

	return false;
}

void IntroState::translateTextEntities()
{
	char* language = Utilities::itoa(I18n::getActiveLanguage(I18n::getInstance()), 10, 1);
	AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this->entityText1), language);
	AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this->entityText2), language);
	AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this->entityText3), language);
	AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this->entityText4), language);
	AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this->entityText5), language);
	AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this->entityText6), language);
	AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this->entityText7), language);
	AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this->entityText8), language);
	AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this->entityText9), language);
}

void IntroState::nextImageStep()
{
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kIntroNextImage);
	MessageDispatcher::dispatchMessage(INTRO_IMAGE_DURATION, Object::safeCast(this), Object::safeCast(this), kIntroNextImage, NULL);

	switch(this->currentStep++)
	{
		case 0:
			Entity::show(this->entityText1);
			break;
		case 1:
			Entity::show(this->entityImage2);
			break;
		case 2:
			Entity::show(this->entityText2);
			break;
		case 3:
			Entity::show(this->entityImage3);
			break;
		case 4:
			Entity::show(this->entityText3);
			break;
		case 5:
			Entity::show(this->entityImage4);
			break;
		case 6:
			Entity::show(this->entityText4);
			break;
		case 7:
			Entity::show(this->entityText5);
			break;
		case 8:
			Entity::hide(this->entityImage1);
			Entity::hide(this->entityText1);
			Entity::hide(this->entityImage2);
			Entity::hide(this->entityText2);
			Entity::hide(this->entityImage3);
			Entity::hide(this->entityText3);
			Entity::hide(this->entityImage4);
			Entity::hide(this->entityText4);
			Entity::hide(this->entityText5);
			Entity::show(this->entityImage5);
			break;
		case 9:
			Entity::show(this->entityText6);
			break;
		case 10:
			Entity::show(this->entityImage6);
			break;
		case 11:
			Entity::show(this->entityText7);
			break;
		case 12:
			Entity::show(this->entityImage7);
			break;
		case 13:
			Entity::show(this->entityText8);
			break;
		case 14:
			Entity::show(this->entityImage8);
			break;
		case 15:
			Entity::show(this->entityText9);
			break;
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
				(void (*)(Object, Object))IntroState::onFadeOutComplete, // callback function
				Object::safeCast(this) // callback scope
			);
		}
	}
}

// handle event
void IntroState::onFadeInComplete(Object eventFirer __attribute__ ((unused)))
{
	// enable user input
	Game::enableKeypad(Game::getInstance());
}

// handle event
void IntroState::onFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	Game::changeState(Game::getInstance(), GameState::safeCast(TitleScreenState::getInstance()));
}
