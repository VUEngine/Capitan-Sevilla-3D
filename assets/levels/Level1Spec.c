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

#include <PlatformerLevelState.h>
#include <Languages.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageEntryPointROMSpec Level1Stage1MainEntryPoint;


//---------------------------------------------------------------------------------------------------------
//												LEVEL DEFINITION
//---------------------------------------------------------------------------------------------------------

PlatformerLevelROMSpec Level1 =
{
	// starting entry point
	(StageEntryPointSpec*)&Level1Stage1MainEntryPoint,

	// id
	1,

	// name
	(void*)STR_LEVEL_1_NAME,
};
