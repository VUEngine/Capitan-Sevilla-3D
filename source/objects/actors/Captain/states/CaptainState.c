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

#include "CaptainState.h"
#include <VirtualList.h>
#include <Entity.h>
#include <Shape.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void CaptainState::constructor()
{
	// construct base
	Base::constructor();
}

void CaptainState::destructor()
{
	// destroy base
	Base::destructor();
}

void CaptainState::onKeyHold(void* owner __attribute__ ((unused)), const UserInput* userInput __attribute__ ((unused)))
{
}

void CaptainState::onKeyPressed(void* owner __attribute__ ((unused)), const UserInput* userInput __attribute__ ((unused)))
{
}

void CaptainState::onKeyReleased(void* owner __attribute__ ((unused)), const UserInput* userInput __attribute__ ((unused)))
{
}
