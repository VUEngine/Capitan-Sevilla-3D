/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef CS_ADJUSTMENT_SCREEN_STATE_H_
#define CS_ADJUSTMENT_SCREEN_STATE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <SplashScreenState.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

dynamic_singleton class CsAdjustmentScreenState : SplashScreenState
{
	static CsAdjustmentScreenState getInstance(void);
	override void initNextState();
}


#endif
