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

#ifndef COLLISION_H_
#define COLLISION_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Entity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Collision_METHODS(ClassName)																	\
		Entity_METHODS(ClassName)																		\

#define Collision_SET_VTABLE(ClassName)																	\
		Entity_SET_VTABLE(ClassName)																	\
		__VIRTUAL_SET(ClassName, Collision, setExtraInfo);												\
		__VIRTUAL_SET(ClassName, Collision, initialTransform);											\

__CLASS(Collision);

#define Collision_ATTRIBUTES																			\
		Entity_ATTRIBUTES																				\


typedef const EntityDefinition CollisionDefinition;
typedef const CollisionDefinition CollisionROMDef;


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(Collision, EntityDefinition* inGameEntityDefinition, s16 id, s16 internalId, const char* const name);

void Collision_constructor(Collision this, EntityDefinition* inGameEntityDefinition, s16 id, s16 internalId, const char* const name);
void Collision_destructor(Collision this);
void Collision_setExtraInfo(Collision this, void* extraInfo);
void Collision_initialTransform(Collision this, Transformation* environmentTransform, u32 recursive);


#endif
