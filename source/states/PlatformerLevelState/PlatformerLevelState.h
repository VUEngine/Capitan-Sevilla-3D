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

#ifndef PLATFORMER_LEVEL_STATE_H_
#define PLATFORMER_LEVEL_STATE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <GameState.h>
#include <KeyPadManager.h>



//---------------------------------------------------------------------------------------------------------
//												DEFINES
//---------------------------------------------------------------------------------------------------------

enum PlatformerLevelModes
{
	kPlaying = 1,
	kShowingUp,
	kPaused,
};


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define PlatformerLevelState_METHODS(ClassName)															\
		GameState_METHODS(ClassName)																	\

// declare the virtual methods which are redefined
#define PlatformerLevelState_SET_VTABLE(ClassName)														\
		GameState_SET_VTABLE(ClassName)																	\
		__VIRTUAL_SET(ClassName, PlatformerLevelState, enter);											\
		__VIRTUAL_SET(ClassName, PlatformerLevelState, exit);											\
		__VIRTUAL_SET(ClassName, PlatformerLevelState, suspend);										\
		__VIRTUAL_SET(ClassName, PlatformerLevelState, resume);											\
		__VIRTUAL_SET(ClassName, PlatformerLevelState, processMessage);									\
		__VIRTUAL_SET(ClassName, PlatformerLevelState, processUserInput);								\

__CLASS(PlatformerLevelState);

#define PlatformerLevelState_ATTRIBUTES																	\
		/* inherits */																					\
		GameState_ATTRIBUTES																			\
		/* the currently loaded level */																\
		PlatformerLevelDefinition* currentLevel;														\
		/* the currently loaded entry point */															\
		StageEntryPointDefinition* currentStageEntryPoint;												\
		/* the last reached checkpoint */																\
		StageEntryPointDefinition* currentCheckPoint;													\
		/* to allow moving the screen */																\
		u8 mode;																						\
		/* in-game clock */																				\
		Clock clock;																					\
		/* previous user input */																		\
		UserInput userInput;																			\


//---------------------------------------------------------------------------------------------------------
//											CLASS'S ROM DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef struct StageEntryPointDefinition
{
	// the stage to load
	StageDefinition* stageDefinition;

	// name of the entity to start at
	char* destinationName;

	// offset from entry point (x, y, z)
	ScreenPixelVector offset;

	// whether this entry point acts as a checkpoint
	bool isCheckPoint;

} StageEntryPointDefinition;

typedef const StageEntryPointDefinition StageEntryPointROMDef;


typedef struct PlatformerLevelDefinition
{
	// starting entry point
	StageEntryPointDefinition* entryPoint;

	// id
	u8 id;

	// identifier
	void* identifier;

	// name
	void* name;

	// slogan
	void* slogan;

} PlatformerLevelDefinition;

typedef const PlatformerLevelDefinition PlatformerLevelROMDef;


enum PlatformerLevelStateMessageTypes
{
	kLevelSetUp = kLastEngineMessage + 1,
	kLevelStarted,
	kLevelResumed,
	kHeroResumePhysics,
	kHeroCheckVelocity,
	kHideLevelMessage,
	kScreenFocused,
	kHeroFall,
	kHeroStopInvincibility,
	kHeroFlash,
	kHeroSleep,
	kItemTaken,
	kTakeKey,
	kTakeCoin,
	kTakeBandana,
	kRemoveFromStage,
	kLavaTriggerStart,
	kLavaTriggerEnd,
	kCogWheelMove,
	kCogWheelStop,
	kLavaMove,
	kIntroNextImage,
	kProjectileEject,
	kProjectileCheckPosition,
	kMovingEntityStartMoving,
	kMovingEntityCheckDirection,
	kLoadCheckPoint,
	kReactToCollision,
	kStopReactToCollision,

	// don't remove me
	kLastPlatformerMessage
};


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

PlatformerLevelState PlatformerLevelState_getInstance(void);

Clock PlatformerLevelState_getClock(PlatformerLevelState this);
PlatformerLevelDefinition* PlatformerLevelState_getCurrentLevelDefinition(PlatformerLevelState this);
void PlatformerLevelState_startLevel(PlatformerLevelState this, PlatformerLevelDefinition* platformerLevelDefinition);
void PlatformerLevelState_enterStage(PlatformerLevelState this, StageEntryPointDefinition* entryPointDefinition);
void PlatformerLevelState_setModeToPaused(PlatformerLevelState this);
void PlatformerLevelState_setModeToPlaying(PlatformerLevelState this);
UserInput PlatformerLevelState_getUserInput(PlatformerLevelState this);
void PlatformerLevelState_processUserInput(PlatformerLevelState this, UserInput userInput);


#endif
