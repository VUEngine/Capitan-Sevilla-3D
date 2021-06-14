/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef CREDITS_STATE_H_
#define CREDITS_STATE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <GameState.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define CREDITS_INITIAL_DELAY	800


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

singleton class CreditsState : GameState
{
	Vector3D cameraTranslation;
	bool finishedScrolling;
	u16 totalScrolled;

	static CreditsState getInstance();
	override void enter(void* owner);
	override void execute(void* owner);
	override bool handleMessage(Telegram telegram);
	override void processUserInput(UserInput userInput);
}


#endif
