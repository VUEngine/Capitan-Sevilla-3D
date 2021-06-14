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
#include <MessageDispatcher.h>
#include <Optics.h>
#include <PhysicalWorld.h>
#include <MessageDispatcher.h>
#include <PlatformerLevelState.h>
#include <debugUtilities.h>
#include <Captain.h>
#include "MovingOneWayEntity.h"


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void MovingOneWayEntity::constructor(MovingOneWayEntitySpec* movingOneWayEntitySpec, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor((ActorSpec*)&movingOneWayEntitySpec->actorSpec, internalId, name);

	this->speed = movingOneWayEntitySpec->speed;
}

void MovingOneWayEntity::destructor()
{
	// destroy the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// override speed via extra info if given
void MovingOneWayEntity::setExtraInfo(void* extraInfo)
{
	if(extraInfo != NULL)
	{
		this->speed = __I_TO_FIX10_6((int)extraInfo);
	}
}

void MovingOneWayEntity::ready(bool recursive)
{
	// call base
	Base::ready(this, recursive);

	// start movement
	MovingOneWayEntity::startMovement(this);
}

void MovingOneWayEntity::startMovement()
{
	if(this->speed != 0)
	{
		if(isDeleted(Captain::getInstance()))
 		{
			Velocity velocity = {this->speed, 0, 0};
			Actor::moveUniformly(this, &velocity);
 			return;
 		}

 		const Vector3D* captainPosition = Captain::getPosition(Captain::getInstance());

		this->speed = captainPosition->x <= this->transformation.globalPosition.x ? this->speed : -this->speed;

 		Velocity velocity = {this->speed, 0, 0};
 		Actor::moveUniformly(this, &velocity);
	}
}

void MovingOneWayEntity::stopMovement()
{
	Actor::stopAllMovement(this);
}
