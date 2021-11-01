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
#include "Punk.h"


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void Punk::constructor(EnemySpec* enemySpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor(enemySpec, internalId, name);
}

void Punk::destructor()
{
	// destroy the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

bool Punk::handleMessage(Telegram telegram)
{
	// handle messages that any state would handle here
	switch(Telegram::getMessage(telegram))
	{
		case 1234:

			Punk::doDie(this);
			return true;
			break;

	}

	return Base::handleMessage(this, telegram);
}

void Punk::die()
{
	extern SpriteSpec* const PUNK_DYING_SPRITES[];
	Punk::addSprites(this, (SpriteSpec**)PUNK_DYING_SPRITES);

	Punk::stopAllMovement(this);
	Punk::allowCollisions(this, false);
	this->invalidateGraphics |= __INVALIDATE_ROTATION;
	this->respawn = false;

	MessageDispatcher::dispatchMessage(1, Object::safeCast(this), Object::safeCast(this), 1234, NULL);
}

void Punk::doDie()
{
	if(this->sprites)
	{
		SpriteManager::disposeSprite(SpriteManager::getInstance(), Sprite::safeCast(VirtualList::popFront(this->sprites)));
		SpriteManager::disposeSprite(SpriteManager::getInstance(), Sprite::safeCast(VirtualList::popFront(this->sprites)));
	}

	Punk::playAnimation(this, "Die");
}

void Punk::onDieAnimationComplete(Object eventFirer __attribute__ ((unused)))
{
	Punk::deleteMyself(this);
}

// process collisions
bool Punk::enterCollision(const CollisionInformation* collisionInformation)
{
	Shape collidingShape = collisionInformation->collidingShape;
	SpatialObject collidingObject = Shape::getOwner(collidingShape);
	uint32 collidingObjectInGameType = SpatialObject::getInGameType(collidingObject);

	Velocity velocity = (Velocity){-this->speed, 0, 0};

	switch(collidingObjectInGameType)
	{
		// speed things up by breaking early
		case kEnemyWall:

			this->speed = -this->speed;
			Punk::moveUniformly(this, &velocity);
			break;
	}

	return false;
}