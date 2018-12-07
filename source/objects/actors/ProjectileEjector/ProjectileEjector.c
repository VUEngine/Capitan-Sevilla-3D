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
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void ProjectileEjector::constructor(ProjectileEjectorSpec* projectileEjectorSpec, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor((AnimatedEntitySpec*)&projectileEjectorSpec->animatedEntitySpec, id, internalId, name);

	// save spec
	this->projectileEjectorSpec = projectileEjectorSpec;

	// initialize members
	this->active = this->projectileEjectorSpec->initiallyActive;

	// No projectiles created yet
	this->createdProjectiles = 0;
}

void ProjectileEjector::destructor()
{
	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kProjectileEject);

	// not necessary to manually destroy the Projectiles here as all children are automatically
	// destroyed as well when an entity is unloaded

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void ProjectileEjector::ready(bool recursive)
{
	// call base
	Base::ready(this, recursive);

	// play idle animation
	AnimatedEntity::playAnimation(this, this->projectileEjectorSpec->idleAnimationName);

	// add projectiles to stage as children of this ejector
	for(u8 i = 0; i < this->projectileEjectorSpec->maxProjectiles; i++)
	{
		Stage::spawnEntity(Game::getStage(Game::getInstance()), &this->projectileEjectorSpec->projectilePositionedEntitySpec, Container::safeCast(this), (EventListener)ProjectileEjector::onProjectileSpawned);
	}
}

void ProjectileEjector::onProjectileSpawned(Object eventFirer __attribute__ ((unused)))
{
	this->createdProjectiles++;

	// send delayed message to self to trigger first shot
	if(this->active && this->createdProjectiles == this->projectileEjectorSpec->maxProjectiles)
	{
		MessageDispatcher::dispatchMessage(this->projectileEjectorSpec->initialEjectDelay, Object::safeCast(this), Object::safeCast(this), kProjectileEject, NULL);
	}
}

bool ProjectileEjector::handleMessage(Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kProjectileEject:

			ProjectileEjector::ejectProjectile(this);
			break;
	}

	return false;
}

// eject a projectile
void ProjectileEjector::ejectProjectile()
{
	if(this->active)
	{
		// poll all projectiles to find a (re)useable one
		VirtualNode node = VirtualList::begin(this->children);
		Projectile projectile = NULL;
		for(; node; node = VirtualNode::getNext(node))
		{
			projectile = Projectile::safeCast(VirtualNode::getData(node));
			if(Projectile::canBeReused(projectile))
			{
				// start ejection sequence
				AnimatedEntity::playAnimation(this, this->projectileEjectorSpec->ejectAnimationName);

				// set projectile to moving state
				Projectile::startMovement(projectile);

				// fire ejection event
				Object::fireEvent(this, kEventProjectileEjected);

				break;
			}
		}

		// send delayed message to self to trigger next shot
		MessageDispatcher::dispatchMessage(this->projectileEjectorSpec->ejectDelay, Object::safeCast(this), Object::safeCast(this), kProjectileEject, NULL);
	}
}

void ProjectileEjector::setActive(bool active)
{
	this->active = active;

	if(this->active)
	{
		MessageDispatcher::dispatchMessage(0, Object::safeCast(this), Object::safeCast(this), kProjectileEject, NULL);
	}
	else
	{
		MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kProjectileEject);
	}
}

bool ProjectileEjector::isActive()
{
	return this->active;
}

// spawn a projectile, this is the callback of the "Eject" animation
void ProjectileEjector::onEjectAnimationComplete()
{
	// play idle animation
	AnimatedEntity::playAnimation(this, this->projectileEjectorSpec->idleAnimationName);
}
