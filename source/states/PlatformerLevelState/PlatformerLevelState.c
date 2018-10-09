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
#include <GameEvents.h>
#include <Game.h>
#include <Optics.h>
#include <Camera.h>
#include <MessageDispatcher.h>
#include <PhysicalWorld.h>
#include <I18n.h>
#include <PlatformerLevelState.h>
#include <AdjustmentScreenState.h>
#include <PauseScreenState.h>
#include <Hero.h>
#include <Languages.h>
#include <ProgressManager.h>
#include <CustomCameraMovementManager.h>
#include <CustomCameraEffectManager.h>
#include <EventManager.h>
#include <KeyPadManager.h>
#include <debugUtilities.h>


//---------------------------------------------------------------------------------------------------------
//											DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern PlatformerLevelDefinition LEVEL_1_LV;
extern EntityDefinition HERO_AC;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void PlatformerLevelState::constructor()
{
	Base::constructor();

	// clock
	this->clock = new Clock();

	// set default entry point
	this->currentLevel = (PlatformerLevelDefinition*)&LEVEL_1_LV;
	this->currentStageEntryPoint = this->currentLevel->entryPoint;
	this->currentCheckPoint = this->currentLevel->entryPoint;
	this->userInput = (UserInput){0, 0, 0, 0, 0, 0, 0};
}

// class's destructor
void PlatformerLevelState::destructor()
{
	delete this->clock;

	// destroy base
	__SINGLETON_DESTROY;
}

void PlatformerLevelState::getPositionedEntitiesToIgnore(VirtualList positionedEntitiesToIgnore __attribute__ ((unused)))
{
}

// state's enter
void PlatformerLevelState::enter(void* owner)
{
	// call base
	Base::enter(this, owner);

	// set the custom screen managers
	Camera::setCameraMovementManager(Camera::getInstance(), CameraMovementManager::safeCast(CustomCameraMovementManager::getInstance()));
	Camera::setCameraEffectManager(Camera::getInstance(), CameraEffectManager::safeCast(CustomCameraEffectManager::getInstance()));

	// disable user input
	Game::disableKeypad(Game::getInstance());

	// get list of entities that should not be loaded
	VirtualList positionedEntitiesToIgnore = new VirtualList();
	PlatformerLevelState::getPositionedEntitiesToIgnore(this, positionedEntitiesToIgnore);

	Vector3D* initialPosition = (Vector3D*)&this->currentStageEntryPoint->startingPosition;

	if(initialPosition)
	{
		// set world's limits
		Camera::setStageSize(Camera::getInstance(), Size::getFromPixelSize(this->currentStageEntryPoint->stageDefinition->level.pixelSize));

		// focus screen on new position
		Vector3D screenPosition =
		{
			initialPosition->x - __PIXELS_TO_METERS(__HALF_SCREEN_WIDTH),
			initialPosition->y - __PIXELS_TO_METERS(__HALF_SCREEN_HEIGHT),
			__PIXELS_TO_METERS(this->currentStageEntryPoint->stageDefinition->level.cameraInitialPosition.z)
		};

		Camera::setPosition(Camera::getInstance(), screenPosition);

		// load stage
		GameState::loadStage(GameState::safeCast(this), this->currentStageEntryPoint->stageDefinition, positionedEntitiesToIgnore, false);

		// create hero
		PositionedEntity positionedEntity =
		{
			&HERO_AC,
			{
				initialPosition->x,
				initialPosition->y,
				initialPosition->z,
				0
			},
			0,
			NULL,
			NULL,
			NULL,
			false
		};

		Hero hero = Hero::safeCast(Stage::addChildEntity(this->stage, &positionedEntity, true));

		Object::addEventListener(hero, Object::safeCast(this), (EventListener)PlatformerLevelState::onHeroStreamedOut, kStageChildStreamedOut);

		// make sure that focusing gets completed immediately
		CustomCameraMovementManager::enable(CustomCameraMovementManager::getInstance());
		CustomCameraMovementManager::disableFocusEasing(CustomCameraMovementManager::getInstance());

		// update actor's global transformations
		GameState::transform(GameState::safeCast(this));

		// set focus on the hero
		Camera::setFocusGameEntity(Camera::getInstance(), Entity::safeCast(hero));
		Vector3D screenDisplacement = {__PIXELS_TO_METERS(50), __PIXELS_TO_METERS(-30), 0};
		Camera::setFocusEntityPositionDisplacement(Camera::getInstance(), screenDisplacement);

		// apply changes to the visuals
		GameState::synchronizeGraphics(GameState::safeCast(this));
	}
	else
	{
		// load stage
		GameState::loadStage(GameState::safeCast(this), this->currentStageEntryPoint->stageDefinition, positionedEntitiesToIgnore, true);
	}

	CustomCameraMovementManager::disable(CustomCameraMovementManager::getInstance());

	// free some memory
	delete positionedEntitiesToIgnore;

	// level is paused
	PlatformerLevelState::setModeToPaused(this);

	// show up level after a little delay
	MessageDispatcher::dispatchMessage(200, Object::safeCast(this), Object::safeCast(Game::getInstance()), kLevelSetUp, NULL);

	// start clocks
	Clock::start(this->clock);
	Clock::setTimeInMilliSeconds(this->clock, ProgressManager::getCurrentLevelTime(ProgressManager::getInstance()));
	GameState::startClocks(GameState::safeCast(this));

	// register event listeners
	Object::addEventListener(EventManager::getInstance(), Object::safeCast(this), (EventListener)PlatformerLevelState::onHeroDied, kEventHeroDied);

	// activate pulsating effect in indoor stages
	if(this->currentStageEntryPoint->stageDefinition->rendering.colorConfig.brightnessRepeat != NULL)
	{
		Camera::startEffect(Camera::getInstance(), kScreenPulsate);
	}
}

