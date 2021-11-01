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

#include "CaptainMoving.h"
#include "CaptainIdle.h"
#include "../Captain.h"

#include <PlatformerLevelState.h>
#include <MessageDispatcher.h>
#include <KeypadManager.h>
#include <SoundManager.h>
#include <debugUtilities.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern Sound WALK_SND;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void CaptainMoving::constructor()
{
	// construct base
	Base::constructor();

	this->bouncing = false;
}

void CaptainMoving::destructor()
{
	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kDisallowJumpOnBouncing);

	// destroy base
	Base::destructor();
}

void CaptainMoving::enter(void* owner)
{
	KeypadManager::registerInput(KeypadManager::getInstance(), __KEY_PRESSED | __KEY_RELEASED);

	// make sure that the captain's body is awaken right now so the check during
	// the execute method doesn't fail
	Captain::applyForce(owner, __X_AXIS, false);
}

void CaptainMoving::execute(void* owner)
{
	// keep adding force
	if(((K_LL | K_LR ) & KeypadManager::getHoldKey(KeypadManager::getInstance())) && Body::isAwake(Actor::getBody(owner)))
	{
		Captain::applyForce(owner, __X_AXIS, false);
	}

	// play footstep sounds
	/*if (AnimatedEntity::isAnimationLoaded(AnimatedEntity::safeCast(owner), "Walk"))
	{
		int8 currentFrame = AnimatedEntity::getActualFrame(AnimatedEntity::safeCast(owner));
		if (currentFrame == 0 || currentFrame == 6)
		{
			SoundManager::playSound(
				SoundManager::getInstance(),
				&WALK_SND,
				kPlayAll,
				Actor::getPosition(Actor::safeCast(owner)),
				kSoundWrapperPlaybackNormal,
				NULL,
				NULL
			);
		}
	}*/
}

bool CaptainMoving::processMessage(void* owner, Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kMessageBodyStopped:

			Captain::stopMovementOnAxis(owner, *(int*)Telegram::getExtraInfo(telegram));
			return true;
			break;

		case kMessageBodyStartedMoving:

			Captain::startedMovingOnAxis(owner, *(int*)Telegram::getExtraInfo(telegram));
			break;
	}

	return false;
}

void CaptainMoving::onKeyPressed(void* owner, const UserInput* userInput)
{
	if((K_SEL|K_RD|K_RU|K_RL|K_RR|K_LT|K_RT) & userInput->pressedKey)
	{
		if(!Captain::isJumping(owner))
		{
			Captain::reload(owner);
		}
	}
	else if(K_A & userInput->pressedKey)
	{
		Captain::jump(owner, !this->bouncing);
	}
	else if(K_B & userInput->pressedKey)
	{
		Captain::startShooting(owner);
	}
	else if((K_LL | K_LR ) & (userInput->pressedKey | userInput->holdKey))
	{
		Captain::applyForce(owner, __X_AXIS, true);

		Captain::checkDirection(owner, userInput->pressedKey, "Walk");
	}
	else if(K_LD & userInput->pressedKey)
	{
		if(!Captain::isJumping(owner))
		{
			Captain::kneel(owner);
		}
	}
}

void CaptainMoving::onKeyReleased(void* owner, const UserInput* userInput)
{
	if((K_LL | K_LR) & userInput->releasedKey)
	{
		Captain::stopAddingForce(owner);
	}
}

