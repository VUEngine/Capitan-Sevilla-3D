/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef LIFT_H_
#define LIFT_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Actor.h>
#include <PlatformerLevelState.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// spec in ROM memory
typedef struct LiftSpec
{
	// base actor spec
	ActorSpec actorSpec;

	// velocity after entering
	Velocity velocity;

	// entry poto load after entering
	StageEntryPointSpec* entryPoint;

} LiftSpec;

typedef const LiftSpec LiftROMSpec;


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

class Lift : Actor
{
	// spec pointer
	LiftSpec* liftSpec;

	void constructor(LiftSpec* liftSpec, int16 internalId, const char* const name);
	override bool handleMessage(Telegram telegram);
	override void ready(bool recursive);
	override void resume();
}


#endif
