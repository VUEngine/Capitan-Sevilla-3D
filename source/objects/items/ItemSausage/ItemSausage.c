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
#include <SoundManager.h>
#include <EventManager.h>
#include "ItemSausage.h"


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern Sound JUMP_SND;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void ItemSausage::constructor(AnimatedEntitySpec* animatedEntitySpec, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(animatedEntitySpec, internalId, name);
}

void ItemSausage::destructor()
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void ItemSausage::collect()
{
	SoundManager::playSound(
		SoundManager::getInstance(),
		&JUMP_SND,
		kPlayAll,
		(const Vector3D*)&this->transformation.globalPosition,
		kSoundWrapperPlaybackNormal,
		NULL,
		NULL
	);

	// set shape to inactive so no other hits with this item can occur
	Entity::allowCollisions(this, false);

	AnimatedEntity::playAnimation(this, "Taken");
}

void ItemSausage::onTakenAnimationComplete()
{
	Container::deleteMyself(this);
}
