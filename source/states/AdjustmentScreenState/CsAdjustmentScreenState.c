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
#include <CsAdjustmentScreenState.h>
#include <AutoPauseSelectScreenState.h>
#include <DirectDraw.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMSpec CS_ADJUSTMENT_SCREEN_STAGE;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void CsAdjustmentScreenState::constructor()
{
	Base::constructor();

	this->stageSpec = (StageSpec*)&CS_ADJUSTMENT_SCREEN_STAGE;
}

// class's destructor
void CsAdjustmentScreenState::destructor()
{
	// destroy base
	Base::destructor();
}

// state's enter
void CsAdjustmentScreenState::enter(void* owner)
{
	// call base
	Base::enter(this, owner);

	this->stream = false;
	this->transform = false;
	this->synchronizeGraphics = false;
	this->updatePhysics = false;
	this->processCollisions = false;
}

void CsAdjustmentScreenState::initNextState()
{
	this->nextState = GameState::safeCast(AutoPauseSelectScreenState::getInstance());
}