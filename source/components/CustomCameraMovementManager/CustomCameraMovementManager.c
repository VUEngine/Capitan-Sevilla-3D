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
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void CustomCameraMovementManager::constructor()
{
	// construct base object
	Base::constructor();

	this->positionFlag.x = 0;
	this->positionFlag.y = 0;
	this->positionFlag.z = 0;

	this->focusFunction = &CustomCameraMovementManager::doFocus;
	this->previousFocusFunction = this->focusFunction;

	this->camera = Camera::getInstance();

	NM_ASSERT(this->camera, "CustomCameraMovementManager::constructor: null this->camera");
}

void CustomCameraMovementManager::destructor()
{
	// destroy base
	Base::destructor();
}

// center world's this->camera in function of focus actor's position
void CustomCameraMovementManager::focus(u32 checkIfFocusEntityIsMoving __attribute__ ((unused)))
{
	this->focusFunction(this, checkIfFocusEntityIsMoving, false);
}

bool CustomCameraMovementManager::doFocusWithNoEasing(u32 checkIfFocusEntityIsMoving __attribute__ ((unused)), u32 introFocusing __attribute__ ((unused)))
{
	Vector3D focusEntityPosition = Camera::getFocusEntityPosition(this->camera);
	Direction direction = Entity::getDirection(Camera::getFocusEntity(this->camera));

	Vector3D cameraPosition =
	{
		focusEntityPosition.x + direction.x * Camera::getFocusEntityPositionDisplacement(this->camera).x - __PIXELS_TO_METERS(__SCREEN_WIDTH / 2),
		focusEntityPosition.y + Camera::getFocusEntityPositionDisplacement(this->camera).y - __PIXELS_TO_METERS(__SCREEN_HEIGHT / 2),
		0
	};

	Camera::setPosition(this->camera, cameraPosition);

	return true;
}

// center world's this->camera in function of focus actor's position
bool CustomCameraMovementManager::dontFocus(u32 checkIfFocusEntityIsMoving __attribute__ ((unused)), u32 introFocusing __attribute__ ((unused)))
{
	return false;
}

