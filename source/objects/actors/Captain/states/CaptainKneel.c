/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include "CaptainKneel.h"
#include "CaptainMoving.h"
#include "../Captain.h"

#include <PlatformerLevelState.h>
#include <MessageDispatcher.h>
#include <KeypadManager.h>
#include <debugUtilities.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void CaptainKneel::constructor()
{
	// construct base
	Base::constructor();
}

void CaptainKneel::destructor()
{
	// destroy base
	Base::destructor();
}

void CaptainKneel::enter(void* owner)
{
	// show animation
	Captain::playAnimation(owner, "KneelDown");

	KeypadManager::registerInput(KeypadManager::getInstance(), __KEY_RELEASED | __KEY_PRESSED);

	// manipulate captain's shape
	Captain::toggleShapes(owner, true);
}

void CaptainKneel::exit(void* owner)
{
	// manipulate captain's shape
	Captain::toggleShapes(owner, false);
}

void CaptainKneel::onKeyReleased(void* owner, const UserInput* userInput)
{
    if(K_LD & userInput->releasedKey)
    {
        Captain::standUp(owner);
    }
}

void CaptainKneel::onKeyPressed(void* owner, const UserInput* userInput)
{
	if((K_SEL|K_RD|K_RU|K_RL|K_RR|K_LT|K_RT) & userInput->pressedKey)
	{
		Captain::reload(owner);
	}
	else if(K_A & userInput->pressedKey)
	{
		Captain::jump(owner, true);
	}
	else if(K_B & userInput->pressedKey)
	{
		Captain::startShooting(owner);
	}
}

