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
#include <ProgressManager.h>
#include <AutomaticPauseManager.h>
#include <PrecautionScreenState.h>
#include <AdjustmentScreenState.h>
#include <AutomaticPauseSelectionScreenState.h>
#include <LanguageSelectionScreenState.h>
#include <RugarsoAnimationScreenState.h>
#include <TitleScreenState.h>
#include <CreditsState.h>


//---------------------------------------------------------------------------------------------------------
//											GAME'S MAIN LOOP
//---------------------------------------------------------------------------------------------------------

int32 main()
{
	// initialize plugins
	AutomaticPauseManager::setActive(AutomaticPauseManager::getInstance(), true);
	AutomaticPauseManager::setAutomaticPauseDelay(AutomaticPauseManager::getInstance(), 30);
	ProgressManager::restoreSettings(ProgressManager::getInstance());
	SplashScreenState::setNextState(
		SplashScreenState::safeCast(PrecautionScreenState::getInstance()),
		GameState::safeCast(AdjustmentScreenState::getInstance())
	);
	SplashScreenState::setNextState(
		SplashScreenState::safeCast(AdjustmentScreenState::getInstance()),
		GameState::safeCast(LanguageSelectionScreenState::getInstance())
	);
	SplashScreenState::setNextState(
		SplashScreenState::safeCast(LanguageSelectionScreenState::getInstance()),
		GameState::safeCast(RugarsoAnimationScreenState::getInstance())
	);
	SplashScreenState::setNextState(
		SplashScreenState::safeCast(RugarsoAnimationScreenState::getInstance()),
		GameState::safeCast(TitleScreenState::getInstance())
	);

	// start the game
	//Game::start(Game::getInstance(), GameState::safeCast(CreditsState::getInstance()));
	//Game::start(Game::getInstance(), GameState::safeCast(PlatformerLevelState::getInstance()));
	//Game::start(Game::getInstance(), GameState::safeCast(TitleScreenState::getInstance()));
	//Game::start(Game::getInstance(), GameState::safeCast(AdjustmentScreenState::getInstance()));
	Game::start(Game::getInstance(), GameState::safeCast(PrecautionScreenState::getInstance()));

	// end program
	return true;
}
