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

#include <GameEvents.h>
#include <CustomCameraMovementManager.h>
#include <Optics.h>
#include <Camera.h>
#include <MessageDispatcher.h>
#include <Actor.h>
#include <Game.h>
#include <PhysicalWorld.h>
#include <EventManager.h>
#include <Utilities.h>

#include <debugConfig.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

// define the CustomCameraMovementManager
__CLASS_DEFINITION(CustomCameraMovementManager, CameraMovementManager);

__CLASS_FRIEND_DEFINITION(Camera);


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void CustomCameraMovementManager_constructor(CustomCameraMovementManager this);
static bool CustomCameraMovementManager_doFocusWithNoEasing(CustomCameraMovementManager this, u32 checkIfFocusEntityIsMoving, u32 introFocusing);
static bool CustomCameraMovementManager_dontFocus(CustomCameraMovementManager this, u32 checkIfFocusEntityIsMoving, u32 introFocusing);
static bool CustomCameraMovementManager_doFocus(CustomCameraMovementManager this, u32 checkIfFocusEntityIsMoving, u32 introFocusing);
static bool CustomCameraMovementManager_doFocusAndAlertWhenTargetReached(CustomCameraMovementManager this, u32 checkIfFocusEntityIsMoving, u32 introFocusing);


//---------------------------------------------------------------------------------------------------------
//												GLOBALS
//---------------------------------------------------------------------------------------------------------

static Camera _camera = NULL;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// it's a singleton
__SINGLETON(CustomCameraMovementManager);

// class's constructor
static void __attribute__ ((noinline)) CustomCameraMovementManager_constructor(CustomCameraMovementManager this)
{
	ASSERT(this, "CustomCameraMovementManager::constructor: null this");

	// construct base object
	__CONSTRUCT_BASE(CameraMovementManager);

	this->positionFlag.x = 0;
	this->positionFlag.y = 0;
	this->positionFlag.z = 0;

	this->focusFunction = &CustomCameraMovementManager_doFocus;
	this->previousFocusFunction = this->focusFunction;

	_camera = Camera_getInstance();

	NM_ASSERT(_camera, "CustomCameraMovementManager::constructor: null _camera");
}

// class's destructor
void CustomCameraMovementManager_destructor(CustomCameraMovementManager this)
{
	ASSERT(this, "CustomCameraMovementManager::destructor: null this");

	// destroy base
	__SINGLETON_DESTROY;
}

// center world's _camera in function of focus actor's position
void CustomCameraMovementManager_focus(CustomCameraMovementManager this, u32 checkIfFocusEntityIsMoving __attribute__ ((unused)))
{
	ASSERT(this, "CustomCameraMovementManager::focus: null this");

	this->focusFunction(this, checkIfFocusEntityIsMoving, false);
}

static bool CustomCameraMovementManager_doFocusWithNoEasing(CustomCameraMovementManager this __attribute__ ((unused)), u32 checkIfFocusEntityIsMoving __attribute__ ((unused)), u32 introFocusing __attribute__ ((unused)))
{
	ASSERT(this, "CustomCameraMovementManager::doFocusWithNoEasing: null this");

	Vector3D focusEntityPosition = *_camera->focusEntityPosition;
	Direction direction = Entity_getDirection(__SAFE_CAST(Entity, _camera->focusEntity));
	_camera->position.x = focusEntityPosition.x + direction.x * _camera->focusEntityPositionDisplacement.x - __PIXELS_TO_METERS(__SCREEN_WIDTH / 2);
	_camera->position.y = focusEntityPosition.y + _camera->focusEntityPositionDisplacement.y - __PIXELS_TO_METERS(__SCREEN_HEIGHT / 2);

	Camera_capPosition(_camera);
	Camera_forceDisplacement(_camera, true);

	return true;
}

// center world's _camera in function of focus actor's position
static bool CustomCameraMovementManager_dontFocus(CustomCameraMovementManager this __attribute__ ((unused)), u32 checkIfFocusEntityIsMoving __attribute__ ((unused)), u32 introFocusing __attribute__ ((unused)))
{
	ASSERT(this, "CustomCameraMovementManager::dontFocus: null this");

	return false;
}

