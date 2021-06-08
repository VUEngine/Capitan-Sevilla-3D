/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2019 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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

#include <SoundManager.h>
#include <WaveForms.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define LIFT_FREQ				MINIMUM_AUDIBLE_NOTE + 480
#define LIFT_DURATION			140
#define LIFT_VOLUME_DELTA		6


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

const u16 LIFT_TRACK_1[] =
{
  PAU, 0x016 + LIFT_FREQ, 0x024 + LIFT_FREQ, 0x032 + LIFT_FREQ, 0x040 + LIFT_FREQ, 0x032 + LIFT_FREQ, 0x024 + LIFT_FREQ, 0x016 + LIFT_FREQ, ENDSOUND,
  50, LIFT_DURATION * 4, LIFT_DURATION * 3, LIFT_DURATION * 2, LIFT_DURATION * 1, LIFT_DURATION * 2, LIFT_DURATION * 3, LIFT_DURATION * 4,
  0, LIFT_VOLUME_DELTA, LIFT_VOLUME_DELTA, LIFT_VOLUME_DELTA, LIFT_VOLUME_DELTA, LIFT_VOLUME_DELTA, LIFT_VOLUME_DELTA, LIFT_VOLUME_DELTA,
};

SoundChannelConfigurationROM LIFT_CHANNEL_1_CONFIGURATION =
{
	/// kMIDI, kPCM
	kMIDI,

	/// SxINT
	0x00,

	/// Volume SxLRV
	0x00,

	/// SxRAM (this is overrode by the SoundManager)
	0x00,

	/// SxEV0
	0xF0,

	/// SxEV1
	0x00,

	/// SxFQH
	0x00,

	/// SxFQL
	0x00,

	/// Ch. 5 only
	0x00,

	/// Waveform data pointer
	engineWaveForm,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelModulation,

	/// Volume
	__SOUND_LR
};

SoundChannelROM LIFT_CHANNEL_1 =
{
	/// Configuration
	(SoundChannelConfiguration*)&LIFT_CHANNEL_1_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const u8*)LIFT_TRACK_1
	}
};


SoundChannelROM* LIFT_CHANNELS[] =
{
	&LIFT_CHANNEL_1,
	NULL
};

SoundROM LIFT_SND =
{
	/// Name
	"Lift",

	/// Play in loop
	true,

	/// Target timer resolution in us
	3000,

	/// Tracks
	(SoundChannel**)LIFT_CHANNELS
};