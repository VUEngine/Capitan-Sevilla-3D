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
#include <Entity.h>
#include <MessageDispatcher.h>
#include <Box.h>
#include <Container.h>
#include <Projectile.h>
#include <PlatformerLevelState.h>
#include "ProjectileEjector.h"


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(ProjectileEjector, AnimatedEntity);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(ProjectileEjector, ProjectileEjectorDefinition* projectileEjectorDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(ProjectileEjector, projectileEjectorDefinition, id, internalId, name);

// class's constructor
void ProjectileEjector_constructor(ProjectileEjector this, ProjectileEjectorDefinition* projectileEjectorDefinition, s16 id, s16 internalId, const char* const name)
{
	ASSERT(this, "ProjectileEjector::constructor: null this");

	// construct base
	Base_constructor(this, (AnimatedEntityDefinition*)&projectileEjectorDefinition->animatedEntityDefinition, id, internalId, name);

	// save definition
	this->projectileEjectorDefinition = projectileEjectorDefinition;

	// initialize members
	this->active = this->projectileEjectorDefinition->initiallyActive;
}

// class's destructor
void ProjectileEjector_destructor(ProjectileEjector this)
{
	ASSERT(this, "ProjectileEjector::destructor: null this");

	// discard pending delayed messages
	MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kProjectileEject);

	// not necessary to manually destroy the Projectile here as all children are automatically
	// destroyed as well when an entity is unloaded

	// delete the super object
	// must always be called at the end of the destructor
	Base_destructor();
}

void ProjectileEjector_ready(ProjectileEjector this, bool recursive)
{
	ASSERT(this, "ProjectileEjector::ready: null this");

	// call base
	Base_ready(this, recursive);

	// play idle animation
	AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), this->projectileEjectorDefinition->idleAnimationName);

	// send delayed message to self to trigger first shot
	if(this->active)
	{
		MessageDispatcher_dispatchMessage(this->projectileEjectorDefinition->initialEjectDelay, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kProjectileEject, NULL);
	}
}

// state's handle message
bool ProjectileEjector_handleMessage(ProjectileEjector this, Telegram telegram)
{
	ASSERT(this, "ProjectileEjector::handleMessage: null this");

	switch(Telegram_getMessage(telegram))
	{
		case kProjectileEject:

			ProjectileEjector_ejectProjectile(this);
			break;
	}

	return false;
}

// eject a projectile
void ProjectileEjector_ejectProjectile(ProjectileEjector this)
{
	ASSERT(this, "ProjectileEjector::ejectProjectile: null this");

	if(this->active)
	{
		// construct projectile entities if they don't exist yet
		if(!this->children)
		{
			// add projectiles to stage
			for(u8 i = 0; i < this->projectileEjectorDefinition->maxProjectiles; i++)
			{
				Stage_spawnEntity(Game_getStage(Game_getInstance()), &this->projectileEjectorDefinition->projectilePositionedEntityDefinition, __SAFE_CAST(Container, this), (EventListener)ProjectileEjector_ejectProjectile);
			}
		}
		else
		{
			// poll all projectiles to find a (re)useable one
			VirtualNode node = VirtualList_begin(this->children);
			Projectile projectile = NULL;
			for(; node; node = VirtualNode_getNext(node))
			{
				projectile = __SAFE_CAST(Projectile, VirtualNode_getData(node));
				if(Projectile_canBeReused(projectile))
				{
					// start ejection sequence
					AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), this->projectileEjectorDefinition->ejectAnimationName);

					// set projectile to moving state
					Projectile_startMovement(projectile);

					break;
				}
			}

			// send delayed message to self to trigger next shot
			MessageDispatcher_dispatchMessage(this->projectileEjectorDefinition->ejectDelay, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kProjectileEject, NULL);
		}
	}
}

void ProjectileEjector_setActive(ProjectileEjector this, bool active)
{
	ASSERT(this, "ProjectileEjector::setActive: null this");

	this->active = active;

	if(this->active)
	{
		MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kProjectileEject, NULL);
	}
	else
	{
		MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kProjectileEject);
	}
}

bool ProjectileEjector_isActive(ProjectileEjector this)
{
	ASSERT(this, "ProjectileEjector::isActive: null this");

	return this->active;
}

// spawn a projectile, this is the callback of the "Eject" animation
void ProjectileEjector_onEjectAnimationComplete(ProjectileEjector this)
{
	ASSERT(this, "ProjectileEjector::onEjectAnimationComplete: null this");

	// play idle animation
	AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), this->projectileEjectorDefinition->idleAnimationName);
}
