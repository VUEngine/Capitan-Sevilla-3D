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
#include <Utilities.h>
#include <I18n.h>
#include <EventManager.h>
#include "Mission.h"


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void Mission::constructor(MissionSpec* missionSpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor((AnimatedEntitySpec*)missionSpec, internalId, name);

	// add event listeners
	Object eventManager = Object::safeCast(EventManager::getInstance());
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)Mission::onSetModeToPlaying, kEventComicDeleted);
}

void Mission::destructor()
{
	// remove event listeners
	Object eventManager = Object::safeCast(EventManager::getInstance());
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)Mission::onSetModeToPlaying, kEventComicDeleted);

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void Mission::delete()
{
	Container::deleteMyself(this);
}

void Mission::resume()
{
	Base::resume(this);
	Mission::delete(this);
}

bool Mission::respawn()
{
	return false;
}

void Mission::onSetModeToPlaying(Object eventFirer __attribute__ ((unused)))
{
	char* language = Utilities::itoa(I18n::getActiveLanguage(I18n::getInstance()), 10, 1);
	AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this), language);
}
