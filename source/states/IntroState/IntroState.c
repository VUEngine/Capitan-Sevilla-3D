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
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void IntroState_destructor(IntroState this);
static void IntroState_constructor(IntroState this);
static void IntroState_enter(IntroState this, void* owner);
static void IntroState_exit(IntroState this, void* owner);
static void IntroState_resume(IntroState this, void* owner);
static void IntroState_suspend(IntroState this, void* owner);
static void IntroState_onFadeInComplete(IntroState this, Object eventFirer);
static void IntroState_onFadeOutComplete(IntroState this, Object eventFirer);
void IntroState_translateTextEntities(IntroState this);


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(IntroState, GameState);
__SINGLETON(IntroState);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void __attribute__ ((noinline)) IntroState_constructor(IntroState this)
{
	__CONSTRUCT_BASE(GameState);

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
static void IntroState_destructor(IntroState this)
{
	// discard pending messages
	MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kIntroNextImage);

	// delete the super object
	// must always be called at the end of the destructor
	__SINGLETON_DESTROY;
}

// state's enter
static void IntroState_enter(IntroState this, void* owner)
{
	// call base
	__CALL_BASE_METHOD(GameState, enter, this, owner);

	// load stage
	GameState_loadStage(__SAFE_CAST(GameState, this), (StageDefinition*)&INTRO_STAGE_ST, NULL, true);

	// init members
	this->currentStep = 0;

	// get entity references
	this->entityImage1 = __SAFE_CAST(Entity, Container_getChildByName(__SAFE_CAST(Container, Game_getStage(Game_getInstance())), "IMAGE1", true));
	this->entityImage2 = __SAFE_CAST(Entity, Container_getChildByName(__SAFE_CAST(Container, Game_getStage(Game_getInstance())), "IMAGE2", true));
	this->entityImage3 = __SAFE_CAST(Entity, Container_getChildByName(__SAFE_CAST(Container, Game_getStage(Game_getInstance())), "IMAGE3", true));
	this->entityImage4 = __SAFE_CAST(Entity, Container_getChildByName(__SAFE_CAST(Container, Game_getStage(Game_getInstance())), "IMAGE4", true));
	this->entityImage5 = __SAFE_CAST(Entity, Container_getChildByName(__SAFE_CAST(Container, Game_getStage(Game_getInstance())), "IMAGE5", true));
	this->entityImage6 = __SAFE_CAST(Entity, Container_getChildByName(__SAFE_CAST(Container, Game_getStage(Game_getInstance())), "IMAGE6", true));
	this->entityImage7 = __SAFE_CAST(Entity, Container_getChildByName(__SAFE_CAST(Container, Game_getStage(Game_getInstance())), "IMAGE7", true));
	this->entityImage8 = __SAFE_CAST(Entity, Container_getChildByName(__SAFE_CAST(Container, Game_getStage(Game_getInstance())), "IMAGE8", true));
	this->entityText1 = __SAFE_CAST(Entity, Container_getChildByName(__SAFE_CAST(Container, Game_getStage(Game_getInstance())), "TEXT1", true));
	this->entityText2 = __SAFE_CAST(Entity, Container_getChildByName(__SAFE_CAST(Container, Game_getStage(Game_getInstance())), "TEXT2", true));
	this->entityText3 = __SAFE_CAST(Entity, Container_getChildByName(__SAFE_CAST(Container, Game_getStage(Game_getInstance())), "TEXT3", true));
	this->entityText4 = __SAFE_CAST(Entity, Container_getChildByName(__SAFE_CAST(Container, Game_getStage(Game_getInstance())), "TEXT4", true));
	this->entityText5 = __SAFE_CAST(Entity, Container_getChildByName(__SAFE_CAST(Container, Game_getStage(Game_getInstance())), "TEXT5", true));
	this->entityText6 = __SAFE_CAST(Entity, Container_getChildByName(__SAFE_CAST(Container, Game_getStage(Game_getInstance())), "TEXT6", true));
	this->entityText7 = __SAFE_CAST(Entity, Container_getChildByName(__SAFE_CAST(Container, Game_getStage(Game_getInstance())), "TEXT7", true));
	this->entityText8 = __SAFE_CAST(Entity, Container_getChildByName(__SAFE_CAST(Container, Game_getStage(Game_getInstance())), "TEXT8", true));
	this->entityText9 = __SAFE_CAST(Entity, Container_getChildByName(__SAFE_CAST(Container, Game_getStage(Game_getInstance())), "TEXT9", true));

	// hide most entities initially
	Entity_hide(this->entityImage2);
    Entity_hide(this->entityImage3);
    Entity_hide(this->entityImage4);
    Entity_hide(this->entityImage5);
    Entity_hide(this->entityImage6);
    Entity_hide(this->entityImage7);
    Entity_hide(this->entityImage8);
    Entity_hide(this->entityText1);
    Entity_hide(this->entityText2);
    Entity_hide(this->entityText3);
    Entity_hide(this->entityText4);
    Entity_hide(this->entityText5);
    Entity_hide(this->entityText6);
    Entity_hide(this->entityText7);
    Entity_hide(this->entityText8);
    Entity_hide(this->entityText9);

	// translate text boxes
	IntroState_translateTextEntities(this);

	// disable user input
	Game_disableKeypad(Game_getInstance());

	// send delayed message to self to trigger next image
	MessageDispatcher_dispatchMessage(INTRO_IMAGE_DURATION, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kIntroNextImage, NULL);

	// fade in screen
	Camera_startEffect(Camera_getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))IntroState_onFadeInComplete, // callback function
		__SAFE_CAST(Object, this) // callback scope
	);
}

