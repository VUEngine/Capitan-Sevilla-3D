/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef STATE_EXIT_POINT_H_
#define STATE_EXIT_POINT_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Entity.h>
#include <PlatformerLevelState.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef struct StageExitPointSpec
{
	/// entity spec
	EntitySpec entitySpec;

	/// target entry point
	StageEntryPointSpec* stageEntryPointSpec;

} StageExitPointSpec;

typedef const StageExitPointSpec StageExitPointROMSpec;


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

class StageExitPoint : Entity
{
	StageEntryPointSpec* stageEntryPointSpec;

	void constructor(StageExitPointSpec* stageExitPointSpec, s16 internalId, const char* const name);
}


#endif
