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
	__CONSTRUCT_BASE(AnimatedEntity, (AnimatedEntityDefinition*)&projectileEjectorDefinition->animatedEntityDefinition, id, internalId, name);

	// save definition
	this->projectileEjectorDefinition = projectileEjectorDefinition;

	// initialize members
	this->currentProjectileIndex = 0;
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
	__DESTROY_BASE;
}

void ProjectileEjector_ready(ProjectileEjector this, bool recursive)
{
	ASSERT(this, "ProjectileEjector::ready: null this");

	// call base
	__CALL_BASE_METHOD(AnimatedEntity, ready, this, recursive);

	if(!this->children)
	{
		u8 i;
		for(i = 0; i < this->projectileEjectorDefinition->maxProjectiles; i++)
		{
			// add projectile to stage
			Stage_spawnEntity(Game_getStage(Game_getInstance()), &this->projectileEjectorDefinition->projectilePositionedEntityDefinition, __SAFE_CAST(Container, this), NULL);
		}
	}

	// send delayed message to self to trigger first shot
	MessageDispatcher_dispatchMessage(this->projectileEjectorDefinition->initialEjectDelay, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kProjectileEject, NULL);
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

	// start shooting sequence
	AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Shoot");

	// send delayed message to self to trigger next shot
	MessageDispatcher_dispatchMessage(this->projectileEjectorDefinition->ejectDelay, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kProjectileEject, NULL);

	// set projectile to moving state
	ASSERT(0 < VirtualList_getSize(this->children), "ProjectileEjector::ejectProjectile: no children");
	Projectile projectile = __SAFE_CAST(Projectile, VirtualList_getObjectAtPosition(this->children, this->currentProjectileIndex));
	MessageDispatcher_dispatchMessage(1, __SAFE_CAST(Object, this), __SAFE_CAST(Object, projectile), kProjectileEject, NULL);

	// increase projectile index
	if(++this->currentProjectileIndex >= this->projectileEjectorDefinition->maxProjectiles)
	{
		this->currentProjectileIndex = 0;
	}
}

// spawn a projectile, this is the callback of the "Shoot" animation
void ProjectileEjector_onShootAnimationComplete(ProjectileEjector this)
{
	ASSERT(this, "ProjectileEjector::onShootAnimationComplete: null this");

	// TODO: add shoot and idle animations to projectile ejector definition?
	AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Idle");
}
