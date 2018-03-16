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

#ifndef PROJECTILE_EJECTOR_H_
#define PROJECTILE_EJECTOR_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AnimatedEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define PROJECTILE_EJECTOR_INITIAL_SHOOT_DELAY 1200
#define PROJECTILE_EJECTOR_SHOOT_DELAY 2400


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define ProjectileEjector_METHODS(ClassName)															\
		AnimatedEntity_METHODS(ClassName)																\

#define ProjectileEjector_SET_VTABLE(ClassName)															\
		AnimatedEntity_SET_VTABLE(ClassName)															\
		__VIRTUAL_SET(ClassName, ProjectileEjector, handleMessage);										\
		__VIRTUAL_SET(ClassName, ProjectileEjector, ready);												\

__CLASS(ProjectileEjector);

#define ProjectileEjector_ATTRIBUTES																	\
		AnimatedEntity_ATTRIBUTES																		\


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(ProjectileEjector, AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name);

void ProjectileEjector_constructor(ProjectileEjector this, AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name);
void ProjectileEjector_destructor(ProjectileEjector this);
bool ProjectileEjector_handleMessage(ProjectileEjector this, Telegram telegram);
void ProjectileEjector_ready(ProjectileEjector this, bool recursive);
void ProjectileEjector_shoot(ProjectileEjector this);
void ProjectileEjector_onShootAnimationComplete(ProjectileEjector this);


#endif
