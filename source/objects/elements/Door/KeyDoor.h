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

#ifndef KEY_DOOR_H_
#define KEY_DOOR_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Door.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define KeyDoor_METHODS(ClassName)																		\
		Door_METHODS(ClassName)																			\

#define KeyDoor_SET_VTABLE(ClassName)																	\
		Door_SET_VTABLE(ClassName)																		\
		__VIRTUAL_SET(ClassName, KeyDoor, ready);														\
		__VIRTUAL_SET(ClassName, KeyDoor, hasDestination);												\
		__VIRTUAL_SET(ClassName, KeyDoor, setOverlapping);												\
		__VIRTUAL_SET(ClassName, KeyDoor, unsetOverlapping);											\
		__VIRTUAL_SET(ClassName, KeyDoor, canEnter);													\
		__VIRTUAL_SET(ClassName, KeyDoor, getHintType);													\

__CLASS(KeyDoor);

#define KeyDoor_ATTRIBUTES																				\
		/* it is derived from */																		\
		Door_ATTRIBUTES																					\

typedef const DoorDefinition KeyDoorDefinition;
typedef const KeyDoorDefinition KeyDoorROMDef;


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(KeyDoor, AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name);

void KeyDoor_constructor(KeyDoor this, AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name);
void KeyDoor_destructor(KeyDoor this);
void KeyDoor_ready(KeyDoor this, bool recursive);
bool KeyDoor_hasDestination(KeyDoor this);
void KeyDoor_setOverlapping(KeyDoor this);
void KeyDoor_unsetOverlapping(KeyDoor this);
bool KeyDoor_canEnter(KeyDoor this);
u32 KeyDoor_getHintType(KeyDoor this);


#endif
