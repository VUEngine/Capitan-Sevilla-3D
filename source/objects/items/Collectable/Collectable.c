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

extern const u16 COLLECT_SND[];


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void Collectable::constructor(AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(animatedEntityDefinition, id, internalId, name);
}

// class's destructor
void Collectable::destructor()
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// state's handle message
bool Collectable::handleMessage(Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kItemTaken:
		{
			// play collect sound
			SoundManager::playFxSound(SoundManager::getInstance(), COLLECT_SND, this->transformation.globalPosition);

			// set shape to inactive so no other hits with this item can occur
			Entity::activateShapes(this, false);

			// additional action
			Collectable::collect(this);

			// delete myself now
			Container::deleteMyself(this);

			break;
		}
	}

	return false;
}

void Collectable::collect()
{}