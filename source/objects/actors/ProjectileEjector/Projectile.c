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
#include <Optics.h>
#include <PlatformerLevelState.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include "Projectile.h"


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Projectile, Actor);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Projectile, ProjectileDefinition* projectileDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(Projectile, projectileDefinition, id, internalId, name);

// class's constructor
void Projectile_constructor(Projectile this, ProjectileDefinition* projectileDefinition, s16 id, s16 internalId, const char* const name)
{
	ASSERT(this, "Projectile::constructor: null this");

	// construct base
	__CONSTRUCT_BASE(Actor, (ActorDefinition*)&projectileDefinition->actorDefinition, id, internalId, name);

	// save definition
	this->projectileDefinition = projectileDefinition;
}

// class's constructor
void Projectile_destructor(Projectile this)
{
	ASSERT(this, "Projectile::destructor: null this");

	MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kProjectileCheckPosition);

	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

void Projectile_ready(Projectile this, bool recursive)
{
	ASSERT(this, "Projectile::ready: null this");

	// call base
	__CALL_BASE_METHOD(Actor, ready, this, recursive);

	Projectile_stopMovement(this);
}

// start moving
void Projectile_startMovement(Projectile this)
{
	// set back to local position
	Actor_setLocalPosition(__SAFE_CAST(Actor, this), &this->projectileDefinition->position);

	// set to moving
	Actor_moveUniformly(__SAFE_CAST(Actor, this), &this->projectileDefinition->velocity);

	// activate shapes
	Entity_activateShapes(__SAFE_CAST(Entity, this), true);

	// show me
	Entity_show(__SAFE_CAST(Entity, this));

	// send first message of periodic position check
	if(this->projectileDefinition->checkDelay > -1)
	{
		MessageDispatcher_dispatchMessage(this->projectileDefinition->checkDelay, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kProjectileCheckPosition, NULL);
	}
}

// move back to ejector
void Projectile_stopMovement(Projectile this)
{
	// stop movement
	Actor_stopAllMovement(__SAFE_CAST(Actor, this));

	// deactivate shapes
	Entity_activateShapes(__SAFE_CAST(Entity, this), false);

	// hide me
	Entity_hide(__SAFE_CAST(Entity, this));
}

static void Projectile_checkPosition(Projectile this)
{
	if(	(this->projectileDefinition->maxPosition.x && (this->transformation.globalPosition.x > this->projectileDefinition->maxPosition.x)) ||
		(this->projectileDefinition->maxPosition.y && (this->transformation.globalPosition.y > this->projectileDefinition->maxPosition.y)) ||
		(this->projectileDefinition->maxPosition.z && (this->transformation.globalPosition.z > this->projectileDefinition->maxPosition.z)))
	{
		Projectile_stopMovement(this);
	}
	else
	{
		MessageDispatcher_dispatchMessage(this->projectileDefinition->checkDelay, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kProjectileCheckPosition, NULL);
	}
}

// state's handle message
bool Projectile_handleMessage(Projectile this, Telegram telegram)
{
	ASSERT(this, "Projectile::handleMessage: null this");

	switch(Telegram_getMessage(telegram))
	{
		case kProjectileEject:

			Projectile_startMovement(this);
			break;

		case kProjectileCheckPosition:

			Projectile_checkPosition(this);
			break;
	}

	return false;
}
