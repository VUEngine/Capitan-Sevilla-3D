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
#include <MIDI.h>


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// Instrument: 0 patchchange ch: 1 electric guitar(jazz);
const u16 GAME_OVER_TRACK_1[] =
{
  PAU, GS5, PAU, GS5, PAU, B_5, PAU, GS5, PAU, B_5, PAU, A_5, PAU, A_5, PAU, CS6, PAU, A_5, PAU, CS6, PAU, B_5, PAU, B_5, PAU, E_6, PAU, DS6, PAU, CS6, PAU, B_5, PAU, ENDSOUND,
  1, 94, 2, 46, 2, 94, 2, 46, 2, 94, 2, 94, 2, 46, 2, 94, 2, 46, 2, 94, 2, 94, 2, 46, 2, 94, 2, 46, 2, 94, 2, 94, 96,
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};

// Instrument: 0 patchchange ch: 2 electric guitar(jazz);
const u16 GAME_OVER_TRACK_2[] =
{
  PAU, E_4, PAU, E_4, PAU, GS4, PAU, E_4, PAU, GS4, PAU, FS4, PAU, FS4, PAU, A_4, PAU, FS4, PAU, A_4, PAU, GS4, PAU, GS4, PAU, CS5, PAU, B_4, PAU, A_4, PAU, E_4, PAU, B_3, PAU, GS3, PAU, E_3, ENDSOUND,
  1, 94, 2, 46, 2, 94, 2, 46, 2, 94, 2, 94, 2, 46, 2, 94, 2, 46, 2, 94, 2, 94, 2, 46, 2, 94, 2, 46, 2, 94, 2, 46, 2, 46, 2, 46, 2, 46,
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};



SoundChannelConfigurationROM GAME_OVER_CHANNEL_1_CONFIGURATION =
{
	/// kMIDI, kPCM
	kMIDI,

	/// SxINT
	0x9F,

	/// Volume SxLRV
	0xFF,

	/// SxRAM (this is overrode by the SoundManager)
	0x00,

	/// SxEV0
	0x80,

	/// SxEV1
	0x01,

	/// SxFQH
	0x00,

	/// SxFQL
	0x00,

	/// Ch. 5 only
	0x00,

	/// Waveform data pointer
	triangleWaveForm,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelROM GAME_OVER_CHANNEL_1 =
{
	/// Configuration
	(SoundChannelConfiguration*)&GAME_OVER_CHANNEL_1_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const u8*)GAME_OVER_TRACK_1
	}
};

SoundChannelConfigurationROM GAME_OVER_CHANNEL_2_CONFIGURATION =
{
	/// kMIDI, kPCM
	kMIDI,

	/// SxINT
	0x9F,

	/// Volume SxLRV
	0xFF,

	/// SxRAM (this is overrode by the SoundManager)
	0x00,

	/// SxEV0
	0x80,

	/// SxEV1
	0x01,

	/// SxFQH
	0x00,

	/// SxFQL
	0x00,

	/// Ch. 5 only
	0x00,

	/// Waveform data pointer
	trumpetWaveForm,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelROM GAME_OVER_CHANNEL_2 =
{
	/// Configuration
	(SoundChannelConfiguration*)&GAME_OVER_CHANNEL_2_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const u8*)GAME_OVER_TRACK_2
	}
};


SoundChannelROM* GAME_OVER_CHANNELS[] =
{
	&GAME_OVER_CHANNEL_1,
	&GAME_OVER_CHANNEL_2,
	NULL
};

SoundROM GAME_OVER_SND =
{
	/// Name
	"GameOver",

	/// Play in loop
	false,

	/// Target timer resolution in us
	2240,

	/// Tracks
	(SoundChannel**)GAME_OVER_CHANNELS
};
