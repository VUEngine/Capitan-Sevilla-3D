/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef INTRO_STATE_H_
#define INTRO_STATE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <GameState.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define INTRO_IMAGE_DURATION	1500


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

singleton class IntroState : GameState
{
	// image entity references
	Entity entityImage1;
	Entity entityImage2;
	Entity entityImage3;
	Entity entityImage4;
	Entity entityImage5;
	Entity entityImage6;
	Entity entityImage7;
	Entity entityImage8;
	// text entity references
	Entity entityText1;
	Entity entityText2;
	Entity entityText3;
	Entity entityText4;
	Entity entityText5;
	Entity entityText6;
	Entity entityText7;
	Entity entityText8;
	Entity entityText9;
	// current intro step
	u8 currentStep;

	static IntroState getInstance();
	void nextImageStep();
	override bool handleMessage(Telegram telegram);
	override void enter(void* owner);
	override void exit(void* owner);
	override void resume(void* owner);
	override void processUserInput(UserInput userInput);
}


#endif
