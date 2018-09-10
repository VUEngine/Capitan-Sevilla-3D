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

// class's constructor
void ProjectileEjector::constructor(ProjectileEjectorDefinition* projectileEjectorDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor((AnimatedEntityDefinition*)&projectileEjectorDefinition->animatedEntityDefinition, id, internalId, name);

	// save definition
	this->projectileEjectorDefinition = projectileEjectorDefinition;

	// initialize members
	this->active = this->projectileEjectorDefinition->initiallyActive;
}

// class's destructor
void ProjectileEjector::destructor()
{
	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kProjectileEject);

	// not necessary to manually destroy the Projectile here as all children are automatically
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
	AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this), this->projectileEjectorDefinition->idleAnimationName);

	// send delayed message to self to trigger first shot
	if(this->active)
	{
		MessageDispatcher::dispatchMessage(this->projectileEjectorDefinition->initialEjectDelay, Object::safeCast(this), Object::safeCast(this), kProjectileEject, NULL);
	}
}

// state's handle message
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
		// construct projectile entities if they don't exist yet
		if(!this->children)
		{
			// add projectiles to stage
			for(u8 i = 0; i < this->projectileEjectorDefinition->maxProjectiles; i++)
			{
				Stage::spawnEntity(Game::getStage(Game::getInstance()), &this->projectileEjectorDefinition->projectilePositionedEntityDefinition, Container::safeCast(this), (EventListener)ProjectileEjector::ejectProjectile);
			}
		}
		else
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
					AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this), this->projectileEjectorDefinition->ejectAnimationName);

					// set projectile to moving state
					Projectile::startMovement(projectile);

					break;
				}
			}

			// send delayed message to self to trigger next shot
			MessageDispatcher::dispatchMessage(this->projectileEjectorDefinition->ejectDelay, Object::safeCast(this), Object::safeCast(this), kProjectileEject, NULL);
		}
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
	AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this), this->projectileEjectorDefinition->idleAnimationName);
}
