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
#include <IntroState.h>
#include <Captain.h>
#include <ParticleSystem.h>
#include <PlatformerLevelState.h>
#include <OptionsScreenState.h>
#include <ProgressManager.h>
#include <EventManager.h>
#include <KeypadManager.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMSpec IntroStage;
extern PlatformerLevelSpec Level1;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

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

void IntroState::destructor()
{
	// discard pending messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kIntroNextImage);

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void IntroState::enter(void* owner)
{
	// call base
	Base::enter(this, owner);

	// load stage
	GameState::loadStage(this, (StageSpec*)&IntroStage, NULL, true, false);

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
	Camera::startEffect(Camera::getInstance(), kHide);
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		50, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))IntroState::onFadeInComplete, // callback function
		Object::safeCast(this) // callback scope
	);
}

void IntroState::exit(void* owner)
{
	Camera::startEffect(Camera::getInstance(), kHide);

	// call base
	Base::exit(this, owner);
}

void IntroState::resume(void* owner)
{
	Base::resume(this, owner);

	Camera::startEffect(Camera::getInstance(), kFadeIn, __FADE_DELAY);
}

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
	AnimatedEntity::playAnimation(this->entityText1, language);
	AnimatedEntity::playAnimation(this->entityText2, language);
	AnimatedEntity::playAnimation(this->entityText3, language);
	AnimatedEntity::playAnimation(this->entityText4, language);
	AnimatedEntity::playAnimation(this->entityText5, language);
	AnimatedEntity::playAnimation(this->entityText6, language);
	AnimatedEntity::playAnimation(this->entityText7, language);
	AnimatedEntity::playAnimation(this->entityText8, language);
	AnimatedEntity::playAnimation(this->entityText9, language);
}

void IntroState::nextImageStep()
{
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kIntroNextImage);

	switch(this->currentStep++)
	{
		case 0:
			MessageDispatcher::dispatchMessage(INTRO_IMAGE_DURATION, Object::safeCast(this), Object::safeCast(this), kIntroNextImage, NULL);
			Entity::show(this->entityText1);
			break;
		case 1:
			MessageDispatcher::dispatchMessage(INTRO_IMAGE_DURATION, Object::safeCast(this), Object::safeCast(this), kIntroNextImage, NULL);
			Entity::show(this->entityImage2);
			break;
		case 2:
			MessageDispatcher::dispatchMessage(INTRO_IMAGE_DURATION, Object::safeCast(this), Object::safeCast(this), kIntroNextImage, NULL);
			Entity::show(this->entityText2);
			break;
		case 3:
			MessageDispatcher::dispatchMessage(INTRO_IMAGE_DURATION, Object::safeCast(this), Object::safeCast(this), kIntroNextImage, NULL);
			Entity::show(this->entityImage3);
			break;
		case 4:
			MessageDispatcher::dispatchMessage(INTRO_IMAGE_DURATION, Object::safeCast(this), Object::safeCast(this), kIntroNextImage, NULL);
			Entity::show(this->entityText3);
			break;
		case 5:
			MessageDispatcher::dispatchMessage(INTRO_IMAGE_DURATION, Object::safeCast(this), Object::safeCast(this), kIntroNextImage, NULL);
			Entity::show(this->entityImage4);
			break;
		case 6:
			MessageDispatcher::dispatchMessage(INTRO_IMAGE_DURATION, Object::safeCast(this), Object::safeCast(this), kIntroNextImage, NULL);
			Entity::show(this->entityText4);
			break;
		case 7:
			Entity::show(this->entityText5);
			break;
		case 8:
			MessageDispatcher::dispatchMessage(INTRO_IMAGE_DURATION, Object::safeCast(this), Object::safeCast(this), kIntroNextImage, NULL);
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
			MessageDispatcher::dispatchMessage(INTRO_IMAGE_DURATION, Object::safeCast(this), Object::safeCast(this), kIntroNextImage, NULL);
			Entity::show(this->entityText6);
			break;
		case 10:
			MessageDispatcher::dispatchMessage(INTRO_IMAGE_DURATION, Object::safeCast(this), Object::safeCast(this), kIntroNextImage, NULL);
			Entity::show(this->entityImage6);
			break;
		case 11:
			MessageDispatcher::dispatchMessage(INTRO_IMAGE_DURATION, Object::safeCast(this), Object::safeCast(this), kIntroNextImage, NULL);
			Entity::show(this->entityText7);
			break;
		case 12:
			MessageDispatcher::dispatchMessage(INTRO_IMAGE_DURATION, Object::safeCast(this), Object::safeCast(this), kIntroNextImage, NULL);
			Entity::show(this->entityImage7);
			break;
		case 13:
			MessageDispatcher::dispatchMessage(INTRO_IMAGE_DURATION, Object::safeCast(this), Object::safeCast(this), kIntroNextImage, NULL);
			Entity::show(this->entityText8);
			break;
		case 14:
			MessageDispatcher::dispatchMessage(INTRO_IMAGE_DURATION, Object::safeCast(this), Object::safeCast(this), kIntroNextImage, NULL);
			Entity::show(this->entityImage8);
			break;
		case 15:
			Entity::show(this->entityText9);
			break;
		default:
		{
			Game::disableKeypad(Game::getInstance());

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

void IntroState::onFadeInComplete(Object eventFirer __attribute__ ((unused)))
{
	Game::enableKeypad(Game::getInstance());
}

void IntroState::onFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	PlatformerLevelState::startLevel(PlatformerLevelState::getInstance(), &Level1);
}
