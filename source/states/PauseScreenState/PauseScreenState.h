/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef PAUSE_SCREEN_STATE_H_
#define PAUSE_SCREEN_STATE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <GameState.h>
#include <OptionsSelector.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

enum PauseScreenModes
{
	kPauseScreenModeShowOptions,
	kPauseScreenModeShowConfirmQuit
};

enum PauseScreenOptions
{
	kPauseScreenOptionContinue,
	kPauseScreenOptionOptions,
	kPauseScreenOptionQuitLevel
};


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

singleton class PauseScreenState : GameState
{
	u8 mode;
	OptionsSelector optionsSelector;

	static PauseScreenState getInstance();
	override void enter(void* owner);
	override void exit(void* owner);
	override void processUserInput(UserInput userInput);
}


#endif
