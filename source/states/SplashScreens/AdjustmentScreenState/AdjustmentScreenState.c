/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Game.h>
#include <Camera.h>
#include <MessageDispatcher.h>
#include <AdjustmentScreenState.h>
#include <LangSelectScreenState.h>
#include <DirectDraw.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef ADJUSTMENT_SCREEN_STAGE_ST;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void AdjustmentScreenState::constructor()
{
	Base::constructor();

	SplashScreenState::setNextState(SplashScreenState::safeCast(this), GameState::safeCast(LangSelectScreenState::getInstance()));
	this->stageDefinition = (StageDefinition*)&ADJUSTMENT_SCREEN_STAGE_ST;
}

// class's destructor
void AdjustmentScreenState::destructor()
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
void AdjustmentScreenState::enter(void* owner)
{
	// call base
	Base::enter(this, owner);

	// move the printing area out of the visible screen to save CPU resources
	Printing::setWorldCoordinates(Printing::getInstance(), __SCREEN_WIDTH, __SCREEN_HEIGHT);

	// add rhombus effect
	VIPManager::pushBackPostProcessingEffect(VIPManager::getInstance(), AdjustmentScreenState::rhombusEmitterPostProcessingEffect, NULL);
}

void AdjustmentScreenState::processInput(u32 pressedKey __attribute__ ((unused)))
{
	// TODO: replace this ugly hack with a proper Game::isPaused check or something similar
	if(this->nextState == NULL)
	{
		Camera::startEffect(Camera::getInstance(), kFadeOut, __FADE_DELAY);
		Game::unpause(Game::getInstance(), GameState::safeCast(this));
	}
	else
	{
		SplashScreenState::loadNextState(SplashScreenState::safeCast(this));
	}
}

static void AdjustmentScreenState::rhombusEmitterPostProcessingEffect(u32 currentDrawingFrameBufferSet __attribute__ ((unused)), SpatialObject spatialObject __attribute__ ((unused)))
{
	// runtime working variables
	// negative value to achieve an initial delay
	static int radius = ADJUSTMENT_SCREEN_RHOMBUS_INITIAL_VALUE;

	// increase radius in each cycle
	radius += 2;

	if(radius < 68)
	{
		return;
	}
	else if(radius > 300)
	{
		// reset radius when reaching a certain length
		radius = ADJUSTMENT_SCREEN_RHOMBUS_INITIAL_VALUE;
		return;
	}

	// draw rhombus around object with given radius
	DirectDraw directDraw = DirectDraw::getInstance();

	// top left line
	DirectDraw::drawLine(
		directDraw,
		(PixelVector) {(192 - radius),	(112),			0, -((radius + ADJUSTMENT_SCREEN_RHOMBUS_INITIAL_VALUE)>>5)},
		(PixelVector) {(192),			(112 - radius),	0, -((radius + ADJUSTMENT_SCREEN_RHOMBUS_INITIAL_VALUE)>>5)},
		__COLOR_BRIGHT_RED
	);

	// top right line
	DirectDraw::drawLine(
		directDraw,
		(PixelVector) {(192 + radius),	(112),			0, -((radius + ADJUSTMENT_SCREEN_RHOMBUS_INITIAL_VALUE)>>5)},
		(PixelVector) {(192),			(112 - radius),	0, -((radius + ADJUSTMENT_SCREEN_RHOMBUS_INITIAL_VALUE)>>5)},
		__COLOR_BRIGHT_RED
	);

	// bottom right line
	DirectDraw::drawLine(
		directDraw,
		(PixelVector) {(192 + radius),	(112),			0, -((radius + ADJUSTMENT_SCREEN_RHOMBUS_INITIAL_VALUE)>>5)},
		(PixelVector) {(192),			(112 + radius),	0, -((radius + ADJUSTMENT_SCREEN_RHOMBUS_INITIAL_VALUE)>>5)},
		__COLOR_BRIGHT_RED
	);

	// bottom left line
	DirectDraw::drawLine(
		directDraw,
		(PixelVector) {(192 - radius),	(112),			0, -((radius + ADJUSTMENT_SCREEN_RHOMBUS_INITIAL_VALUE)>>5)},
		(PixelVector) {(192),			(112 + radius),	0, -((radius + ADJUSTMENT_SCREEN_RHOMBUS_INITIAL_VALUE)>>5)},
		__COLOR_BRIGHT_RED
	);
}
