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
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Box.h>
#include <PhysicalWorld.h>
#include "LayerSwitchDoor.h"
#include <PlatformerLevelState.h>
#include <Hero.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(LayerSwitchDoor, Door);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(LayerSwitchDoor, AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(LayerSwitchDoor, animatedEntityDefinition, id, internalId, name);

// class's constructor
void LayerSwitchDoor_constructor(LayerSwitchDoor this, AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(Door, animatedEntityDefinition, id, internalId, name);
}

// class's destructor
void LayerSwitchDoor_destructor(LayerSwitchDoor this)
{
	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// state's handle message
bool LayerSwitchDoor_handleMessage(LayerSwitchDoor this, Telegram telegram)
{
	switch(Telegram_getMessage(telegram))
	{
		case kHeroEnterDoor:

			if(this->destinationDefinition)
			{
				// get global position of destination door
				LayerSwitchDoor destinationDoor = (LayerSwitchDoor)Container_getChildByName(__SAFE_CAST(Container, Game_getStage(Game_getInstance())), (char *)this->destinationDefinition->destinationName, true);
				Vector3D destinationDoorPosition = *Container_getGlobalPosition(__SAFE_CAST(Container, destinationDoor));

				// apply offset
				destinationDoorPosition.x += __PIXELS_TO_METERS(this->destinationDefinition->offset.x);
				destinationDoorPosition.y += __PIXELS_TO_METERS(this->destinationDefinition->offset.y);
				destinationDoorPosition.z += __PIXELS_TO_METERS(this->destinationDefinition->offset.z + this->destinationDefinition->offset.zDisplacement);

				// set hero's position
				Hero_getOutOfDoor(Hero_getInstance(), &destinationDoorPosition);
				// TODO: switch hero's palette according to new layer

				return true;
			}
			break;
	}

	return __CALL_BASE_METHOD(Door, handleMessage, this, telegram);
}
