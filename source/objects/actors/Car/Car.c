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
#include "Car.h"


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern Sound EngineSound;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void Car::constructor(MovingOneWayEntitySpec* movingOneWayEntitySpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor(movingOneWayEntitySpec, internalId, name);

	this->engineSound = NULL;
}

void Car::destructor()
{
	if(!isDeleted(this->engineSound))
	{
		SoundWrapper::release(this->engineSound);
		this->engineSound = NULL;
	}

	// destroy the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void Car::ready(bool recursive)
{
	// call base
	Base::ready(this, recursive);

	this->engineSound = SoundManager::getSound(
		SoundManager::getInstance(),
		&EngineSound,
		kPlayAll,
		(EventListener)Car::onEngineSoundReleased,
		Object::safeCast(this)
	);

	if(!isDeleted(this->engineSound))
	{
		SoundWrapper::play(this->engineSound, (const Vector3D*)&this->transformation.globalPosition, kSoundWrapperPlaybackFadeIn);
	}
}

void Car::onEngineSoundReleased(Object eventFirer __attribute__((unused)))
{
	NM_ASSERT(eventFirer == Object::safeCast(this->engineSound), "Car::onEngineSoundReleased: no engine sound");

	this->engineSound = NULL;
}

