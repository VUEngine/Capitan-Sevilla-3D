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

#define ENGINE_FREQ				MINIMUM_AUDIBLE_NOTE + 0x0AA + 256
#define ENGINE_DURATION			17
#define ENGINE_VOLUME_DELTA		15


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

const u16 EngineSoundTrack1[] =
{
  0x016 + ENGINE_FREQ, 0x024 + ENGINE_FREQ, 0x032 + ENGINE_FREQ, 0x040 + ENGINE_FREQ, 0x032 + ENGINE_FREQ, 0x024 + ENGINE_FREQ, 0x016 + ENGINE_FREQ, ENDSOUND,
  ENGINE_DURATION * 4, ENGINE_DURATION * 3, ENGINE_DURATION * 2, ENGINE_DURATION * 1, ENGINE_DURATION * 2, ENGINE_DURATION * 3, ENGINE_DURATION * 4,
  ENGINE_VOLUME_DELTA, ENGINE_VOLUME_DELTA, ENGINE_VOLUME_DELTA, ENGINE_VOLUME_DELTA, ENGINE_VOLUME_DELTA, ENGINE_VOLUME_DELTA, ENGINE_VOLUME_DELTA,
};

SoundChannelConfigurationROM ENGINE_SOUND_CHANNEL_1_CONFIGURATION =
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
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelROM ENGINE_SOUND_CHANNEL_1 =
{
	/// Configuration
	(SoundChannelConfiguration*)&ENGINE_SOUND_CHANNEL_1_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const u8*)EngineSoundTrack1
	}
};


SoundChannelROM* ENGINE_SOUND_CHANNELS[] =
{
	&ENGINE_SOUND_CHANNEL_1,
	NULL
};

SoundROM ENGINE_SND =
{
	/// Name
	"Engine",

	/// Play in loop
	true,

	/// Target timer resolution in us
	3000,

	/// Tracks
	(SoundChannel**)ENGINE_SOUND_CHANNELS
};