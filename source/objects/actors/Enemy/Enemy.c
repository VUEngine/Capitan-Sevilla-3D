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
#include <CustomCameraEffectManager.h>
#include <SoundManager.h>
#include <MessageDispatcher.h>
#include <PlatformerLevelState.h>
#include <RumblePakEffects.h>
#include "Enemy.h"


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern Sound HIT_SND;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void Enemy::constructor(EnemySpec* enemySpec, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor((MovingOneWayEntitySpec*)&enemySpec->movingOneWayEntitySpec, internalId, name);

	// init members
	this->respawn = enemySpec->respawn;
	this->energy = enemySpec->energy;
	this->enemySpec = enemySpec;
	this->projectileEjectorEntity = NULL;
}

void Enemy::destructor()
{
	// remove event listeners
	if(this->projectileEjectorEntity)
	{
		Object::removeEventListener(this->projectileEjectorEntity, Object::safeCast(this), (EventListener)Enemy::onProjectileEjected, kEventProjectileEjected);
	}

	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kEntityFlash);

	// destroy the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// ready method
void Enemy::ready(bool recursive)
{
	// call base
	Base::ready(this, recursive);

	// add projectile ejector
	if(this->enemySpec->projectileEjectorSpec)
	{
		this->projectileEjectorEntity = Entity::addChildEntity(this, (EntitySpec*)this->enemySpec->projectileEjectorSpec, -1, NULL, &this->enemySpec->projectileEjectorPosition, NULL);
		Object::addEventListener(this->projectileEjectorEntity, Object::safeCast(this), (EventListener)Enemy::onProjectileEjected, kEventProjectileEjected);
	}
}

void Enemy::takeHit(u8 power)
{
	// start short screen shake
	Camera::startEffect(Camera::getInstance(), kShake, 100);

	// play sound
	SoundManager::playSound(
		SoundManager::getInstance(),
		&HIT_SND,
		kPlayAll,
		(const Vector3D*)&this->transformation.globalPosition,
		kSoundWrapperPlaybackNormal,
		NULL,
		NULL
	);

	// reduce energy
	if(power < this->energy)
	{
		this->energy -= power;

		Enemy::startFlashing(this);

		RumblePakManager::startEffect(&RumbleEffectTakeLightDamage);
	}
	else
	{
		Enemy::die(this);

		RumblePakManager::startEffect(&RumbleEffectDieLight);
	}
}

void Enemy::die()
{
	this->respawn = false;
	Enemy::stopFlashing(this);
	Enemy::deleteMyself(this);
}

bool Enemy::handleMessage(Telegram telegram)
{
	// handle messages that any state would handle here
	switch(Telegram::getMessage(telegram))
	{
		case kStopFlashing:

			Enemy::stopFlashing(this);
			return true;
			break;

		case kEntityFlash:

			Enemy::flash(this);
			return true;
			break;
	}

	return Base::handleMessage(this, telegram);
}

void Enemy::onProjectileEjected(Object eventFirer __attribute__ ((unused)))
{
	// play shoot animation
	AnimatedEntity::playAnimation(this, "Shoot");
}

void Enemy::startFlashing()
{
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kEntityFlash);
	MessageDispatcher::dispatchMessage(0, Object::safeCast(this), Object::safeCast(this), kEntityFlash, NULL);
	MessageDispatcher::dispatchMessage(ENEMY_FLASH_DURATION, Object::safeCast(this), Object::safeCast(this), kStopFlashing, NULL);
}

void Enemy::stopFlashing()
{
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kEntityFlash);
 	Enemy::resetPalette(this);
}

void Enemy::flash()
{
	Enemy::toggleFlashPalette(this);
	MessageDispatcher::dispatchMessage(ENEMY_FLASH_INTERVAL, Object::safeCast(this), Object::safeCast(this), kEntityFlash, NULL);
}

void Enemy::toggleFlashPalette()
{
	VirtualList sprites = Entity::getSprites(this);
	VirtualNode node = VirtualList::begin(sprites);
	for(; node; node = VirtualNode::getNext(node))
	{
		Sprite sprite = Sprite::safeCast(VirtualNode::getData(node));
		Texture texture = Sprite::getTexture(sprite);

		TextureSpec* textureSpec = Texture::getSpec(texture);

		if(Texture::getPalette(texture) == textureSpec->palette)
		{
			Texture::setPalette(texture, ENEMY_FLASH_PALETTE);
		}
		else
		{
			Texture::setPalette(texture, textureSpec->palette);
		}

		Sprite::rewrite(sprite);
	}
}

void Enemy::resetPalette()
{
	VirtualList sprites = Entity::getSprites(this);
	VirtualNode node = VirtualList::begin(sprites);
	for(; node; node = VirtualNode::getNext(node))
	{
		Sprite sprite = Sprite::safeCast(VirtualNode::getData(node));
		Texture texture = Sprite::getTexture(sprite);

		TextureSpec* textureSpec = Texture::getSpec(texture);
		Texture::setPalette(texture, textureSpec->palette);

		Sprite::rewrite(sprite);
	}
}

// spawn a projectile, this is the callback of the "Eject" animation
void Enemy::onEjectAnimationComplete()
{
	// play idle animation
	AnimatedEntity::playAnimation(this, "Idle");
}

bool Enemy::respawn()
{
	return this->respawn;
}