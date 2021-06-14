/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef CAPTAIN_IDLE_H_
#define CAPTAIN_IDLE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <CaptainState.h>


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

singleton class CaptainIdle : CaptainState
{
	static CaptainIdle getInstance();
	override void enter(void* owner);
	override void exit(void* owner);
	override bool processMessage(void* owner, Telegram telegram);
	override void onKeyPressed(void* owner, const UserInput* userInput);
	override void onKeyHold(void* owner, const UserInput* userInput);
}


#endif
