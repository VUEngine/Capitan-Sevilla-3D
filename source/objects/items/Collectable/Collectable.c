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

#include <GameEvents.h>
#include <Game.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Box.h>
#include <PhysicalWorld.h>
#include <SoundManager.h>
#include <EventManager.h>
#include <ProgressManager.h>
#include "Collectable.h"
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern Sound JumpSound;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void Collectable::constructor(AnimatedEntitySpec* animatedEntitySpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor(animatedEntitySpec, internalId, name);
}

void Collectable::destructor()
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

bool Collectable::handleMessage(Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kItemTaken:
		{
			Collectable::collect(this);
			break;
		}
	}

	return false;
}

void Collectable::collect()
{
	// play collect sound
	SoundManager::playSound(
		SoundManager::getInstance(),
		&JumpSound,
		kPlayAll,
		(const Vector3D*)&this->transformation.globalPosition,
		kSoundWrapperPlaybackNormal,
		NULL,
		NULL
	);

	// set shape to inactive so no other hits with this item can occur
	Entity::allowCollisions(this, false);

	// delete myself now
	Container::deleteMyself(this);
}
