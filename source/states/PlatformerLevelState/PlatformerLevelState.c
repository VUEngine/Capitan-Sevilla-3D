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
#include <Utilities.h>
#include <PostProcessingEffects.h>
#include <debugUtilities.h>


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void PlatformerLevelState_constructor(PlatformerLevelState this);
static void PlatformerLevelState_destructor(PlatformerLevelState this);
static void PlatformerLevelState_enter(PlatformerLevelState this, void* owner);
static void PlatformerLevelState_exit(PlatformerLevelState this, void* owner);
static void PlatformerLevelState_suspend(PlatformerLevelState this, void* owner);
static void PlatformerLevelState_resume(PlatformerLevelState this, void* owner);
static bool PlatformerLevelState_processMessage(PlatformerLevelState this, void* owner, Telegram telegram);
static void PlatformerLevelState_getPositionedEntitiesToIgnore(PlatformerLevelState this, VirtualList positionedEntitiesToIgnore);
bool PlatformerLevelState_isStartingLevel(PlatformerLevelState this);
void PlatformerLevelState_setModeToPaused(PlatformerLevelState this);
void PlatformerLevelState_setModeToPlaying(PlatformerLevelState this);
void PlatformerLevelState_onScreenFocused(PlatformerLevelState this, Object eventFirer);
void PlatformerLevelState_onHeroDied(PlatformerLevelState this, Object eventFirer);
static void PlatformerLevelState_onLevelStartedFadeInComplete(PlatformerLevelState this, Object eventFirer);
static void PlatformerLevelState_onStartStageFadeOutComplete(PlatformerLevelState this, Object eventFirer);
static void PlatformerLevelState_onHeroDiedFadeOutComplete(PlatformerLevelState this, Object eventFirer);
static void PlatformerLevelState_onHeroStreamedOut(PlatformerLevelState this, Object eventFirer __attribute__ ((unused)));
void PlatformerLevelState_setPrintingLayerCoordinates(PlatformerLevelState this);
void PlatformerLevelState_startStage(PlatformerLevelState this, StageEntryPointDefinition* entryPointDefinition);


//---------------------------------------------------------------------------------------------------------
//											DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern PlatformerLevelDefinition LEVEL_1_LV;
extern EntityDefinition HERO_AC;


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(PlatformerLevelState, GameState);
__SINGLETON(PlatformerLevelState);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void __attribute__ ((noinline)) PlatformerLevelState_constructor(PlatformerLevelState this)
{
	__CONSTRUCT_BASE(GameState);

	// clock
	this->clock = __NEW(Clock);

	// set default entry point
	this->currentLevel = (PlatformerLevelDefinition*)&LEVEL_1_LV;
	this->currentStageEntryPoint = this->currentLevel->entryPoint;
	this->currentCheckPoint = this->currentLevel->entryPoint;
	this->userInput = (UserInput){0, 0, 0, 0, 0, 0, 0};
}

// class's destructor
static void PlatformerLevelState_destructor(PlatformerLevelState this)
{
	__DELETE(this->clock);

	// destroy base
	__SINGLETON_DESTROY;
}

static void PlatformerLevelState_getPositionedEntitiesToIgnore(PlatformerLevelState this __attribute__ ((unused)), VirtualList positionedEntitiesToIgnore __attribute__ ((unused)))
{
	ASSERT(this, "PlatformerLevelState::getPositionedEntitiesToIgnore: null this");
	ASSERT(positionedEntitiesToIgnore, "PlatformerLevelState::getPositionedEntitiesToIgnore: null positionedEntitiesToIgnore");
}

