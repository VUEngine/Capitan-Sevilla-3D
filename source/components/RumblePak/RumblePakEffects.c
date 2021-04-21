/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2017 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <RumblePakEffects.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S DECLARATIONS
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------




RumbleEffectROMSpec RumbleEffectJump =
{
	/// Effect #
	9,
	/// Frequency
	__RUMBLE_FREQ_240HZ,
	/// Sustain+
	255,
	/// Sustain-
	255,
	/// Overdrive
	255,
	/// Break
	255,
	/// Stop before starting
	true
};

RumbleEffectROMSpec RumbleEffectLand =
{
	/// Effect #
	8,
	/// Frequency
	__RUMBLE_FREQ_240HZ,
	/// Sustain+
	255,
	/// Sustain-
	255,
	/// Overdrive
	255,
	/// Break
	255,
	/// Stop before starting
	true
};

RumbleEffectROMSpec RumbleEffectSpit =
{
	/// Effect #
	9,
	/// Frequency
	__RUMBLE_FREQ_160HZ,
	/// Sustain+
	255,
	/// Sustain-
	255,
	/// Overdrive
	255,
	/// Break
	255,
	/// Stop before starting
	true
};

RumbleEffectROMSpec RumbleEffectTakeLightDamage =
{
	/// Effect #
	19,
	/// Frequency
	__RUMBLE_FREQ_240HZ,
	/// Sustain+
	255,
	/// Sustain-
	255,
	/// Overdrive
	255,
	/// Break
	255,
	/// Stop before starting
	true
};

/// Acceleration rumble effect
RumbleEffectROMSpec RumbleEffectDieLight =
{
	/// Effect #
	17,
	/// Frequency
	__RUMBLE_FREQ_240HZ,
	/// Sustain+
	255,
	/// Sustain-
	255,
	/// Overdrive
	255,
	/// Break
	255,
	/// Stop before starting
	true
};


RumbleEffectROMSpec RumbleEffectTakeStrongDamage =
{
	/// Effect #
	12,
	/// Frequency
	__RUMBLE_FREQ_240HZ,
	/// Sustain+
	255,
	/// Sustain-
	255,
	/// Overdrive
	255,
	/// Break
	255,
	/// Stop before starting
	true
};

/// Acceleration rumble effect
RumbleEffectROMSpec RumbleEffectDieStrong =
{
	/// Effect #
	12,
	/// Frequency
	__RUMBLE_FREQ_160HZ,
	/// Sustain+
	255,
	/// Sustain-
	255,
	/// Overdrive
	255,
	/// Break
	255,
	/// Stop before starting
	true

};

/// Acceleration rumble effect
RumbleEffectROMSpec RumbleEffectReload =
{
	/// Effect #
	62,
	/// Frequency
	__RUMBLE_FREQ_240HZ,
	/// Sustain+
	80,
	/// Sustain-
	80,
	/// Overdrive
	255,
	/// Break
	255,
	/// Stop before starting
	true
};
