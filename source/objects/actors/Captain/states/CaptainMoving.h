/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef CAPTAIN_MOVING_H_
#define CAPTAIN_MOVING_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <CaptainState.h>
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

enum CaptainMovingMessages
{
	 kDisallowJumpOnBouncing = kLastPlatformerMessage + 1,
};


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

singleton class CaptainMoving : CaptainState
{
	// flag to allow jump on bouncing
	bool bouncing;

	static CaptainMoving getInstance();
	override void enter(void* owner);
	override void execute(void* owner);
	override bool processMessage(void* owner, Telegram telegram);
	override void onKeyPressed(void* owner, const UserInput* userInput);
	override void onKeyReleased(void* owner, const UserInput* userInput);
}


#endif