// center world's _camera in function of focus actor's position
static bool CustomCameraMovementManager_doFocus(CustomCameraMovementManager this, u32 checkIfFocusEntityIsMoving __attribute__ ((unused)), u32 introFocusing __attribute__ ((unused)))
{
	ASSERT(this, "CustomCameraMovementManager::doFocus: null this");

	_camera->lastDisplacement.x = 0;
	_camera->lastDisplacement.y = 0;
	_camera->lastDisplacement.z = 0;

	// if focusEntity is defined
	if(!_camera->focusEntity)
	{
		return false;
	}

	Direction direction = Entity_getDirection(__SAFE_CAST(Entity, _camera->focusEntity));

	ASSERT(__SAFE_CAST(Actor, _camera->focusEntity), "CustomCameraMovementManager::update: focus entity is not an actor");

	Vector3D screenPreviousPosition = _camera->position;

	Vector3DFlag reachedTargetFlag = {true, true, true};

	Vector3D focusEntityPosition = *_camera->focusEntityPosition;

	Vector3D position3D = Vector3D_getRelativeToCamera(focusEntityPosition);
	PixelVector position2D = Vector3D_projectToPixelVector(position3D, 0);

	{
		bool focusEntityOutOfBounds = (unsigned)(position2D.x - _cameraFrustum->x0 - SCREEN_WIDTH_REDUCTION) > (unsigned)(_cameraFrustum->x1 - _cameraFrustum->x0 - SCREEN_WIDTH_REDUCTION);

		if(this->positionFlag.x | focusEntityOutOfBounds)
		{
			// calculate the target position
			fix10_6 horizontalPosition = _camera->position.x;
			fix10_6 horizontalTarget = focusEntityPosition.x + direction.x * _camera->focusEntityPositionDisplacement.x - __PIXELS_TO_METERS(__SCREEN_WIDTH / 2);

			fix10_6 easingDisplacement = __PIXELS_TO_METERS(7);

			if(introFocusing)
			{
				easingDisplacement = __PIXELS_TO_METERS(1);
			}

			reachedTargetFlag.x = false;

			if(horizontalPosition + easingDisplacement < horizontalTarget)
			{
				_camera->position.x += easingDisplacement;
			}
			else if(horizontalPosition - easingDisplacement > horizontalTarget)
			{
				_camera->position.x -= easingDisplacement;
			}
			else
			{
				_camera->position.x = horizontalTarget;
				reachedTargetFlag.x = true;
			}

			if(0 > _camera->position.x)
			{
				_camera->position.x = 0;
				reachedTargetFlag.x = true;
			}
			else if(_camera->stageSize.x < _camera->position.x + __PIXELS_TO_METERS(__SCREEN_WIDTH))
			{
				_camera->position.x = _camera->stageSize.x - __PIXELS_TO_METERS(__SCREEN_WIDTH);
				reachedTargetFlag.x = true;
			}

			_camera->lastDisplacement.x = (_camera->position.x - screenPreviousPosition.x);
		}
	}

	{
		bool focusEntityOutOfBounds = position2D.y > _cameraFrustum->y1 - SCREEN_HEIGHT_REDUCTION || position2D.y < _cameraFrustum->y0 + SCREEN_HEIGHT_REDUCTION / 4;

		if(this->positionFlag.y | focusEntityOutOfBounds)
		{
			// calculate the target position
			fix10_6 verticalPosition = _camera->position.y;
			fix10_6 verticalTarget = focusEntityPosition.y + _camera->focusEntityPositionDisplacement.y - __PIXELS_TO_METERS(__SCREEN_HEIGHT / 2);

			fix10_6 downEasingDisplacement = __PIXELS_TO_METERS(3);
			fix10_6 upEasingDisplacement = __PIXELS_TO_METERS(3);

			if(introFocusing)
			{
				downEasingDisplacement = __PIXELS_TO_METERS(1);
				upEasingDisplacement = __PIXELS_TO_METERS(1);
			}
			else
			{
				Velocity velocity = Actor_getVelocity(__SAFE_CAST(Actor, _camera->focusEntity));

				if(0 < velocity.y)
				{
					downEasingDisplacement = __PIXELS_TO_METERS(8);
				}
			}

			reachedTargetFlag.y = false;

			if(focusEntityOutOfBounds)
			{
				this->positionFlag.y = true;
			}

			if(verticalPosition + downEasingDisplacement < verticalTarget)
			{
				_camera->position.y += downEasingDisplacement;
			}
			else if(verticalPosition - upEasingDisplacement > verticalTarget)
			{
				_camera->position.y -= upEasingDisplacement;
			}
			else
			{
				_camera->position.y = verticalTarget;
				this->positionFlag.y = false;
				reachedTargetFlag.y = true;
			}

			if(0 > _camera->position.y)
			{
				_camera->position.y = 0;
				reachedTargetFlag.y = true;
			}
			else if(_camera->stageSize.y < _camera->position.y + __PIXELS_TO_METERS(__SCREEN_HEIGHT))
			{
				_camera->position.y = _camera->stageSize.y - __PIXELS_TO_METERS(__SCREEN_HEIGHT);
				reachedTargetFlag.y = true;
			}

			_camera->lastDisplacement.y = _camera->position.y - screenPreviousPosition.y;
		}
	}

	if(reachedTargetFlag.x && reachedTargetFlag.y)
	{
		return true;
	}

	return false;
}

