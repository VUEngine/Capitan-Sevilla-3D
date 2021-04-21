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
#include "HoverCar.h"


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern Sound HOVER_ENGINE_SND;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void HoverCar::constructor(EnemySpec* enemySpec, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(enemySpec, internalId, name);

	this->engineSound = NULL;
}

void HoverCar::destructor()
{
	if(!isDeleted(this->engineSound))
	{
		SoundWrapper::release(this->engineSound);
		this->engineSound = NULL;
	}

	// destroy the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void HoverCar::ready(bool recursive)
{
	// call base
	Base::ready(this, recursive);

	this->engineSound = SoundManager::getSound(
		SoundManager::getInstance(),
		&HOVER_ENGINE_SND,
		kPlayAll,
		(EventListener)HoverCar::onEngineSoundReleased,
		Object::safeCast(this)
	);

	if(!isDeleted(this->engineSound))
	{
		SoundWrapper::play(this->engineSound, (const Vector3D*)&this->transformation.globalPosition, kSoundWrapperPlaybackFadeIn);
	}
}

void HoverCar::onEngineSoundReleased(Object eventFirer __attribute__((unused)))
{
	NM_ASSERT(eventFirer == Object::safeCast(this->engineSound), "HoverCar::onEngineSoundReleased: no engine sound");

	this->engineSound = NULL;
}
