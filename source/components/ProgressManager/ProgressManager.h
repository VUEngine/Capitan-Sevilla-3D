/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef PROGRESS_MANAGER_H_
#define PROGRESS_MANAGER_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <SaveDataManager.h>
#include <PlatformerLevelState.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// this struct is never instantiated, its sole purpose is to determine offsets of its members.
// therefore it acts as kind of like a map of sram content.
typedef struct GameSaveData
{
	// save data handled by base class
	SaveData baseSaveData;

	// brightness factor
	uint8 brightnessFactor;

} GameSaveData;


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

singleton class ProgressManager : SaveDataManager
{
	// time in current level
	uint32 currentLevelTime;
	// time in current level at last checkpoint
	uint32 checkpointCurrentLevelTime;
	// captain's current energy
	uint8 captainCurrentEnergy;
	// captain's current number of gums
	uint8 captainCurrentGums;

	static ProgressManager getInstance();
	uint32  getCurrentLevelTime();
	uint8   getCaptainCurrentEnergy();
	uint8   getCaptainCurrentGums();
	void initialize();
	void loadCheckPointData();
	void setCheckPointData();
	void resetCurrentLevelProgress();
	override void restoreSettings();
}


#endif