// center world's _camera in function of focus actor's position
static bool CustomCameraMovementManager_doFocusAndAlertWhenTargetReached(CustomCameraMovementManager this, u32 checkIfFocusEntityIsMoving __attribute__ ((unused)), u32 introFocusing __attribute__ ((unused)))
{
	if(CustomCameraMovementManager_doFocus(this, checkIfFocusEntityIsMoving, true))
	{
		Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), kEventScreenFocused);

		return true;
	}

	return false;
}

void CustomCameraMovementManager_setPositionFlag(CustomCameraMovementManager this, Vector3DFlag positionFlag)
{
	ASSERT(this, "CustomCameraMovementManager::setPositionFlag: null this");

	this->positionFlag = positionFlag;
}

Vector3DFlag CustomCameraMovementManager_getPositionFlag(CustomCameraMovementManager this)
{
	ASSERT(this, "CustomCameraMovementManager::getPositionFlag: null this");

	return this->positionFlag;
}

void CustomCameraMovementManager_enable(CustomCameraMovementManager this)
{
	ASSERT(this, "CustomCameraMovementManager::enable: null this");

	this->focusFunction = this->previousFocusFunction;
	this->previousFocusFunction = this->focusFunction;
}

void CustomCameraMovementManager_disable(CustomCameraMovementManager this)
{
	ASSERT(this, "CustomCameraMovementManager::disable: null this");

	if(&CustomCameraMovementManager_dontFocus != this->focusFunction)
	{
		this->previousFocusFunction = this->focusFunction;
	}

	this->focusFunction = &CustomCameraMovementManager_dontFocus;
}

void CustomCameraMovementManager_enableFocusEasing(CustomCameraMovementManager this)
{
	ASSERT(this, "CustomCameraMovementManager::enableFocusEasing: null this");

	this->focusFunction = &CustomCameraMovementManager_doFocus;
	this->previousFocusFunction = this->focusFunction;
}

void CustomCameraMovementManager_disableFocusEasing(CustomCameraMovementManager this)
{
	ASSERT(this, "CustomCameraMovementManager::disableFocusEasing: null this");

	this->focusFunction = &CustomCameraMovementManager_doFocusWithNoEasing;
	this->previousFocusFunction = this->focusFunction;
}

void CustomCameraMovementManager_alertWhenTargetFocused(CustomCameraMovementManager this)
{
	ASSERT(this, "CustomCameraMovementManager::alertWhenTargetFocused: null this");

	if(&CustomCameraMovementManager_doFocusAndAlertWhenTargetReached != this->focusFunction)
	{
		this->previousFocusFunction = this->focusFunction;
	}

	this->focusFunction = &CustomCameraMovementManager_doFocusAndAlertWhenTargetReached;
}

void CustomCameraMovementManager_dontAlertWhenTargetFocused(CustomCameraMovementManager this)
{
	ASSERT(this, "CustomCameraMovementManager::dontAlertWhenTargetFocused: null this");

	this->focusFunction = this->previousFocusFunction;
}
