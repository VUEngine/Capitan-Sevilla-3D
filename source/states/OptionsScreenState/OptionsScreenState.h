/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef OPTIONS_SCREEN_STATE_H_
#define OPTIONS_SCREEN_STATE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <GameState.h>
#include <OptionsSelector.h>


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

singleton class OptionsScreenState : GameState
{
	GameState nextState;
	OptionsSelector optionsSelector;

	static OptionsScreenState getInstance();
	void setNextState(GameState nextState);
	override void enter(void* owner);
	override void exit(void* owner);
	override void processUserInput(UserInput userInput);
}


#endif