// state's exit
static void IntroState_exit(IntroState this, void* owner)
{
	// call base
	__CALL_BASE_METHOD(GameState, exit, this, owner);
}

// state's resume
static void IntroState_resume(IntroState this, void* owner)
{
	__CALL_BASE_METHOD(GameState, resume, this, owner);

	Camera_startEffect(Camera_getInstance(), kFadeIn, __FADE_DELAY);
}

// state's suspend
static void IntroState_suspend(IntroState this, void* owner)
{
	Camera_startEffect(Camera_getInstance(), kFadeOut, __FADE_DELAY);

	__CALL_BASE_METHOD(GameState, suspend, this, owner);
}

void IntroState_processUserInput(IntroState this, UserInput userInput)
{
	if(userInput.pressedKey & ~K_PWR)
	{
		if(userInput.pressedKey & K_SEL)
		{
			this->currentStep = 128;
		}

		IntroState_nextImageStep(this);
	}
}

bool IntroState_handleMessage(IntroState this, Telegram telegram)
{
	ASSERT(this, "IntroState::handleMessage: null this");

	switch(Telegram_getMessage(telegram))
	{
		case kIntroNextImage:

			IntroState_nextImageStep(this);
			break;
	}

	return false;
}

void IntroState_translateTextEntities(IntroState this)
{
	char* language = Utilities_itoa(I18n_getActiveLanguage(I18n_getInstance()), 10, 1);
	AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this->entityText1), language);
	AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this->entityText2), language);
	AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this->entityText3), language);
	AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this->entityText4), language);
	AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this->entityText5), language);
	AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this->entityText6), language);
	AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this->entityText7), language);
	AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this->entityText8), language);
	AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this->entityText9), language);
}

void IntroState_nextImageStep(IntroState this)
{
	ASSERT(this, "IntroState::handleImageStep: null this");

	MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kIntroNextImage);
	MessageDispatcher_dispatchMessage(INTRO_IMAGE_DURATION, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kIntroNextImage, NULL);

	switch(this->currentStep++)
	{
		case 0:
			Entity_show(this->entityText1);
			break;
		case 1:
			Entity_show(this->entityImage2);
			break;
		case 2:
			Entity_show(this->entityText2);
			break;
		case 3:
			Entity_show(this->entityImage3);
			break;
		case 4:
			Entity_show(this->entityText3);
			break;
		case 5:
			Entity_show(this->entityImage4);
			break;
		case 6:
			Entity_show(this->entityText4);
			break;
		case 7:
			Entity_show(this->entityText5);
			break;
		case 8:
			Entity_hide(this->entityImage1);
			Entity_hide(this->entityText1);
			Entity_hide(this->entityImage2);
			Entity_hide(this->entityText2);
			Entity_hide(this->entityImage3);
			Entity_hide(this->entityText3);
			Entity_hide(this->entityImage4);
			Entity_hide(this->entityText4);
			Entity_hide(this->entityText5);
			Entity_show(this->entityImage5);
			break;
		case 9:
			Entity_show(this->entityText6);
			break;
		case 10:
			Entity_show(this->entityImage6);
			break;
		case 11:
			Entity_show(this->entityText7);
			break;
		case 12:
			Entity_show(this->entityImage7);
			break;
		case 13:
			Entity_show(this->entityText8);
			break;
		case 14:
			Entity_show(this->entityImage8);
			break;
		case 15:
			Entity_show(this->entityText9);
			break;
		default:
		{
			// disable user input
			Game_disableKeypad(Game_getInstance());

			// fade out screen
			Brightness brightness = (Brightness){0, 0, 0};
			Camera_startEffect(Camera_getInstance(),
				kFadeTo, // effect type
				0, // initial delay (in ms)
				&brightness, // target brightness
				__FADE_DELAY, // delay between fading steps (in ms)
				(void (*)(Object, Object))IntroState_onFadeOutComplete, // callback function
				__SAFE_CAST(Object, this) // callback scope
			);
		}
	}
}

// handle event
static void IntroState_onFadeInComplete(IntroState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "IntroState::onFadeInComplete: null this");

	// enable user input
	Game_enableKeypad(Game_getInstance());
}

// handle event
static void IntroState_onFadeOutComplete(IntroState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "IntroState::onFadeOutComplete: null this");

	Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, TitleScreenState_getInstance()));
}
