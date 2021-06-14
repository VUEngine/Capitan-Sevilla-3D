/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
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

typedef struct ProjectileEjectorSpec
{
	// the base animated entity
	AnimatedEntitySpec animatedEntitySpec;

	// projectile positioned entity
	PositionedEntity projectilePositionedEntitySpec;

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

} ProjectileEjectorSpec;

typedef const ProjectileEjectorSpec ProjectileEjectorROMSpec;


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
	// spec pointer
	ProjectileEjectorSpec* projectileEjectorSpec;
	// ejection flag
	u8 active;
	// created projectiles counter
	u8 createdProjectiles;
	// cooldown flag
	bool coolingDown;

	void constructor(ProjectileEjectorSpec* projectileEjectorSpec, s16 internalId, const char* const name);
	void ejectProjectile();
	bool isActive();
	bool canEject();
	void onEjectAnimationComplete();
	void setActive(bool active);
	override bool handleMessage(Telegram telegram);
	override void ready(bool recursive);
}


#endif
