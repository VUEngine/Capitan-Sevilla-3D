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

extern StageEntryPointROMSpec LEVEL_1_STAGE_4_MAIN_EP;


//---------------------------------------------------------------------------------------------------------
//												LEVEL DEFINITION
//---------------------------------------------------------------------------------------------------------

PlatformerLevelROMSpec LEVEL_1_LV =
{
	// starting entry point
	(StageEntryPointSpec*)&LEVEL_1_STAGE_4_MAIN_EP,

	// id
	1,

	// name
	(void*)STR_LEVEL_1_NAME,
};
