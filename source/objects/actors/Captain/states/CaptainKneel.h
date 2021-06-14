/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef CAPTAIN_KNEEL_H_
#define CAPTAIN_KNEEL_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <CaptainState.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

singleton class CaptainKneel : CaptainState
{
	static CaptainKneel getInstance();
	override void enter(void* owner);
	override void exit(void* owner);
	override void onKeyReleased(void* owner, const UserInput* userInput);
	override void onKeyPressed(void* owner, const UserInput* userInput);
}


#endif
