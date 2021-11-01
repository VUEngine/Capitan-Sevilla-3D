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
#include <MessageDispatcher.h>
#include <Box.h>
#include <PhysicalWorld.h>
#include <macros.h>
#include <debugConfig.h>
#include <GameEvents.h>
#include <EventManager.h>
#include <PlatformerLevelState.h>
#include "StageExitPoint.h"

#include <CreditsState.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void StageExitPoint::constructor(StageExitPointSpec* stageExitPointSpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor((EntitySpec*)&stageExitPointSpec->entitySpec, internalId, name);

	this->stageEntryPointSpec = stageExitPointSpec->stageEntryPointSpec;

	// add event listeners
	Object eventManager = Object::safeCast(EventManager::getInstance());
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)StageExitPoint::onExitPointReached, kEventExitPointReached);
}

void StageExitPoint::destructor()
{
	// remove event listeners
	Object eventManager = Object::safeCast(EventManager::getInstance());
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)StageExitPoint::onExitPointReached, kEventExitPointReached);

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void StageExitPoint::onExitPointReached(Object eventFirer __attribute__ ((unused)))
{
	// start fade out effect
	Brightness brightness = (Brightness){0, 0, 0};
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		&brightness, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))StageExitPoint::onFadeOutComplete, // callback function
		Object::safeCast(this) // callback scope
	);
}

void StageExitPoint::onFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	if(this->stageEntryPointSpec != NULL)
	{
		PlatformerLevelState::enterStage(PlatformerLevelState::getInstance(), this->stageEntryPointSpec);
	}
	else
	{
    	Game::changeState(Game::getInstance(), (GameState)CreditsState::getInstance());
	}
}
