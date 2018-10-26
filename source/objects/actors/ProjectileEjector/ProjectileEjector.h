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

typedef struct ProjectileEjectorDefinition
{
	// the base animated entity
	AnimatedEntityDefinition animatedEntityDefinition;

	// projectile positioned entity
	PositionedEntity projectilePositionedEntityDefinition;

	// delay of the first projectile ejection (only relevant if initially active)
	u16 initialEjectDelay;

	// pause between projectile ejections
	u16 ejectDelay;

	// whether the ejector should be active on creation
	u8 initiallyActive;

	// maximum number of projectiles on screen at the same time
	u8 maxProjectiles;

	// name of animation to play on projectile ejection
	char* ejectAnimationName;

	// name of animation to play when idle
	char* idleAnimationName;

} ProjectileEjectorDefinition;

typedef const ProjectileEjectorDefinition ProjectileEjectorROMDef;


//---------------------------------------------------------------------------------------------------------
//											ENUMS
//---------------------------------------------------------------------------------------------------------

enum ProjectileEjectorEvents
{
	kEventProjectileEjected,
};


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

class ProjectileEjector : AnimatedEntity
{
	// definition pointer
	ProjectileEjectorDefinition* projectileEjectorDefinition;
	// ejection flag
	u8 active;

	void constructor(ProjectileEjectorDefinition* projectileEjectorDefinition, s16 id, s16 internalId, const char* const name);
	void ejectProjectile();
	bool isActive();
	void onEjectAnimationComplete();
	void setActive(bool active);
	override bool handleMessage(Telegram telegram);
	override void ready(bool recursive);
}


#endif