// state's exit
void PlatformerLevelState::exit(void* owner)
{
	Object::removeEventListener(EventManager::getInstance(), Object::safeCast(this), (EventListener)PlatformerLevelState::onHeroDied, kEventHeroDied);

	// call base
	Base::exit(this, owner);
}

void PlatformerLevelState::suspend(void* owner)
{
	// set pause mode
	PlatformerLevelState::setModeToPaused(this);

	// pause clocks
	Clock::pause(this->messagingClock, true);
	Clock::pause(this->clock, true);

	// pause physical simulations
	GameState::pausePhysics(GameState::safeCast(this), true);

#ifdef __DEBUG_TOOLS
	if(!Game::isExitingSpecialMode(Game::getInstance()))
	{
#endif
#ifdef __STAGE_EDITOR
	if(!Game::isExitingSpecialMode(Game::getInstance()))
	{
#endif
#ifdef __ANIMATION_INSPECTOR
	if(!Game::isExitingSpecialMode(Game::getInstance()))
	{
#endif

	// do a fade out effect
	Camera::startEffect(Camera::getInstance(), kFadeOut, __FADE_DELAY);

#ifdef __DEBUG_TOOLS
	}
#endif
#ifdef __STAGE_EDITOR
	}
#endif
#ifdef __ANIMATION_INSPECTOR
	}
#endif

	// call base
	Base::suspend(this, owner);
}

void PlatformerLevelState::resume(void* owner)
{
	// resume in-game clock
	Clock::pause(this->messagingClock, false);
	Clock::pause(this->clock, false);

	// call base
	Base::resume(this, owner);

#ifdef __DEBUG_TOOLS
	if(!Game::isExitingSpecialMode(Game::getInstance()))
	{
#endif
#ifdef __STAGE_EDITOR
	if(!Game::isExitingSpecialMode(Game::getInstance()))
	{
#endif
#ifdef __ANIMATION_INSPECTOR
	if(!Game::isExitingSpecialMode(Game::getInstance()))
	{
#endif

	// tell any interested entity
	GameState::propagateMessage(GameState::safeCast(this), kLevelResumed);

	// start a fade in effect
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		NULL, // callback function
		NULL // callback scope
	);

#ifdef __DEBUG_TOOLS
	}
#endif
#ifdef __STAGE_EDITOR
	}
#endif
#ifdef __ANIMATION_INSPECTOR
	}
