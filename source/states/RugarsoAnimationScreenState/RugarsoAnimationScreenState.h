/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef RUGARSO_ANIMATION_SCREEN_STATE_H_
#define RUGARSO_ANIMATION_SCREEN_STATE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <SplashScreenState.h>


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

singleton class RugarsoAnimationScreenState : SplashScreenState
{
	static RugarsoAnimationScreenState getInstance();
}


#endif