// state's enter
static void PlatformerLevelState_enter(PlatformerLevelState this, void* owner)
{
	// call base
	__CALL_BASE_METHOD(GameState, enter, this, owner);

	// set the custom screen managers
	Camera_setCameraMovementManager(Camera_getInstance(), __SAFE_CAST(CameraMovementManager, CustomCameraMovementManager_getInstance()));
	Camera_setCameraEffectManager(Camera_getInstance(), __SAFE_CAST(CameraEffectManager, CustomCameraEffectManager_getInstance()));

	// disable user input
	Game_disableKeypad(Game_getInstance());

	// get list of entities that should not be loaded
	VirtualList positionedEntitiesToIgnore = __NEW(VirtualList);
	PlatformerLevelState_getPositionedEntitiesToIgnore(this, positionedEntitiesToIgnore);

	// check if destination entity name is given
	if(this->currentStageEntryPoint->destinationName)
	{
		// iterate stage definition to find global position of destination entity
		Vector3D environmentPosition = {0, 0, 0};
		Vector3D* initialPosition = Entity_calculateGlobalPositionFromDefinitionByName(this->currentStageEntryPoint->stageDefinition->entities.children, environmentPosition, this->currentStageEntryPoint->destinationName);

//		ASSERT(initialPosition, "PlatormerLevelState::enter: no initial position");

		// if global position of destination entity could be found, move the hero and the screen there
		if(initialPosition)
		{
			// apply entry point offset
			initialPosition->x += __PIXELS_TO_METERS(this->currentStageEntryPoint->offset.x);
			initialPosition->y += __PIXELS_TO_METERS(this->currentStageEntryPoint->offset.y);
			initialPosition->z += __PIXELS_TO_METERS(this->currentStageEntryPoint->offset.z + this->currentStageEntryPoint->offset.zDisplacement);

			// set world's limits
			Camera_setStageSize(Camera_getInstance(), Size_getFromPixelSize(this->currentStageEntryPoint->stageDefinition->level.pixelSize));

			// focus screen on new position
			Vector3D screenPosition =
			{
				initialPosition->x - __PIXELS_TO_METERS(__HALF_SCREEN_WIDTH),
				initialPosition->y - __PIXELS_TO_METERS(__HALF_SCREEN_HEIGHT),
				__PIXELS_TO_METERS(this->currentStageEntryPoint->stageDefinition->level.cameraInitialPosition.z)
			};

			Camera_setPosition(Camera_getInstance(), screenPosition);

			// load stage
			GameState_loadStage(__SAFE_CAST(GameState, this), this->currentStageEntryPoint->stageDefinition, positionedEntitiesToIgnore, false);

			// get hero entity
			Container hero = Container_getChildByName(__SAFE_CAST(Container, this->stage), HERO_NAME, true);

			// if no hero could be found, create one. otherwise, move found hero.
			if(!hero)
			{
				PositionedEntity positionedEntity =
				{
					&HERO_AC,
					{
						__METERS_TO_PIXELS(initialPosition->x),
						__METERS_TO_PIXELS(initialPosition->y),
						__METERS_TO_PIXELS(initialPosition->z),
						0
					},
					0,
					HERO_NAME,
					NULL,
					NULL,
					false
				};

				hero = __SAFE_CAST(Container, Stage_addChildEntity(this->stage, &positionedEntity, true));

				// make sure that the streaming doesn't load the hero again
				Stage_registerEntityId(this->stage, Entity_getInternalId(__SAFE_CAST(Entity, hero)), &HERO_AC);
			}

			// set hero's position
			Actor_setPosition(__SAFE_CAST(Actor, hero), initialPosition);

			Object_addEventListener(__SAFE_CAST(Object, hero), __SAFE_CAST(Object, this), (EventListener)PlatformerLevelState_onHeroStreamedOut, kStageChildStreamedOut);

			// make sure that focusing gets completed immediately
			CustomCameraMovementManager_enable(CustomCameraMovementManager_getInstance());
			CustomCameraMovementManager_disableFocusEasing(CustomCameraMovementManager_getInstance());

			// update actor's global transformations
			GameState_transform(__SAFE_CAST(GameState, this));

			// set focus on the hero
			Camera_setFocusGameEntity(Camera_getInstance(), __SAFE_CAST(Entity, hero));
			Vector3D screenDisplacement = {__PIXELS_TO_METERS(50), __PIXELS_TO_METERS(-30), 0};
			Camera_setFocusEntityPositionDisplacement(Camera_getInstance(), screenDisplacement);

			// apply changes to the visuals
			GameState_synchronizeGraphics(__SAFE_CAST(GameState, this));
		}
		else
		{
			// load stage
			GameState_loadStage(__SAFE_CAST(GameState, this), this->currentStageEntryPoint->stageDefinition, positionedEntitiesToIgnore, true);
		}
	}
	else
	{
		// load stage
		GameState_loadStage(__SAFE_CAST(GameState, this), this->currentStageEntryPoint->stageDefinition, positionedEntitiesToIgnore, true);
	}

	CustomCameraMovementManager_disable(CustomCameraMovementManager_getInstance());

	// free some memory
	__DELETE(positionedEntitiesToIgnore);

	// level is paused
	PlatformerLevelState_setModeToPaused(this);

	// show up level after a little delay
	MessageDispatcher_dispatchMessage(200, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game_getInstance()), kLevelSetUp, NULL);

	// start clocks
	Clock_start(this->clock);
	Clock_setTimeInMilliSeconds(this->clock, ProgressManager_getCurrentLevelTime(ProgressManager_getInstance()));
	GameState_startClocks(__SAFE_CAST(GameState, this));

	// register event listeners
	Object_addEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)PlatformerLevelState_onHeroDied, kEventHeroDied);

	// activate pulsating effect in indoor stages
	if(this->currentStageEntryPoint->stageDefinition->rendering.colorConfig.brightnessRepeat != NULL)
	{
		Camera_startEffect(Camera_getInstance(), kScreenPulsate);
	}
}

