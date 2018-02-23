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
#include <Camera.h>
#include <EventManager.h>
#include <GoalDoor.h>
#include <PlatformerLevelState.h>
#include <LevelDoneScreenState.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(GoalDoor, Door);


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void GoalDoor_onFadeOutComplete(GoalDoor this, Object eventFirer);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(GoalDoor, AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(GoalDoor, animatedEntityDefinition, id, internalId, name);

// class's constructor
void GoalDoor_constructor(GoalDoor this, AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(Door, animatedEntityDefinition, id, internalId, name);
}

// class's destructor
void GoalDoor_destructor(GoalDoor this)
{
	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// ready
void GoalDoor_ready(Door this, bool recursive __attribute__ ((unused)))
{
	ASSERT(this, "GoalDoor::ready: null this");

	// call base
	__CALL_BASE_METHOD(Door, ready, this, recursive);

	AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Goal");
}

bool GoalDoor_hasDestination(Door this __attribute__ ((unused)))
{
	return true;
}

// state's handle message
bool GoalDoor_handleMessage(GoalDoor this, Telegram telegram)
{
	switch(Telegram_getMessage(telegram))
	{
		case kHeroEnterDoor:
		{
			// disable user input
			Game_disableKeypad(Game_getInstance());

			// fade out screen
			Brightness brightness = (Brightness){0, 0, 0};
			Camera_startEffect(Camera_getInstance(),
				kFadeTo, // effect type
				0, // initial delay (in ms)
				&brightness, // target brightness
				__FADE_DELAY, // delay between fading steps (in ms)
				(void (*)(Object, Object))GoalDoor_onFadeOutComplete, // callback function
				__SAFE_CAST(Object, this) // callback scope
			);

			return true;
			break;
		}
	}

	return __CALL_BASE_METHOD(Door, handleMessage, this, telegram);
}

bool GoalDoor_canEnter(GoalDoor this __attribute__ ((unused)))
{
	return true;
}

// handle event
static void GoalDoor_onFadeOutComplete(GoalDoor this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "GoalDoor::onFadeOutComplete: null this");

	// announce level completion
	Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), kEventLevelCompleted);

	// switch to next screen
	Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, LevelDoneScreenState_getInstance()));
}
