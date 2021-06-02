/* VUEngine - Virtual Utopia Hit <http://vuengine.planetvb.com/>
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

// Instrument: 0 patchchange ch: 1 accoridan;
const u16 captainTrack1[] =
{
  DS5, PAU, F_5, DS5, F_5, DS5, PAU, AS5, G_5, AS5, DS5, AS5, PAU, C_6, B_5, C_6, B_5, C_6, PAU, F_6, AS5, PAU, GS5, AS5, C_6, GS5, PAU, F_5, AS5, G_5, PAU, GS5, AS5, G_5, DS5, PAU, G_5, F_5, G_5, A_5, PAU, F_5, DS5, C_6, PAU, C_6, AS5, C_6, AS5, C_6, AS5, C_6, AS5, C_6, AS5, C_6, AS5, C_6, AS5, C_6, AS5, DS5, F_5, PAU, DS5, F_5, DS5, AS5, PAU, G_5, AS5, PAU, DS5, AS5, C_6, PAU, B_5, C_6, B_5, C_6, PAU, F_6, AS5, PAU, GS5, AS5, C_6, GS5, F_5, PAU, AS5, G_5, GS5, PAU, AS5, G_5, DS5, G_5, PAU, F_5, GS5, C_6, DS6, PAU, AS5, D_6, F_6, D_6, DS6, PAU, DS5, DS6, PAU, AS5, G_5, DS5, PAU, G_5, AS5, G_5, DS6, AS5, PAU, C_6, GS5, DS5, GS5, C_6, C_6, A_5, PAU, F_5, A_5, C_6, A_5, F_6, PAU, C_6, D_6, AS5, F_5, AS5, PAU, D_6, D_6, PAU, B_5, G_5, B_5, D_6, B_5, PAU, G_6, D_6, DS6, F_6, DS6, PAU, D_6, C_6, PAU, C_6, AS5, PAU, C_6, GS5, DS5, C_6, D_6, PAU, AS5, F_5, D_6, DS6, PAU, DS5, DS6, PAU, DS4, F_4, DS4, F_4, PAU, DS4, AS4, FS4, AS4, DS4, PAU, AS4, B_4, AS4, B_4, PAU, AS4, B_4, F_5, PAU, AS4, PAU, GS4, AS4, PAU, B_4, GS4, F_4, AS4, PAU, FS4, GS4, AS4, FS4, PAU, DS4, FS4, F_4, PAU, FS4, GS4, F_4, DS4, PAU, B_4, B_4, AS4, B_4, AS4, B_4, AS4, B_4, AS4, B_4, AS4, B_4, AS4, B_4, AS4, B_4, AS4, DS4, F_4, DS4, F_4, DS4, PAU, AS4, FS4, AS4, DS4, AS4, PAU, B_4, AS4, B_4, AS4, PAU, B_4, F_5, AS4, PAU, GS4, AS4, B_4, PAU, GS4, F_4, AS4, PAU, FS4, GS4, AS4, FS4, DS4, PAU, FS4, F_4, GS4, PAU, B_4, DS5, AS4, D_5, F_5, PAU, D_5, DS5, DS4, PAU, DS5, PAU, AS4, PAU, FS4, DS4, FS4, AS4, FS4, PAU, DS5, AS4, B_4, GS4, DS4, PAU, GS4, B_4, B_4, GS4, E_4, GS4, B_4, PAU, GS4, E_5, B_4, D_5, AS4, PAU, F_4, AS4, D_5, DS5, AS4, FS4, AS4, PAU, DS5, AS4, FS5, DS5, DS5, PAU, F_5, DS5, CS5, B_4, PAU, B_4, AS4, B_4, GS4, DS4, PAU, B_4, D_5, AS4, F_4, D_5, PAU, DS5, DS4, DS5, ENDSOUND,
  67, 1, 67, 67, 67, 134, 1, 134, 202, 67, 134, 134, 1, 67, 67, 67, 67, 134, 1, 134, 269, 269, 67, 67, 67, 67, 1, 134, 134, 67, 1, 67, 67, 67, 134, 1, 134, 67, 67, 67, 1, 67, 134, 134, 1, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 67, 67, 1, 67, 67, 134, 134, 1, 202, 67, 1, 134, 134, 67, 1, 67, 67, 67, 134, 1, 134, 269, 269, 67, 67, 67, 67, 134, 1, 134, 67, 67, 1, 67, 67, 134, 134, 1, 67, 67, 67, 67, 1, 67, 67, 67, 67, 134, 1, 134, 134, 135, 67, 67, 67, 1, 67, 67, 67, 67, 67, 1, 67, 67, 67, 67, 269, 67, 67, 1, 67, 67, 67, 67, 67, 1, 67, 67, 67, 67, 67, 1, 269, 67, 1, 67, 67, 67, 67, 67, 1, 67, 67, 67, 67, 67, 1, 67, 67, 67, 67, 67, 1, 67, 67, 67, 67, 67, 1, 67, 67, 67, 134, 1, 134, 134, 135, 67, 67, 67, 67, 1, 134, 134, 202, 67, 134, 1, 134, 67, 67, 67, 1, 67, 134, 134, 1, 269, 268, 67, 67, 1, 67, 67, 134, 134, 1, 67, 67, 67, 67, 1, 134, 134, 67, 1, 67, 67, 67, 134, 1, 134, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 67, 67, 67, 67, 134, 1, 134, 202, 67, 134, 134, 1, 67, 67, 67, 67, 1, 134, 134, 269, 269, 67, 67, 67, 1, 67, 134, 134, 1, 67, 67, 67, 67, 134, 1, 134, 67, 67, 1, 67, 67, 67, 67, 67, 1, 67, 134, 134, 1, 134, 134, 67, 1, 67, 67, 67, 67, 67, 1, 67, 67, 67, 67, 67, 1, 67, 269, 67, 67, 67, 67, 67, 1, 67, 67, 67, 67, 67, 1, 67, 67, 269, 67, 67, 67, 67, 1, 67, 67, 67, 67, 67, 1, 67, 67, 67, 67, 68, 67, 67, 67, 67, 67, 1, 67, 67, 67, 67, 67, 1, 134, 134, 134,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 14
};

// Instrument: 0 patchchange ch: 2 piccolo;
const u16 captainTrack2[] =
{
  AS4, PAU, AS4, AS4, C_5, PAU, AS4, G_4, AS4, PAU, C_5, D_5, AS4, C_5, C_5, A_4, F_5, DS5, D_5, PAU, C_5, AS4, PAU, AS4, AS4, C_5, PAU, AS4, G_4, AS4, PAU, C_5, D_5, AS4, C_5, GS4, AS4, G_4, PAU, DS4, DS5, PAU, G_5, DS5, AS4, PAU, DS5, G_5, DS5, AS5, G_5, PAU, GS5, DS5, C_5, DS5, GS5, A_5, F_5, PAU, C_5, F_5, A_5, F_5, C_6, PAU, A_5, AS5, F_5, D_5, F_5, PAU, AS5, B_5, PAU, G_5, D_5, G_5, B_5, G_5, PAU, D_6, B_5, C_6, D_6, C_6, PAU, AS5, G_5, PAU, G_5, PAU, GS5, DS5, C_5, GS5, AS5, PAU, F_5, D_5, AS5, DS5, PAU, DS5, PAU, AS3, PAU, AS3, AS3, B_3, PAU, AS3, FS3, PAU, AS3, B_3, D_4, AS3, B_3, B_3, GS3, F_4, DS4, PAU, D_4, B_3, PAU, AS3, PAU, AS3, AS3, B_3, PAU, AS3, FS3, PAU, AS3, B_3, D_4, AS3, B_3, GS3, AS3, FS3, DS3, PAU, DS4, PAU, FS4, PAU, DS4, AS3, DS4, FS4, DS4, PAU, AS4, FS4, GS4, DS4, B_3, PAU, DS4, GS4, GS4, E_4, B_3, E_4, GS4, PAU, E_4, B_4, GS4, AS4, F_4, PAU, D_4, F_4, GS4, AS4, FS4, DS4, FS4, PAU, AS4, FS4, DS5, AS4, B_4, PAU, CS5, B_4, AS4, FS4, PAU, FS4, GS4, DS4, B_3, PAU, GS4, AS4, F_4, D_4, GS4, PAU, DS4, PAU, DS4, ENDSOUND,
  134, 404, 269, 269, 134, 403, 269, 134, 134, 1, 269, 269, 269, 269, 269, 269, 134, 134, 134, 1, 134, 134, 404, 269, 269, 134, 404, 269, 134, 134, 1, 269, 269, 269, 269, 269, 269, 134, 1, 134, 134, 135, 67, 67, 67, 1, 67, 67, 67, 67, 67, 1, 67, 67, 67, 67, 269, 67, 67, 1, 67, 67, 67, 67, 67, 1, 67, 67, 67, 67, 67, 1, 269, 67, 1, 67, 67, 67, 67, 67, 1, 67, 67, 67, 67, 67, 1, 67, 67, 67, 134, 1, 67, 67, 67, 67, 67, 1, 67, 67, 67, 134, 135, 134, 135, 134, 403, 269, 269, 134, 404, 269, 134, 1, 134, 269, 269, 269, 269, 269, 269, 134, 134, 1, 134, 134, 1, 134, 403, 269, 269, 134, 403, 269, 134, 1, 134, 269, 269, 269, 269, 269, 269, 134, 134, 1, 134, 134, 67, 1, 67, 67, 67, 67, 67, 1, 67, 67, 67, 67, 67, 1, 67, 269, 67, 67, 67, 67, 67, 1, 67, 67, 67, 67, 67, 1, 67, 67, 269, 67, 67, 67, 67, 1, 67, 67, 67, 67, 67, 1, 67, 67, 67, 67, 68, 134, 67, 67, 67, 1, 67, 67, 67, 67, 67, 1, 134, 134, 134,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 14
};

// Instrument: 0 patchchange ch: 3 reed organ;
const u16 captainTrack3[] =
{
  G_4, PAU, DS4, G_4, GS4, PAU, G_4, DS4, G_4, PAU, F_4, GS4, DS4, G_4, A_4, F_4, D_5, C_5, AS4, PAU, GS4, G_4, PAU, DS4, G_4, GS4, PAU, G_4, DS4, G_4, PAU, F_4, GS4, DS4, G_4, F_4, D_4, DS4, DS4, PAU, DS3, PAU, DS3, PAU, GS3, PAU, GS3, F_3, PAU, F_3, PAU, AS3, PAU, AS3, G_3, PAU, G_3, C_4, PAU, C_4, GS2, PAU, AS2, PAU, DS2, PAU, DS3, DS2, PAU, FS3, PAU, DS3, FS3, GS3, PAU, FS3, DS3, PAU, FS3, F_3, GS3, DS3, FS3, GS3, F_3, D_4, B_3, PAU, AS3, GS3, PAU, FS3, PAU, DS3, FS3, GS3, PAU, FS3, DS3, PAU, FS3, F_3, GS3, DS3, FS3, F_3, D_3, DS3, DS3, PAU, DS3, PAU, DS3, GS3, PAU, GS3, E_3, PAU, E_3, AS3, PAU, AS3, FS3, PAU, FS3, B_3, PAU, B_3, GS2, PAU, AS2, PAU, DS2, DS3, DS2, ENDSOUND,
  134, 404, 269, 269, 134, 403, 269, 134, 134, 1, 269, 269, 269, 269, 269, 269, 134, 134, 134, 1, 134, 134, 404, 269, 269, 134, 404, 269, 134, 134, 1, 269, 269, 269, 269, 269, 269, 269, 134, 135, 134, 269, 134, 1, 134, 134, 269, 134, 269, 134, 1, 134, 135, 269, 134, 270, 134, 134, 135, 269, 134, 134, 134, 135, 134, 1, 134, 134, 135, 134, 403, 269, 269, 134, 404, 269, 134, 1, 134, 269, 269, 269, 269, 269, 269, 134, 134, 1, 134, 134, 1, 134, 403, 269, 269, 134, 403, 269, 134, 1, 134, 269, 269, 269, 269, 269, 269, 269, 134, 134, 134, 270, 134, 134, 135, 269, 134, 269, 134, 134, 135, 269, 134, 269, 134, 134, 135, 269, 134, 135, 134, 135, 134, 134, 134,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 14
};


SoundChannelConfigurationROM CAPTAIN_CHANNEL_1_CONFIGURATION =
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
	pianoWaveForm,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelROM CAPTAIN_CHANNEL_1 =
{
	/// Configuration
	(SoundChannelConfiguration*)&CAPTAIN_CHANNEL_1_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const u8*)captainTrack1
	}
};

SoundChannelConfigurationROM CAPTAIN_CHANNEL_2_CONFIGURATION =
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

SoundChannelROM CAPTAIN_CHANNEL_2 =
{
	/// Configuration
	(SoundChannelConfiguration*)&CAPTAIN_CHANNEL_2_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const u8*)captainTrack2
	}
};


SoundChannelConfigurationROM CAPTAIN_CHANNEL_3_CONFIGURATION =
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
	violinWaveForm,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelROM CAPTAIN_CHANNEL_3 =
{
	/// Configuration
	(SoundChannelConfiguration*)&CAPTAIN_CHANNEL_3_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const u8*)captainTrack2
	}
};


SoundChannelROM* CAPTAIN_CHANNELS[] =
{
	&CAPTAIN_CHANNEL_1,
	&CAPTAIN_CHANNEL_2,
	//&CAPTAIN_CHANNEL_3,
	NULL
};

SoundROM CAPTAIN_SONG =
{
	/// Name
	"Captain",

	/// Play in loop
	true,

	/// Target timer resolution in us
	1580,

	/// Tracks
	(SoundChannel**)CAPTAIN_CHANNELS
};