// state's exit
static void PlatformerLevelState_exit(PlatformerLevelState this, void* owner)
{
	Object_removeEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)PlatformerLevelState_onHeroDied, kEventHeroDied);

	// call base
	__CALL_BASE_METHOD(GameState, exit, this, owner);
}

static void PlatformerLevelState_suspend(PlatformerLevelState this, void* owner)
{
	// set pause mode
	PlatformerLevelState_setModeToPaused(this);

	// pause clocks
	Clock_pause(this->messagingClock, true);
	Clock_pause(this->clock, true);

	// pause physical simulations
	GameState_pausePhysics(__SAFE_CAST(GameState, this), true);

#ifdef __DEBUG_TOOLS
	if(!Game_isExitingSpecialMode(Game_getInstance()))
	{
#endif
#ifdef __STAGE_EDITOR
	if(!Game_isExitingSpecialMode(Game_getInstance()))
	{
#endif
#ifdef __ANIMATION_INSPECTOR
	if(!Game_isExitingSpecialMode(Game_getInstance()))
	{
#endif

	// do a fade out effect
	Camera_startEffect(Camera_getInstance(), kFadeOut, __FADE_DELAY);

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
	__CALL_BASE_METHOD(GameState, suspend, this, owner);
}

static void PlatformerLevelState_resume(PlatformerLevelState this, void* owner)
{
	// resume in-game clock
	Clock_pause(this->messagingClock, false);
	Clock_pause(this->clock, false);

	// call base
	__CALL_BASE_METHOD(GameState, resume, this, owner);

#ifdef __DEBUG_TOOLS
	if(!Game_isExitingSpecialMode(Game_getInstance()))
	{
#endif
#ifdef __STAGE_EDITOR
	if(!Game_isExitingSpecialMode(Game_getInstance()))
	{
#endif
#ifdef __ANIMATION_INSPECTOR
	if(!Game_isExitingSpecialMode(Game_getInstance()))
	{
#endif

	// tell any interested entity
	GameState_propagateMessage(__SAFE_CAST(GameState, this), kLevelResumed);

	// start a fade in effect
	Camera_startEffect(Camera_getInstance(),
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
	GameState_pausePhysics(__SAFE_CAST(GameState, this), false);

	PlatformerLevelState_setModeToPlaying(this);

	UserInput userInput = KeypadManager_getUserInput(KeypadManager_getInstance());

	this->userInput.pressedKey 	= userInput.allKeys & ~this->userInput.previousKey;
	this->userInput.releasedKey = ~userInput.allKeys & this->userInput.previousKey;
	this->userInput.holdKey 	= userInput.allKeys & this->userInput.previousKey;

	// make sure that user input is taken into account
	Object_fireEvent(__SAFE_CAST(Object, this), kEventUserInput);

	PlatformerLevelState_setPrintingLayerCoordinates(this);
}

void PlatformerLevelState_setPrintingLayerCoordinates(PlatformerLevelState this __attribute__ ((unused)))
{
	extern TextureROMDef GUI_TX;
	Printing_setWorldCoordinates(Printing_getInstance(), __PRINTING_BGMAP_X_OFFSET, __SCREEN_HEIGHT - GUI_TX.rows * 8);
}

UserInput PlatformerLevelState_getUserInput(PlatformerLevelState this)
{
	return this->userInput;
}

void PlatformerLevelState_processUserInput(PlatformerLevelState this, UserInput userInput)
{
	if(kPlaying == this->mode)
	{
		this->userInput = userInput;

		if(this->userInput.pressedKey)
		{
			if(K_SEL & this->userInput.pressedKey)
			{
				// adjustment screen
				PlatformerLevelState_setModeToPaused(this);

				// set next state of adjustment screen state to null so it can differentiate between
				// being called the splash screen sequence or from within the game (a bit hacky...)
				SplashScreenState_setNextState(__SAFE_CAST(SplashScreenState, AdjustmentScreenState_getInstance()), NULL);

				// pause game and switch to adjustment screen state
				Game_pause(Game_getInstance(), __SAFE_CAST(GameState, AdjustmentScreenState_getInstance()));

				return;
			}
			else if(K_STA & this->userInput.pressedKey)
			{
				// pause game and switch to pause screen state
				Game_pause(Game_getInstance(), __SAFE_CAST(GameState, PauseScreenState_getInstance()));

				return;
			}
		}

		Object_fireEvent(__SAFE_CAST(Object, this), kEventUserInput);
	}
}

// state's handle message
static bool PlatformerLevelState_processMessage(PlatformerLevelState this, void* owner __attribute__ ((unused)), Telegram telegram)
{
	// process message
	switch(Telegram_getMessage(telegram))
	{
		case kLevelSetUp:
			{
				// print level name if at level start point
				if(PlatformerLevelState_isStartingLevel(this) && this->currentLevel->name)
				{
					const char* strLevelName = I18n_getText(I18n_getInstance(), (int)this->currentLevel->name);
					Printing_text(
						Printing_getInstance(),
						strLevelName,
						((__SCREEN_WIDTH_IN_CHARS) - strlen(strLevelName)) >> 1,
						6,
						"GuiFont"
					);

					if(this->currentLevel->identifier)
					{
						const char* strLevel = I18n_getText(I18n_getInstance(), STR_LEVEL);
						const char* strLevelId = this->currentLevel->identifier;
						u8 strLevelLength = strlen(strLevel);
						u8 strLevelIdLength = strlen(strLevelId);
						Printing_text(
							Printing_getInstance(),
							strLevel,
							((__SCREEN_WIDTH_IN_CHARS) - strLevelLength - strLevelIdLength) >> 1,
							4,
							NULL
						);
						Printing_text(
							Printing_getInstance(),
							strLevelId,
							(((__SCREEN_WIDTH_IN_CHARS) - strLevelLength - strLevelIdLength) >> 1) + strLevelLength + 1,
							4,
							NULL
						);
					}

					if(this->currentLevel->slogan)
					{
						const char* strLevelSlogan = I18n_getText(I18n_getInstance(), (int)this->currentLevel->slogan);
						FontSize strLevelSloganSize = Printing_getTextSize(Printing_getInstance(), strLevelSlogan, NULL);
						Printing_text(
							Printing_getInstance(),
							strLevelSlogan,
							((__SCREEN_WIDTH_IN_CHARS) - strLevelSloganSize.x) >> 1,
							9,
							NULL
						);
					}

					// erase level message in 2 seconds
					MessageDispatcher_dispatchMessage(2000, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game_getInstance()), kHideLevelMessage, NULL);
				}
				else if(this->currentStageEntryPoint->isCheckPoint)
				{
					// write checkpoint message to screen
					const char* strCheckpoint = I18n_getText(I18n_getInstance(), STR_CHECKPOINT);
					Printing_text(
						Printing_getInstance(),
						strCheckpoint,
						((__SCREEN_WIDTH_IN_CHARS) - strlen(strCheckpoint)) >> 1,
						6,
						NULL
					);

					// erase checkpoint message in 2 second
					MessageDispatcher_dispatchMessage(2000, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game_getInstance()), kHideLevelMessage, NULL);
				}

				// tell any interested entity
				GameState_propagateMessage(__SAFE_CAST(GameState, this), kLevelSetUp);

				// show level after a little delay
				MessageDispatcher_dispatchMessage(200, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game_getInstance()), kLevelStarted, NULL);

				this->mode = kShowingUp;
			}
			break;

		case kLevelStarted:

			// fade in screen
			Camera_startEffect(Camera_getInstance(),
				kFadeTo, // effect type
				0, // initial delay (in ms)
				NULL, // target brightness
				__FADE_DELAY, // delay between fading steps (in ms)
				(void (*)(Object, Object))PlatformerLevelState_onLevelStartedFadeInComplete, // callback function
				__SAFE_CAST(Object, this) // callback scope
			);

			break;

		case kHideLevelMessage:

			Printing_text(Printing_getInstance(), "                                                ", 0, 5, NULL);
			Printing_text(Printing_getInstance(), "                                                ", 0, 6, NULL);
			Printing_text(Printing_getInstance(), "                                                ", 0, 7, NULL);

			PlatformerLevelState_setPrintingLayerCoordinates(this);
			break;

		case kScreenFocused:

			Object_removeEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)PlatformerLevelState_onScreenFocused, kEventScreenFocused);
			break;

		case kLoadCheckPoint:

			PlatformerLevelState_startStage(this, this->currentCheckPoint);

			// announce checkpoint loaded
			Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), kEventCheckpointLoaded);
			break;
	}

	return false;
}

