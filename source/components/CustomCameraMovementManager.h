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

#ifndef CUSTOM_CAMERA_MOVEMENT_MANAGER_H_
#define CUSTOM_CAMERA_MOVEMENT_MANAGER_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <CameraMovementManager.h>
#include <Telegram.h>
#include <Entity.h>
#include <Camera.h>


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

#define SCREEN_EASING_X_DISPLACEMENT				200
#define SCREEN_POSITIVE_EASING_Y_DISPLACEMENT		250
#define SCREEN_NEGATIVE_EASING_Y_DISPLACEMENT		250
//#define SCREEN_EASING_Y_DISPLACEMENT				(3 << __FRAME_CYCLE)
#define SCREEN_HORIZONTAL_DISPLACEMENT 				30
#define SCREEN_VERTICAL_DISPLACEMENT 				(__SCREEN_HEIGHT / 2) + 30
#define SCREEN_WIDTH_REDUCTION						64
#define SCREEN_HEIGHT_REDUCTION						32


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

singleton class CustomCameraMovementManager : CameraMovementManager
{
	Camera camera;
	/* update axis flag */
	Vector3DFlag positionFlag;
	/* pointer to function that implements the required focusing */
	bool (*focusFunction)(void*, u32, u32);
	bool (*previousFocusFunction)(void*, u32, u32);

	// declare a CustomCameraMovementManager
	static CustomCameraMovementManager getInstance();
	void setPositionFlag(Vector3DFlag positionFlag);
	Vector3DFlag getPositionFlag();
	void enable();
	void disable();
	void enableFocusEasing();
	void disableFocusEasing();
	void alertWhenTargetFocused();
	void dontAlertWhenTargetFocused();
	override void focus(u32 checkIfFocusEntityIsMoving);
}


#endif
