/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef MISSION_H_
#define MISSION_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AnimatedEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//											TYPE DEFINITIONS
//---------------------------------------------------------------------------------------------------------

typedef const AnimatedEntitySpec MissionSpec;
typedef const MissionSpec MissionROMSpec;


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

class Mission : AnimatedEntity
{
	void constructor(MissionSpec* missionSpec, s16 internalId, const char* const name);
	override bool respawn();
	override void resume();
	void delete();
}


#endif
