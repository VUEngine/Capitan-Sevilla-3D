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
#include <Optics.h>
#include <PhysicalWorld.h>
#include <MessageDispatcher.h>
#include <PlatformerLevelState.h>
#include <debugUtilities.h>


#include "MovingOneWayEntity.h"


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(MovingOneWayEntity, Actor);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(MovingOneWayEntity, ActorDefinition* actorDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(MovingOneWayEntity, actorDefinition, id, internalId, name);

// class's constructor
void MovingOneWayEntity_constructor(MovingOneWayEntity this, ActorDefinition* actorDefinition, s16 id, s16 internalId, const char* const name)
{
	ASSERT(this, "MovingOneWayEntity::constructor: null this");

	// construct base
	__CONSTRUCT_BASE(Actor, actorDefinition, id, internalId, name);
}

void MovingOneWayEntity_destructor(MovingOneWayEntity this)
{
	ASSERT(this, "MovingOneWayEntity::destructor: null this");

	// destroy the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// set extra info
void MovingOneWayEntity_setExtraInfo(MovingOneWayEntity this, void* extraInfo)
{
	ASSERT(this, "MovingOneWayEntity::setExtraInfo: null this");

	this->speed = (extraInfo != NULL)
		? __I_TO_FIX10_6((int)extraInfo)
		: __I_TO_FIX10_6(-4);
}

void MovingOneWayEntity_ready(MovingOneWayEntity this, bool recursive)
{
	ASSERT(this, "MovingOneWayEntity::ready: null this");

	// call base
	__CALL_BASE_METHOD(Actor, ready, this, recursive);

	// start movement
	Velocity velocity = {this->speed, 0, 0};
	Actor_moveUniformly(__SAFE_CAST(Actor, this), &velocity);
}

bool MovingOneWayEntity_respawn(MovingOneWayEntity this __attribute__ ((unused)))
{
	ASSERT(this, "MovingOneWayEntity::respawn: null this");

	return false;
}