#endif

	// pause physical simulations
	GameState::pausePhysics(GameState::safeCast(this), false);

	PlatformerLevelState::setModeToPlaying(this);

	UserInput userInput = KeypadManager::getUserInput(KeypadManager::getInstance());

	this->userInput.pressedKey 	= userInput.allKeys & ~this->userInput.previousKey;
	this->userInput.releasedKey = ~userInput.allKeys & this->userInput.previousKey;
	this->userInput.holdKey 	= userInput.allKeys & this->userInput.previousKey;

	// make sure that user input is taken into account
	Object::fireEvent(this, kEventUserInput);

	PlatformerLevelState::setPrintingLayerCoordinates(this);
}

void PlatformerLevelState::setPrintingLayerCoordinates()
{
	extern TextureROMDef GUI_TX;
	Printing::setWorldCoordinates(Printing::getInstance(), __PRINTING_BGMAP_X_OFFSET, __SCREEN_HEIGHT - GUI_TX.rows * 8);
}

UserInput PlatformerLevelState::getUserInput(bool force)
{
	if((kPlaying == this->mode) || force)
	{
		return this->userInput;
	}
	else
	{
		// jorgeche: MEMORY LEAK!
		//UserInput* userInput = new UserInput;
		//return *userInput;

		return (UserInput){0, 0, 0, 0, 0, 0, 0};
	}
}

void PlatformerLevelState::processUserInput(UserInput userInput)
{
	this->userInput = userInput;

	if(kPlaying == this->mode)
	{
		if(this->userInput.pressedKey)
		{
			if(K_SEL & this->userInput.pressedKey)
			{
				// adjustment screen
				PlatformerLevelState::setModeToPaused(this);

				// set next state of adjustment screen state to null so it can differentiate between
				// being called the splash screen sequence or from within the game (a bit hacky...)
				SplashScreenState::setNextState(SplashScreenState::safeCast(AdjustmentScreenState::getInstance()), NULL);

				// pause game and switch to adjustment screen state
				Game::pause(Game::getInstance(), GameState::safeCast(AdjustmentScreenState::getInstance()));

				return;
			}
			else if(K_STA & this->userInput.pressedKey)
			{
				// pause game and switch to pause screen state
				Game::pause(Game::getInstance(), GameState::safeCast(PauseScreenState::getInstance()));

				return;
			}
		}

	}

	Object::fireEvent(this, kEventUserInput);
}

// state's handle message
bool PlatformerLevelState::processMessage(void* owner __attribute__ ((unused)), Telegram telegram)
{
	// process message
	switch(Telegram::getMessage(telegram))
	{
		case kLevelSetUp:
			{
				if(this->currentStageEntryPoint->isCheckPoint)
				{
					// write checkpoint message to screen
					// TODO
				}

				// tell any interested entity
				GameState::propagateMessage(GameState::safeCast(this), kLevelSetUp);

				// show level after a little delay
				MessageDispatcher::dispatchMessage(200, Object::safeCast(this), Object::safeCast(Game::getInstance()), kLevelStarted, NULL);

				this->mode = kShowingUp;
			}
			break;

		case kLevelStarted:

			// fade in screen
			Camera::startEffect(Camera::getInstance(),
				kFadeTo, // effect type
				0, // initial delay (in ms)
				NULL, // target brightness
				__FADE_DELAY, // delay between fading steps (in ms)
				(void (*)(Object, Object))PlatformerLevelState::onLevelStartedFadeInComplete, // callback function
				Object::safeCast(this) // callback scope
			);

			break;

		case kScreenFocused:

			Object::removeEventListener(EventManager::getInstance(), Object::safeCast(this), (EventListener)PlatformerLevelState::onScreenFocused, kEventScreenFocused);
			break;

		case kLoadCheckPoint:

			PlatformerLevelState::startStage(this, this->currentCheckPoint);

			// announce checkpoint loaded
			Object::fireEvent(EventManager::getInstance(), kEventCheckpointLoaded);
			break;
	}

	return false;
}

void PlatformerLevelState::onScreenFocused(Object eventFirer __attribute__ ((unused)))
{
	MessageDispatcher::dispatchMessage(1, Object::safeCast(this), Object::safeCast(Game::getInstance()), kScreenFocused, NULL);

	CustomCameraMovementManager::dontAlertWhenTargetFocused(CustomCameraMovementManager::getInstance());

	Game::enableKeypad(Game::getInstance());
}

