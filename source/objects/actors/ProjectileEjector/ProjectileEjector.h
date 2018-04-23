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
		/* definition pointer */																		\
		ProjectileEjectorDefinition* projectileEjectorDefinition;										\
		/* number of the current projectile to eject */													\
		u8 currentProjectileIndex;																		\


typedef struct ProjectileEjectorDefinition
{
	// the base animated entity
	AnimatedEntityDefinition animatedEntityDefinition;

	// projectile positioned entity
	PositionedEntity projectilePositionedEntityDefinition;

	// delay of the first projectile ejection
	u16 initialEjectDelay;

	// pause between projectile ejections
	u16 ejectDelay;

	// maximum number of projectiles on screen at the same time
	u8 maxProjectiles;

	// name of animation to play on projectile ejection
	char* ejectAnimationName;

	// name of animation to play when idle
	char* idleAnimationName;

} ProjectileEjectorDefinition;

typedef const ProjectileEjectorDefinition ProjectileEjectorROMDef;


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(ProjectileEjector, ProjectileEjectorDefinition* projectileEjectorDefinition, s16 id, s16 internalId, const char* const name);

void ProjectileEjector_constructor(ProjectileEjector this, ProjectileEjectorDefinition* projectileEjectorDefinition, s16 id, s16 internalId, const char* const name);
void ProjectileEjector_destructor(ProjectileEjector this);
bool ProjectileEjector_handleMessage(ProjectileEjector this, Telegram telegram);
void ProjectileEjector_ready(ProjectileEjector this, bool recursive);
void ProjectileEjector_ejectProjectile(ProjectileEjector this);
void ProjectileEjector_onEjectAnimationComplete(ProjectileEjector this);


#endif