void PlatformerLevelState_onScreenFocused(PlatformerLevelState this, Object eventFirer __attribute__ ((unused)))
{
	MessageDispatcher_dispatchMessage(1, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game_getInstance()), kScreenFocused, NULL);

	CustomCameraMovementManager_dontAlertWhenTargetFocused(CustomCameraMovementManager_getInstance());

	Game_enableKeypad(Game_getInstance());
}

void PlatformerLevelState_onHeroDied(PlatformerLevelState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
/*
	// unset the hero as focus entity from the custom screen movement manager
	Camera_setFocusGameEntity(Camera_getInstance(), NULL);

	// start a fade out effect
	Brightness brightness = (Brightness){0, 0, 0};
	Camera_startEffect(Camera_getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		&brightness, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))PlatformerLevelState_onHeroDiedFadeOutComplete, // callback function
		__SAFE_CAST(Object, this) // callback scope
	);

	Game_disableKeypad(Game_getInstance());
*/
}

static void PlatformerLevelState_onHeroStreamedOut(PlatformerLevelState this, Object eventFirer __attribute__ ((unused)))
{
	PlatformerLevelState_setModeToPaused(this);
}

// get in-game clock
Clock PlatformerLevelState_getClock(PlatformerLevelState this)
{
	return this->clock;
}

