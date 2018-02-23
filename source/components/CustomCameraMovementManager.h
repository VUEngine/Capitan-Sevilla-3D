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
#define CustomCameraMovementManager_METHODS(ClassName)													\
		CameraMovementManager_METHODS(ClassName)														\

// declare the virtual methods which are redefined
#define CustomCameraMovementManager_SET_VTABLE(ClassName)												\
		CameraMovementManager_SET_VTABLE(ClassName)														\
		__VIRTUAL_SET(ClassName, CustomCameraMovementManager, focus);									\

#define CustomCameraMovementManager_ATTRIBUTES															\
		/* super's attributes */																		\
		CameraMovementManager_ATTRIBUTES																\
		/* update axis flag */																			\
		Vector3DFlag positionFlag;																		\
		/* pointer to function that implements the required focusing */									\
		bool (*focusFunction)(CustomCameraMovementManager, u32, u32);									\
		bool (*previousFocusFunction)(CustomCameraMovementManager, u32, u32);							\

// declare a CustomCameraMovementManager
__CLASS(CustomCameraMovementManager);


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

CustomCameraMovementManager CustomCameraMovementManager_getInstance();

void CustomCameraMovementManager_destructor(CustomCameraMovementManager this);
void CustomCameraMovementManager_focus(CustomCameraMovementManager this, u32 checkIfFocusEntityIsMoving);
void CustomCameraMovementManager_setPositionFlag(CustomCameraMovementManager this, Vector3DFlag positionFlag);
Vector3DFlag CustomCameraMovementManager_getPositionFlag(CustomCameraMovementManager this);
void CustomCameraMovementManager_enable(CustomCameraMovementManager this);
void CustomCameraMovementManager_disable(CustomCameraMovementManager this);
void CustomCameraMovementManager_enableFocusEasing(CustomCameraMovementManager this);
void CustomCameraMovementManager_disableFocusEasing(CustomCameraMovementManager this);
void CustomCameraMovementManager_alertWhenTargetFocused(CustomCameraMovementManager this);
void CustomCameraMovementManager_dontAlertWhenTargetFocused(CustomCameraMovementManager this);


#endif
