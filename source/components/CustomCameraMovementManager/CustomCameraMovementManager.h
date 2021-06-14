/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
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
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

singleton class CustomCameraMovementManager : CameraMovementManager
{
	Camera camera;
	// update axis flag
	Vector3DFlag positionFlag;
	// pointer to function that implements the required focusing
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
