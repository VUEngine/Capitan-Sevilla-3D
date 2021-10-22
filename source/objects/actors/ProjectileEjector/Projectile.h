/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef PROJECTILE_H_
#define PROJECTILE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Actor.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef struct ProjectileSpec
{
	// the base animated entity
	ActorSpec actorSpec;

	// velocity when moving
	Velocity velocity;

	// position relative to ejector
	Vector3D position;

	// max position relative to ejector before position reset
	Vector3D maxDistance;

	// delay between position checks (-1 to disable)
	int32 checkDelay;

} ProjectileSpec;

typedef const ProjectileSpec ProjectileROMSpec;


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

class Projectile : Actor
{
	// spec pointer
	ProjectileSpec* projectileSpec;
	// position at time of ejection
	Vector3D originalPosition;

	void constructor(ProjectileSpec* projectileSpec, int16 internalId, const char* const name);
	void startMovement();
	bool canBeReused();
	void stop(bool hide);
	void onHitAnimationComplete();
	override void ready(bool recursive);
	override bool handleMessage(Telegram telegram);
	override bool enterCollision(const CollisionInformation* collisionInformation);
}


#endif
