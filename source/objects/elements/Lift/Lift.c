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

#include <GameEvents.h>
#include <Game.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Box.h>
#include <PhysicalWorld.h>
#include <SoundManager.h>
#include <EventManager.h>
#include <ProgressManager.h>
#include "Lift.h"
#include <PlatformerLevelState.h>

#include <ThankYouForPlayingScreenState.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern const u16 COLLECT_SND[];


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void Lift::constructor(LiftDefinition* liftDefinition, s16 id, s16 internalId, const char* const name)
{
	Base::constructor((ActorDefinition*)&liftDefinition->actorDefinition, id, internalId, name);

	this->liftDefinition = liftDefinition;
}

void Lift::destructor()
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// state's handle message
bool Lift::handleMessage(Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kLiftActivate:
		{
			AnimatedEntity::playAnimation(this, "Closed");

			// start delayed moving upwards
			MessageDispatcher::dispatchMessage(500, Object::safeCast(this), Object::safeCast(this), kLiftStart, NULL);

			// start fade out effect
			Brightness brightness = (Brightness){0, 0, 0};
			Camera::startEffect(Camera::getInstance(),
				kFadeTo, // effect type
				0, // initial delay (in ms)
				&brightness, // target brightness
				__FADE_DELAY, // delay between fading steps (in ms)
				(void (*)(Object, Object))Lift::onFadeOutComplete, // callback function
				Object::safeCast(this) // callback scope
			);

			break;
		}

		case kLiftStart:
		{
			Velocity velocity = {0, __I_TO_FIX10_6(-2), 0};
			Actor::moveUniformly(this, &velocity);

			break;
		}
	}

	return false;
}

// handle event
void Lift::onFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	Game::changeState(Game::getInstance(), (GameState)ThankYouForPlayingScreenState::getInstance());

	//PlatformerLevelState::enterStage(PlatformerLevelState::getInstance(), this->liftDefinition->entryPoint);
}
