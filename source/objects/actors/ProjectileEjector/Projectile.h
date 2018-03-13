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

#ifndef PROJECTILE_H_
#define PROJECTILE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Actor.h>
#include <macros.h>
#include <Actor.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define PROJECTILE_EJECTOR_MAX_Y_POS					128
#define PROJECTILE_EJECTOR_DISPLACEMENT_CHECK_DELAY		500


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Projectile_METHODS(ClassName)																	\
		Actor_METHODS(ClassName)																		\

#define Projectile_SET_VTABLE(ClassName)																\
		Actor_SET_VTABLE(ClassName)																		\
		__VIRTUAL_SET(ClassName, Projectile, handleMessage);											\

__CLASS(Projectile);

#define Projectile_ATTRIBUTES																			\
		Actor_ATTRIBUTES																				\

//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

// allocator
__CLASS_NEW_DECLARE(Projectile, ActorDefinition* actorDefinition, s16 id, s16 internalId, const char* const name);

void Projectile_constructor(Projectile this, ActorDefinition* actorDefinition, s16 id, s16 internalId, const char* const name);
void Projectile_destructor(Projectile this);
void Projectile_startMovement(Projectile this);
void Projectile_stopMovement(Projectile this);
void Projectile_checkPosition(Projectile this);
bool Projectile_handleMessage(Projectile this, Telegram telegram);


#endif