// center world's this->camera in function of focus actor's position
bool CustomCameraMovementManager::doFocus(u32 checkIfFocusEntityIsMoving __attribute__ ((unused)), u32 introFocusing __attribute__ ((unused)))
{
	// if focusEntity is defined
	if(!Camera::getFocusEntity(this->camera))
	{
		return false;
	}

	Actor focusActor = Actor::safeCast(Camera::getFocusEntity(this->camera));

	Direction direction = Entity::getDirection(Entity::safeCast(focusActor));

	Vector3D cameraNewPosition = Camera::getPosition(this->camera);

	Vector3DFlag reachedTargetFlag = {true, true, true};

	Vector3D focusEntityPosition = Camera::getFocusEntityPosition(this->camera);
	Vector3D focusEntityPositionDisplacement = Camera::getFocusEntityPositionDisplacement(this->camera);

	Vector3D position3D = Vector3D::getRelativeToCamera(focusEntityPosition);
	PixelVector position2D = Vector3D::projectToPixelVector(position3D, 0);

	Size stageSize = Camera::getStageSize(this->camera);

	{
		bool focusEntityOutOfBounds = (unsigned)(position2D.x - _cameraFrustum->x0 - SCREEN_WIDTH_REDUCTION) > (unsigned)(_cameraFrustum->x1 - _cameraFrustum->x0 - SCREEN_WIDTH_REDUCTION);

		if(this->positionFlag.x | focusEntityOutOfBounds)
		{
			// calculate the target position
			fix10_6 horizontalPosition = cameraNewPosition.x;
			fix10_6 horizontalTarget = focusEntityPosition.x + direction.x * focusEntityPositionDisplacement.x - __PIXELS_TO_METERS(__SCREEN_WIDTH / 2);

			fix10_6 easingDisplacement = __PIXELS_TO_METERS(7);

			if(introFocusing)
			{
				easingDisplacement = __PIXELS_TO_METERS(1);
			}

			reachedTargetFlag.x = false;

			if(horizontalPosition + easingDisplacement < horizontalTarget)
			{
				cameraNewPosition.x += easingDisplacement;
			}
			else if(horizontalPosition - easingDisplacement > horizontalTarget)
			{
				cameraNewPosition.x -= easingDisplacement;
			}
			else
			{
				cameraNewPosition.x = horizontalTarget;
				reachedTargetFlag.x = true;
			}

			if(0 > cameraNewPosition.x)
			{
				reachedTargetFlag.x = true;
			}
			else if(stageSize.x < cameraNewPosition.x + __PIXELS_TO_METERS(__SCREEN_WIDTH))
			{
				reachedTargetFlag.x = true;
			}
		}
	}

	{
		bool focusEntityOutOfBounds = position2D.y > _cameraFrustum->y1 - SCREEN_HEIGHT_REDUCTION || position2D.y < _cameraFrustum->y0 + SCREEN_HEIGHT_REDUCTION / 4;

		if(this->positionFlag.y | focusEntityOutOfBounds)
		{
			// calculate the target position
			fix10_6 verticalPosition = cameraNewPosition.y;
			fix10_6 verticalTarget = focusEntityPosition.y + focusEntityPositionDisplacement.y - __PIXELS_TO_METERS(__SCREEN_HEIGHT / 2);

			fix10_6 downEasingDisplacement = __PIXELS_TO_METERS(3);
			fix10_6 upEasingDisplacement = __PIXELS_TO_METERS(3);

			if(introFocusing)
			{
				downEasingDisplacement = __PIXELS_TO_METERS(1);
				upEasingDisplacement = __PIXELS_TO_METERS(1);
			}
			else
			{
				Velocity velocity = Actor::getVelocity(focusActor);

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
				cameraNewPosition.y += downEasingDisplacement;
			}
			else if(verticalPosition - upEasingDisplacement > verticalTarget)
			{
				cameraNewPosition.y -= upEasingDisplacement;
			}
			else
			{
				cameraNewPosition.y = verticalTarget;
				this->positionFlag.y = false;
				reachedTargetFlag.y = true;
			}

			if(0 > cameraNewPosition.y)
			{
				reachedTargetFlag.y = true;
			}
			else if(stageSize.y < cameraNewPosition.y + __PIXELS_TO_METERS(__SCREEN_HEIGHT))
			{
				reachedTargetFlag.y = true;
			}
		}
	}

	Camera::setPosition(this->camera, cameraNewPosition);

	if(reachedTargetFlag.x && reachedTargetFlag.y)
	{
		return true;
	}

	return false;
}

// center world's this->camera in function of focus actor's position
bool CustomCameraMovementManager::doFocusAndAlertWhenTargetReached(u32 checkIfFocusEntityIsMoving __attribute__ ((unused)), u32 introFocusing __attribute__ ((unused)))
{
	if(CustomCameraMovementManager::doFocus(this, checkIfFocusEntityIsMoving, true))
	{
		Object::fireEvent(EventManager::getInstance(), kEventScreenFocused);

		return true;
	}

	return false;
}

void CustomCameraMovementManager::setPositionFlag(Vector3DFlag positionFlag)
{
	this->positionFlag = positionFlag;
}

Vector3DFlag CustomCameraMovementManager::getPositionFlag()
{
	return this->positionFlag;
}

void CustomCameraMovementManager::enable()
{
	this->focusFunction = this->previousFocusFunction;
	this->previousFocusFunction = this->focusFunction;
}

void CustomCameraMovementManager::disable()
{
	if(&CustomCameraMovementManager::dontFocus != this->focusFunction)
	{
		this->previousFocusFunction = this->focusFunction;
	}

	this->focusFunction = &CustomCameraMovementManager::dontFocus;
}

void CustomCameraMovementManager::enableFocusEasing()
{
	this->focusFunction = &CustomCameraMovementManager::doFocus;
	this->previousFocusFunction = this->focusFunction;
}

void CustomCameraMovementManager::disableFocusEasing()
{
	this->focusFunction = &CustomCameraMovementManager::doFocusWithNoEasing;
	this->previousFocusFunction = this->focusFunction;
}

void CustomCameraMovementManager::alertWhenTargetFocused()
{
	if(&CustomCameraMovementManager::doFocusAndAlertWhenTargetReached != this->focusFunction)
	{
		this->previousFocusFunction = this->focusFunction;
	}

	this->focusFunction = &CustomCameraMovementManager::doFocusAndAlertWhenTargetReached;
}

void CustomCameraMovementManager::dontAlertWhenTargetFocused()
{
	this->focusFunction = this->previousFocusFunction;
}
