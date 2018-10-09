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


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Game.h>
#include <CustomCameraEffectManager.h>
#include <SoundManager.h>
#include "Enemy.h"

//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern const u16 FIRE_SND[];


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void Enemy::constructor(EnemyDefinition* enemyDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor((MovingOneWayEntityDefinition*)&enemyDefinition->movingOneWayEntityDefinition, id, internalId, name);

	// init members
	this->energy = enemyDefinition->energy;
}

void Enemy::destructor()
{
	// destroy the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void Enemy::takeHit(u8 power)
{
	// start short screen shake
	//Camera::startEffect(Camera::getInstance(), kShake, 100);

	// play sound
	SoundManager::playFxSound(SoundManager::getInstance(), FIRE_SND, this->transformation.globalPosition);

	// reduce energy
	if(power < this->energy)
	{
		this->energy -= power;

		// flash
		// TODO
	}
	else
	{
		Enemy::die(this);
	}
}

void Enemy::die()
{
	Container::deleteMyself(Container::safeCast(this));
}