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

#include <Game.h>
#include <Camera.h>
#include <MessageDispatcher.h>
#include <RugarsoAnimationScreenState.h>
#include <TitleScreenState.h>
#include <I18n.h>
#include <Languages.h>
#include <DirectDraw.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMSpec RUGARSO_ANIMATION_SCREEN_STAGE_ST;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void RugarsoAnimationScreenState::constructor()
{
	Base::constructor();

	SplashScreenState::setNextState(SplashScreenState::safeCast(this), GameState::safeCast(TitleScreenState::getInstance()));
	this->stageSpec = (StageSpec*)&RUGARSO_ANIMATION_SCREEN_STAGE_ST;
}

void RugarsoAnimationScreenState::destructor()
{
	// destroy base
	Base::destructor();
}
