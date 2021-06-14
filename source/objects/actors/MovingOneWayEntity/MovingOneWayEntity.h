/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef MOVING_ONE_WAY_ENTITY_H_
#define MOVING_ONE_WAY_ENTITY_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Actor.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//											TYPE DEFINITIONS
//---------------------------------------------------------------------------------------------------------

typedef struct MovingOneWayEntitySpec
{
	/// actor spec
	ActorSpec actorSpec;

	/// speed (x axis)
	fix10_6 speed;

} MovingOneWayEntitySpec;

typedef const MovingOneWayEntitySpec MovingOneWayEntityROMSpec;


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

class MovingOneWayEntity : Actor
{
	fix10_6 speed;
	bool respawn;

	void constructor(MovingOneWayEntitySpec* movingOneWayEntitySpec, s16 internalId, const char* const name);
	void startMovement();
	void stopMovement();
	override void ready(bool recursive);
	override void setExtraInfo(void* extraInfo);
}


#endif
