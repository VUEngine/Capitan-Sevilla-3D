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

#include <CameraTriggerEntity.h>
#include <CollisionManager.h>
#include <Optics.h>
#include <Shape.h>
#include <Camera.h>
#include <PlatformerLevelState.h>
#include <CustomCameraMovementManager.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

// define the CameraTriggerEntity
__CLASS_DEFINITION(CameraTriggerEntity, Entity);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(CameraTriggerEntity, CameraTriggerEntityDefinition* cameraEntityDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(CameraTriggerEntity, cameraEntityDefinition, id, internalId, name);

// class's constructor
void CameraTriggerEntity_constructor(CameraTriggerEntity this, CameraTriggerEntityDefinition* cameraEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	ASSERT(this, "CameraTriggerEntity::constructor: null this");
	ASSERT(cameraEntityDefinition, "CameraTriggerEntity::constructor: null definition");

	// construct base object
	__CONSTRUCT_BASE(Entity, (EntityDefinition*)cameraEntityDefinition, id, internalId, name);

	this->overridePositionFlag.x = false;
	this->overridePositionFlag.y = false;
	this->overridePositionFlag.z = false;
}

// class's destructor
void CameraTriggerEntity_destructor(CameraTriggerEntity this)
{
	ASSERT(this, "CameraTriggerEntity::destructor: null this");

	Camera_setFocusGameEntity(Camera_getInstance(), NULL);

	// destroy the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

void CameraTriggerEntity_transform(CameraTriggerEntity this, const Transformation* environmentTransform, u8 invalidateTransformationFlag)
{
	ASSERT(this, "CameraTriggerEntity::transform: null this");

	Vector3D currentGlobalPosition = this->transformation.globalPosition;

	__CALL_BASE_METHOD(Container, transform, this, environmentTransform, invalidateTransformationFlag);

	if(this->overridePositionFlag.x)
	{
		this->transformation.globalPosition.x = currentGlobalPosition.x;
	}

	if(this->overridePositionFlag.y)
	{
		this->transformation.globalPosition.y = currentGlobalPosition.y;
	}

	Entity_transformShapes(__SAFE_CAST(Entity, this));

//	__VIRTUAL_CALL(Shape, show, VirtualList_front(this->shapes));
}

void CameraTriggerEntity_setOverridePositionFlag(CameraTriggerEntity this, Vector3DFlag overridePositionFlag)
{
	ASSERT(this, "CameraTriggerEntity::setOverridePositionFlag: null this");

	Container_invalidateGlobalPosition(__SAFE_CAST(Container, this));

	Transformation* environmentTransform = Container_getTransform(this->parent);

	// don't lock yet, allow the global position to be calculated before locking
	this->overridePositionFlag.y = false;
	CameraTriggerEntity_transform(this, environmentTransform, __INVALIDATE_TRANSFORMATION);

	this->overridePositionFlag = overridePositionFlag;
}

Vector3DFlag CameraTriggerEntity_getOverridePositionFlag(CameraTriggerEntity this)
{
	ASSERT(this, "CameraTriggerEntity::getOverridePositionFlag: null this");

	return this->overridePositionFlag;
}
