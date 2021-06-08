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

// Instrument: ;
const u16 TITLE_TRACK_1[] =
{
  PAU, E_5, PAU, B_4, PAU, D_5, PAU, E_5, PAU, B_4, PAU, D_5, PAU, E_5, PAU, G_5, PAU, E_5, PAU, D_5, PAU, B_4, PAU, E_5, PAU, B_4, PAU, D_5, PAU, E_5, PAU, B_4, PAU, D_5, PAU, E_5, PAU, A_5, PAU, G_5, PAU, E_5, PAU, D_5, PAU, E_5, ENDSOUND,
  1, 342, 18, 114, 6, 342, 18, 1416, 24, 114, 6, 342, 18, 114, 6, 342, 18, 114, 6, 342, 18, 114, 6, 342, 18, 114, 6, 342, 18, 1416, 24, 114, 6, 342, 18, 114, 6, 342, 18, 114, 6, 342, 18, 114, 6, 456,
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12
};

// Instrument: ;
const u16 TITLE_TRACK_2[] =
{
  PAU, B_4, PAU, B_4, PAU, CS5, PAU, CS5, PAU, D_5, PAU, D_5, PAU, CS5, PAU, D_5, PAU, B_4, PAU, B_4, PAU, CS5, PAU, CS5, PAU, D_5, PAU, D_5, PAU, CS5, PAU, D_5, PAU, GS4, ENDSOUND,
  1, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 342, 18, 594, 6, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 342, 18, 594, 6, 456,
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12
};

// Instrument: ;
const u16 TITLE_TRACK_3[] =
{
  PAU, E_3, PAU, E_3, PAU, E_3, PAU, E_3, PAU, E_3, PAU, E_3, PAU, E_3, PAU, E_3, PAU, E_3, PAU, E_3, PAU, E_3, PAU, E_3, PAU, E_3, PAU, E_3, PAU, E_3, PAU, E_3, PAU, E_3, ENDSOUND,
  1, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456,
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12
};


SoundChannelConfigurationROM TITLE_CHANNEL_1_CONFIGURATION =
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
	squareWaveForm,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelROM TITLE_CHANNEL_1 =
{
	/// Configuration
	(SoundChannelConfiguration*)&TITLE_CHANNEL_1_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const u8*)TITLE_TRACK_1
	}
};

SoundChannelConfigurationROM TITLE_CHANNEL_2_CONFIGURATION =
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
	squareWaveForm,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelROM TITLE_CHANNEL_2 =
{
	/// Configuration
	(SoundChannelConfiguration*)&TITLE_CHANNEL_2_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const u8*)TITLE_TRACK_2
	}
};

SoundChannelConfigurationROM TITLE_CHANNEL_3_CONFIGURATION =
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

SoundChannelROM TITLE_CHANNEL_3 =
{
	/// Configuration
	(SoundChannelConfiguration*)&TITLE_CHANNEL_3_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const u8*)TITLE_TRACK_3
	}
};

SoundChannelROM* TITLE_CHANNELS[] =
{
	&TITLE_CHANNEL_1,
	&TITLE_CHANNEL_2,
	&TITLE_CHANNEL_3,
	NULL
};

SoundROM TITLE_SONG =
{
	/// Name
	"Title",

	/// Play in loop
	true,

	/// Target timer resolution in us
	1060,

	/// Tracks
	(SoundChannel**)TITLE_CHANNELS
};