void PlatformerLevelState::onHeroDied(Object eventFirer __attribute__ ((unused)))
{
	// start a fade out effect
	Brightness brightness = (Brightness){0, 0, 0};
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		5000, // initial delay (in ms)
		&brightness, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))PlatformerLevelState::onHeroDiedFadeOutComplete, // callback function
		Object::safeCast(this) // callback scope
	);

	Game::disableKeypad(Game::getInstance());
}

void PlatformerLevelState::onHeroStreamedOut(Object eventFirer __attribute__ ((unused)))
{
	PlatformerLevelState::setModeToPaused(this);
}

// get in-game clock
Clock PlatformerLevelState::getClock()
{
	return this->clock;
}

// get current level's definition
PlatformerLevelDefinition* PlatformerLevelState::getCurrentLevelDefinition()
{
	return this->currentLevel;
}

// start a given level
void PlatformerLevelState::startLevel(PlatformerLevelDefinition* platformerLevelDefinition)
{
	this->currentLevel = platformerLevelDefinition;
	this->currentCheckPoint = this->currentStageEntryPoint = this->currentLevel->entryPoint;

	Game::changeState(Game::getInstance(), GameState::safeCast(this));
}

// enter a given stage
void PlatformerLevelState::enterStage(StageEntryPointDefinition* entryPointDefinition)
{
	// save stats if is checkpoint
	if(entryPointDefinition->isCheckPoint)
	{
		// write checkpoint stats
		ProgressManager::setCheckPointData(ProgressManager::getInstance());

		// set current checkpoint
		this->currentCheckPoint = entryPointDefinition;
	}

	PlatformerLevelState::startStage(this, entryPointDefinition);
}

// start a given stage
void PlatformerLevelState::startStage(StageEntryPointDefinition* entryPointDefinition)
{
	// set current entry point
	this->currentStageEntryPoint = entryPointDefinition;

	// disable user input
	Game::disableKeypad(Game::getInstance());

	// pause physical simulations
	GameState::pausePhysics(GameState::safeCast(this), true);

	// start a fade out effect
	Brightness brightness = (Brightness){0, 0, 0};
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		&brightness, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))PlatformerLevelState::onStartStageFadeOutComplete, // callback function
		Object::safeCast(this) // callback scope
	);
}

// determine if starting a new level
bool PlatformerLevelState::isStartingLevel()
{
	return (this->currentStageEntryPoint == this->currentLevel->entryPoint);
}

// set paused mode
void PlatformerLevelState::setModeToPaused()
{
	this->mode = kPaused;

	Object::fireEvent(EventManager::getInstance(), kEventSetModeToPaused);
}

// set playing mode
void PlatformerLevelState::setModeToPlaying()
{
	this->mode = kPlaying;

	Object::fireEvent(EventManager::getInstance(), kEventSetModeToPlaying);
}

// handle event
void PlatformerLevelState::onLevelStartedFadeInComplete(Object eventFirer __attribute__ ((unused)))
{
	PlatformerLevelState::setModeToPlaying(this);

	// enable focus easing
	Object::addEventListener(EventManager::getInstance(), Object::safeCast(this), (EventListener)PlatformerLevelState::onScreenFocused, kEventScreenFocused);
	CustomCameraMovementManager::enableFocusEasing(CustomCameraMovementManager::getInstance());
	CustomCameraMovementManager::enable(CustomCameraMovementManager::getInstance());
	CustomCameraMovementManager::alertWhenTargetFocused(CustomCameraMovementManager::getInstance());

	// tell any interested entity
	GameState::propagateMessage(GameState::safeCast(this), kLevelStarted);

	// announce level start
	Object::fireEvent(EventManager::getInstance(), kEventLevelStarted);
}

// handle event
void PlatformerLevelState::onStartStageFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	Game::changeState(Game::getInstance(), GameState::safeCast(this));
}

// handle event
void PlatformerLevelState::onHeroDiedFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	MessageDispatcher::dispatchMessage(1, Object::safeCast(this), Object::safeCast(Game::getInstance()), kLoadCheckPoint, NULL);
}
