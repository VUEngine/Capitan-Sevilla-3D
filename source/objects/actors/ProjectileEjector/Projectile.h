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
	int checkDelay;

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

	void constructor(ProjectileSpec* projectileSpec, s16 id, s16 internalId, const char* const name);
	void startMovement();
	bool canBeReused();
	void stop();
	void onHitAnimationComplete();
	override void ready(bool recursive);
	override bool handleMessage(Telegram telegram);
	override bool isVisible(int pad, bool recursive);
	override bool enterCollision(const CollisionInformation* collisionInformation);
}


#endif
