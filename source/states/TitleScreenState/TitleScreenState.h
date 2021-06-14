/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef TITLE_SCREEN_STATE_H_
#define TITLE_SCREEN_STATE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <GameState.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

singleton class TitleScreenState : GameState
{
	static TitleScreenState getInstance();
	override void enter(void* owner);
	override void exit(void* owner);
	override void resume(void* owner);
	override void suspend(void* owner);
	override void processUserInput(UserInput userInput);
}


#endif
