/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
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
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern Sound ShootSound;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void ProjectileEjector::constructor(ProjectileEjectorSpec* projectileEjectorSpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor((AnimatedEntitySpec*)&projectileEjectorSpec->animatedEntitySpec, internalId, name);

	// save spec
	this->projectileEjectorSpec = projectileEjectorSpec;

	// initialize members
	this->active = this->projectileEjectorSpec->initiallyActive;

	// No projectiles created yet
	this->createdProjectiles = 0;

	// Ready to fire
	this->coolingDown = false;
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
	for(uint8 i = 0; i < this->projectileEjectorSpec->maxProjectiles; i++)
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
	if(this->coolingDown)
	{
		return;
	}

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

				// play shooting sound
				SoundManager::playSound(
					SoundManager::getInstance(),
					&ShootSound,
					kPlayAll,
					(const Vector3D*)&this->transformation.globalPosition,
					kSoundWrapperPlaybackNormal,
					NULL,
					NULL
				);

				this->coolingDown = NULL != this->projectileEjectorSpec->ejectAnimationName;

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
		if(ProjectileEjector::canEject(this))
		{
			MessageDispatcher::dispatchMessage(0, Object::safeCast(this), Object::safeCast(this), kProjectileEject, NULL);
		}
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

bool ProjectileEjector::canEject()
{
	return !this->coolingDown;
}

// spawn a projectile, this is the callback of the "Eject" animation
void ProjectileEjector::onEjectAnimationComplete()
{
	// play idle animation
	AnimatedEntity::playAnimation(this, this->projectileEjectorSpec->idleAnimationName);

	this->coolingDown = false;
}
