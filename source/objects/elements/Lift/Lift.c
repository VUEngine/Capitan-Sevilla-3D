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
#include "Lift.h"
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern Sound LIFT_SND;
extern Sound LIFT_BREAK_SND;
extern Sound INTRO_LOWER_SONG;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void Lift::constructor(LiftSpec* liftSpec, s16 internalId, const char* const name)
{
	Base::constructor((ActorSpec*)&liftSpec->actorSpec, internalId, name);

	this->liftSpec = liftSpec;
}

void Lift::destructor()
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void Lift::ready(bool recursive)
{
	Base::ready(this, recursive);

	if(NULL == this->liftSpec->entryPoint)
	{
		Lift::break(this);
	}
}

void Lift::resume()
{
	Base::resume(this);

	SoundManager::playSound(
		SoundManager::getInstance(),
		&INTRO_LOWER_SONG,
		kPlayAll,
		(const Vector3D*)&this->transformation.globalPosition,
		kSoundWrapperPlaybackNormal,
		NULL,
		NULL
	);
}

bool Lift::handleMessage(Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kLiftActivate:
		{
			AnimatedEntity::playAnimation(this, "Closed");

			// start delayed moving
			MessageDispatcher::dispatchMessage(500, Object::safeCast(this), Object::safeCast(this), kLiftStart, NULL);
			break;
		}

		case kLiftStart:
		{
			SoundManager::playSound(
				SoundManager::getInstance(),
				&LIFT_SND,
				kPlayAll,
				(const Vector3D*)&this->transformation.globalPosition,
				kSoundWrapperPlaybackNormal,
				NULL,
				NULL
			);

			Actor::moveUniformly(this, &this->liftSpec->velocity);

			// start fade out effect
			Brightness brightness = (Brightness){0, 0, 0};
			Camera::startEffect(Camera::getInstance(),
				kFadeTo, // effect type
				2000, // initial delay (in ms)
				&brightness, // target brightness
				__FADE_DELAY, // delay between fading steps (in ms)
				(void (*)(Object, Object))Lift::onFadeOutComplete, // callback function
				Object::safeCast(this) // callback scope
			);
			
			break;
		}
	}

	return false;
}

void Lift::onFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	PlatformerLevelState::enterStage(PlatformerLevelState::getInstance(), this->liftSpec->entryPoint);
}

void Lift::break()
{
	SoundManager::playSound(
		SoundManager::getInstance(),
		&LIFT_BREAK_SND,
		kPlayAll,
		(const Vector3D*)&this->transformation.globalPosition,
		kSoundWrapperPlaybackNormal,
		(EventListener)Lift::onBreakingSoundReleased, 
		Object::safeCast(this)
	);
}

void Lift::onBreakingSoundReleased(Object eventFirer __attribute__((unused)))
{
	Lift::allowCollisions(this, false);

	Lift::playAnimation(this, "Broken");

	SoundManager::playSound(
		SoundManager::getInstance(),
		&INTRO_LOWER_SONG,
		kPlayAll,
		(const Vector3D*)&this->transformation.globalPosition,
		kSoundWrapperPlaybackNormal,
		NULL,
		NULL
	);
}