// get current level's definition
PlatformerLevelDefinition* PlatformerLevelState_getCurrentLevelDefinition(PlatformerLevelState this)
{
	return this->currentLevel;
}

// start a given level
void PlatformerLevelState_startLevel(PlatformerLevelState this, PlatformerLevelDefinition* platformerLevelDefinition)
{
	this->currentLevel = platformerLevelDefinition;
	this->currentCheckPoint = this->currentStageEntryPoint = this->currentLevel->entryPoint;

	// announce level start
	Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), kEventLevelStarted);

	Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, this));
}

// enter a given stage
void PlatformerLevelState_enterStage(PlatformerLevelState this, StageEntryPointDefinition* entryPointDefinition)
{
	// save stats if is checkpoint
	if(entryPointDefinition->isCheckPoint)
	{
		// write checkpoint stats
		ProgressManager_setCheckPointData(ProgressManager_getInstance());

		// set current checkpoint
		this->currentCheckPoint = entryPointDefinition;
	}

	PlatformerLevelState_startStage(this, entryPointDefinition);
}

// start a given stage
void PlatformerLevelState_startStage(PlatformerLevelState this, StageEntryPointDefinition* entryPointDefinition)
{
	// set current entry point
	this->currentStageEntryPoint = entryPointDefinition;

	// disable user input
	Game_disableKeypad(Game_getInstance());

	// pause physical simulations
	GameState_pausePhysics(__SAFE_CAST(GameState, this), true);

	// start a fade out effect
	Brightness brightness = (Brightness){0, 0, 0};
	Camera_startEffect(Camera_getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		&brightness, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))PlatformerLevelState_onStartStageFadeOutComplete, // callback function
		__SAFE_CAST(Object, this) // callback scope
	);
}

// determine if starting a new level
bool PlatformerLevelState_isStartingLevel(PlatformerLevelState this)
{
	return (this->currentStageEntryPoint == this->currentLevel->entryPoint);
}

// set paused mode
void PlatformerLevelState_setModeToPaused(PlatformerLevelState this)
{
	this->mode = kPaused;
}

// set playing mode
void PlatformerLevelState_setModeToPlaying(PlatformerLevelState this)
{
	this->mode = kPlaying;
}

// handle event
static void PlatformerLevelState_onLevelStartedFadeInComplete(PlatformerLevelState this, Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "PlatformerLevelState::onLevelStartedFadeInComplete: null this");

	// tell any interested entity
	GameState_propagateMessage(__SAFE_CAST(GameState, this), kLevelStarted);

	PlatformerLevelState_setModeToPlaying(this);

	// enable focus easing
	Object_addEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)PlatformerLevelState_onScreenFocused, kEventScreenFocused);
	CustomCameraMovementManager_enableFocusEasing(CustomCameraMovementManager_getInstance());
	CustomCameraMovementManager_enable(CustomCameraMovementManager_getInstance());
	CustomCameraMovementManager_alertWhenTargetFocused(CustomCameraMovementManager_getInstance());
}

// handle event
static void PlatformerLevelState_onStartStageFadeOutComplete(PlatformerLevelState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "PlatformerLevelState::onEnterStageFadeOutComplete: null this");

	Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, this));
}

// handle event
static void PlatformerLevelState_onHeroDiedFadeOutComplete(PlatformerLevelState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "PlatformerLevelState::onHeroDiedFadeOutComplete: null this");

	MessageDispatcher_dispatchMessage(1, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game_getInstance()), kLoadCheckPoint, NULL);
}
