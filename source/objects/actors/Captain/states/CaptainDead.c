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

#include <MessageDispatcher.h>
#include <Game.h>
#include <KeypadManager.h>
#include <EventManager.h>
#include <PlatformerLevelState.h>
#include <debugUtilities.h>
#include <GameEvents.h>
#include <RumblePakEffects.h>
#include <Captain.h>
#include "CaptainDead.h"


//---------------------------------------------------------------------------------------------------------
//											DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern Sound GAME_OVER_SND;
extern EntitySpec GAME_OVER_EN;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void CaptainDead::constructor()
{
	// construct base
	Base::constructor();
}

void CaptainDead::destructor()
{
	// destroy base
	Base::destructor();
}

void CaptainDead::enter(void* owner)
{
	// set flashing palette back to original
	Captain::stopFlashing(owner);

	Captain::stopAllMovement(owner);
	Game::disableKeypad(Game::getInstance());
	Captain::setInvincible(owner, true);

	// set direction to right, so that tombstone is never mirrored
	Direction direction = {__RIGHT, __DOWN, __FAR};
	Captain::setDirection(owner, direction);

	// show animation
	Captain::playAnimation(owner, "Dead");

	// stop all other sounds, than play game over jingle
	SoundManager::stopAllSounds(SoundManager::getInstance(), true);
	SoundManager::playSound(
		SoundManager::getInstance(),
		&GAME_OVER_SND,
		kPlayAll,
		Actor::getPosition(Actor::safeCast(owner)),
		kSoundWrapperPlaybackNormal,
		NULL,
		NULL
	);

	// make 'em feel it
	RumblePakManager::startEffect(&RumbleEffectDieStrong);

	// add "game over"
	Vector3D position = {0, __PIXELS_TO_METERS(-48), __PIXELS_TO_METERS(-16)};
	Entity::addChildEntity(owner, &GAME_OVER_EN, -1, NULL, &position, NULL);

	// announce my dead
	Object::fireEvent(EventManager::getInstance(), kEventCaptainDied);
}
