/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void StageExitPoint::constructor(EntityDefinition* inGameEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(inGameEntityDefinition, id, internalId, name);

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
	// TODO: move hardcoded entry point to stageexitpointromdef

	static int times = 0;

	if(times == 0)
	{
		times++;
		extern StageEntryPointDefinition LEVEL_1_STAGE_2_MAIN_EP;
		PlatformerLevelState::enterStage(PlatformerLevelState::getInstance(), (StageEntryPointDefinition*)&LEVEL_1_STAGE_2_MAIN_EP);
	}
	else
	{
		#include <CreditsState.h>
    	Game::changeState(Game::getInstance(), (GameState)CreditsState::getInstance());
	}
}
