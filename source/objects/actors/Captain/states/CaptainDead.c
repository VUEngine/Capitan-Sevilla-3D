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
