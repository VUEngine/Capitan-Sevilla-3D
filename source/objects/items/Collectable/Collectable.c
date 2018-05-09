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
#include "Collectable.h"
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Collectable, AnimatedEntity);


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void Collectable_collect(Collectable this);
void Collectable_removeFromStage(Collectable this);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Collectable, AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(Collectable, animatedEntityDefinition, id, internalId, name);

// class's constructor
void Collectable_constructor(Collectable this, AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	ASSERT(this, "Collectable::constructor: null this");

	// construct base
	Base_constructor(this, animatedEntityDefinition, id, internalId, name);
}

// class's destructor
void Collectable_destructor(Collectable this)
{
	ASSERT(this, "Collectable::destructor: null this");

	// delete the super object
	// must always be called at the end of the destructor
	Base_destructor();
}

// state's handle message
bool Collectable_handleMessage(Collectable this, Telegram telegram)
{
	ASSERT(this, "Collectable::handleMessage: null this");

	extern const u16 COLLECT_SND[];

	switch(Telegram_getMessage(telegram))
	{
		case kItemTaken:

			// play collect sound
			SoundManager_playFxSound(SoundManager_getInstance(), COLLECT_SND, this->transformation.globalPosition);

			// set shape to inactive so no other hits with this item can occur
			Entity_activateShapes(__SAFE_CAST(Entity, this), false);

			// additional action
			Collectable_collect(this);

			// delete myself now
			Container_deleteMyself(__SAFE_CAST(Container, this));

			// send message to remove item in next game frame
			//MessageDispatcher_dispatchMessage(__GAME_FRAME_DURATION, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kRemoveFromStage, NULL);
			break;
/*
		case kRemoveFromStage:

			Collectable_removeFromStage(this);
			break;
*/	}

	return false;
}

void Collectable_collect(Collectable this __attribute__ ((unused)))
{
	ASSERT(this, "Collectable::collect: null this");
}
/*
void Collectable_removeFromStage(Collectable this)
{
	ASSERT(this, "Collectable::removeFromStage: null this");

	Container_deleteMyself(__SAFE_CAST(Container, this));
}
*/