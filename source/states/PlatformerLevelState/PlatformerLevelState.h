/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef PLATFORMER_LEVEL_STATE_H_
#define PLATFORMER_LEVEL_STATE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <GameState.h>
#include <KeypadManager.h>


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
//											CLASS'S ROM DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef struct StageEntryPointSpec
{
	// the stage to load
	StageSpec* stageSpec;

	// starting position (x, y, z)
	Vector3D startingPosition;

	// facing direction of the captain
	int8 direction;

	// whether this entry point32 acts as a checkpoint
	bool isCheckPoint;

} StageEntryPointSpec;

typedef const StageEntryPointSpec StageEntryPointROMSpec;


typedef struct PlatformerLevelSpec
{
	// starting entry point
	StageEntryPointSpec* entryPoint;

	// id
	uint8 id;

	// name
	void* name;

} PlatformerLevelSpec;

typedef const PlatformerLevelSpec PlatformerLevelROMSpec;


enum PlatformerLevelStateMessageTypes
{
	kLevelSetUp = kMessageLastEngine + 1,
	kLevelStarted,
	kLevelResumed,
	kCaptainCheckVelocity,
	kScreenFocused,
	kCaptainFall,
	kCaptainStopInvincibility,
	kStopFlashing,
	kEntityFlash,
	kCaptainSleep,
	kItemTaken,
	kLiftActivate,
	kLiftStart,
	kRemoveFromStage,
	kComicMove,
	kIntroNextImage,
	kCreditsStart,
	kProjectileEject,
	kProjectileCheckPosition,
	kLoadCheckPoint,
    kGameEnterCollision,
    kGameExitCollision,

	// don't remove me
	kLastPlatformerMessage
};


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

singleton class PlatformerLevelState : GameState
{
	// the currently loaded level
	PlatformerLevelSpec* currentLevel;
	// the currently loaded entry point
	StageEntryPointSpec* currentStageEntryPoint;
	// the last reached checkpoint
	StageEntryPointSpec* currentCheckPoint;
	// to allow moving the screen
	uint8 mode;
	// in-game clock
	Clock clock;
	// previous user input
	UserInput userInput;

	static PlatformerLevelState getInstance();
	Clock getClock();
	PlatformerLevelSpec* getCurrentLevelSpec();
	void startLevel(PlatformerLevelSpec* platformerLevelSpec);
	void enterStage(StageEntryPointSpec* entryPointSpec);
	void setModeToPaused();
	void setModeToPlaying();
	void resetProgress();
	UserInput getUserInput(bool force);
	override void enter(void* owner);
	override void exit(void* owner);
	override void resume(void* owner);
	override void suspend(void* owner);
	override bool processMessage(void* owner, Telegram telegram);
	override void processUserInput(UserInput userInput);
}


#endif
