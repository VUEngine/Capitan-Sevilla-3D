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

#ifndef CUSTOM_CAMERA_EFFECT_MANAGER_H_
#define CUSTOM_CAMERA_EFFECT_MANAGER_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <CameraEffectManager.h>
#include <Telegram.h>
#include <Entity.h>


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

// delay between camera movements during shaking effect (in ms)
#define MINIMUM_SHAKE_DELAY				20
#define SHAKE_DELAY_DELTA				60
#define CAMERA_PULSATE_DELAY			270

enum CustomCameraFX
{
	kShake = kCameraLastFX,
	kScreenPulsate
};


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

singleton class CustomCameraEffectManager : CameraEffectManager
{
	// temporary variable to hold the focus entity during shaking fx
	Entity tempFocusEntity;
	// last offset set by shake function
	Vector3D lastShakeOffset;
	// time left in current shaking fx (in ms)
	int shakeTimeLeft;
	// values to load on next pulsate fx step
	u8 pulsateNextStep;

	static CustomCameraEffectManager getInstance();
	override void startEffect(int effect, va_list args);
	override void stopEffect(int effect);
	override bool handleMessage(Telegram telegram);
}


#endif
