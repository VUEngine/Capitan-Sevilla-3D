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

#ifndef DOOR_H_
#define DOOR_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AnimatedEntity.h>
#include <PlatformerLevelState.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

#define DOOR_OVERLAPPING_CHECK_DELAY	250


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Door_METHODS(ClassName)																			\
		AnimatedEntity_METHODS(ClassName)															\
		__VIRTUAL_DEC(ClassName, bool, hasDestination);													\
		__VIRTUAL_DEC(ClassName, void, setOverlapping);													\
		__VIRTUAL_DEC(ClassName, void, unsetOverlapping);												\
		__VIRTUAL_DEC(ClassName, bool, canEnter);														\
		__VIRTUAL_DEC(ClassName, u32, getHintType);														\

#define Door_SET_VTABLE(ClassName)																		\
		AnimatedEntity_SET_VTABLE(ClassName)															\
		__VIRTUAL_SET(ClassName, Door, setExtraInfo);													\
		__VIRTUAL_SET(ClassName, Door, ready);															\
		__VIRTUAL_SET(ClassName, Door, handleMessage);													\
		__VIRTUAL_SET(ClassName, Door, hasDestination);													\
		__VIRTUAL_SET(ClassName, Door, setOverlapping);													\
		__VIRTUAL_SET(ClassName, Door, unsetOverlapping);												\
		__VIRTUAL_SET(ClassName, Door, canEnter);														\
		__VIRTUAL_SET(ClassName, Door, getHintType);													\

__CLASS(Door);

#define Door_ATTRIBUTES																					\
		/* it is derived from */																		\
		AnimatedEntity_ATTRIBUTES																		\
		/* destination of door */																		\
		StageEntryPointDefinition* destinationDefinition;												\


typedef const AnimatedEntityDefinition DoorDefinition;
typedef const DoorDefinition DoorROMDef;


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(Door, AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name);

void Door_constructor(Door this, AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name);
void Door_destructor(Door this);
StageEntryPointDefinition* Door_getExtraInfo(Door this);
void Door_setExtraInfo(Door this, void* extraInfo);
void Door_ready(Door this, bool recursive);
bool Door_handleMessage(Door this, Telegram telegram);
bool Door_hasDestination(Door this);
void Door_onOverlapping(Door this);
void Door_setOverlapping(Door this);
void Door_unsetOverlapping(Door this);
bool Door_canEnter(Door this);
u32 Door_getHintType(Door this);


#endif
