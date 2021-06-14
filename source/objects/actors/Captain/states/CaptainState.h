/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef CAPTAIN_STATE_H_
#define CAPTAIN_STATE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <State.h>
#include <KeypadManager.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

class CaptainState : State
{
	void constructor();
	virtual void onKeyHold(void* owner, const UserInput* userInput);
	virtual void onKeyPressed(void* owner, const UserInput* userInput);
	virtual void onKeyReleased(void* owner, const UserInput* userInput);
}


#endif
