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

// Instrument: square;
const u16 INTRO_TRACK_1[] =
{
  PAU, E_5, E_3, E_3, D_4, E_4, B_4, E_3, E_3, E_3, E_4, CS4, E_3, E_3, E_3, E_3, A_4, E_4, E_3, GS4, D_4, CS4, A_4, B_3, E_3, GS4, E_3, E_3, D_4, E_4, E_4, E_3, E_3, E_3, B_3, CS4, E_3, D_4, E_3, E_3, D_4, E_4, E_4, E_3, D_4, CS4, A_3, B_3, E_3, E_5, E_3, E_3, D_4, E_4, B_4, E_3, E_3, E_3, E_4, CS4, E_3, E_3, E_3, E_3, A_4, E_4, E_3, GS4, D_4, CS4, A_4, B_3, E_3, GS4, E_3, E_3, D_4, E_4, E_4, E_3, E_3, E_3, B_3, CS4, E_3, D_4, E_3, E_3, D_4, E_4, E_4, E_3, D_4, CS4, FS4, B_3, E_3, B_4, A_3, A_3, G_4, A_4, E_5, A_3, A_3, A_3, G_4, FS4, A_3, A_3, A_3, A_3, G_5, A_4, A_3, FS5, G_4, FS4, B_4, E_4, A_3, D_5, A_3, A_3, G_4, A_4, E_5, A_3, A_3, A_3, G_4, FS4, A_3, A_3, A_3, A_3, G_5, A_4, A_3, A_5, G_4, FS4, E_5, E_4, A_3, B_4, A_3, A_3, G_4, A_4, E_5, A_3, A_3, A_3, G_4, FS4, A_3, A_3, A_3, A_3, G_5, A_4, A_3, FS5, G_4, FS4, D_5, E_4, A_3, E_5, A_3, A_3, G_4, A_4, A_5, A_3, A_3, A_3, G_5, FS4, A_3, FS5, A_3, A_3, G_4, A_4, E_5, A_3, G_4, FS4, D_5, E_4, A_3, E_5, E_3, E_3, D_4, E_4, B_4, E_3, E_3, E_3, E_4, CS4, E_3, E_3, E_3, E_3, A_4, E_4, E_3, GS4, D_4, CS4, A_4, B_3, E_3, GS4, E_3, E_3, D_4, E_4, E_4, E_3, E_3, E_3, B_3, CS4, E_3, D_4, E_3, E_3, D_4, E_4, E_4, E_3, D_4, CS4, A_3, B_3, E_3, E_5, E_3, E_3, D_4, E_4, B_4, E_3, E_3, E_3, E_4, CS4, E_3, E_3, E_3, E_3, A_4, E_4, E_3, GS4, D_4, CS4, A_4, B_3, E_3, GS4, E_3, E_3, D_4, E_4, E_4, E_3, E_3, E_3, B_3, CS4, E_3, D_4, E_3, E_3, D_4, E_4, E_4, E_3, D_4, CS4, FS4, B_3, E_3, B_4, A_3, A_3, G_4, A_4, E_5, A_3, A_3, A_3, G_4, FS4, A_3, A_3, A_3, A_3, G_5, A_4, A_3, FS5, G_4, FS4, B_4, E_4, A_3, D_5, A_3, A_3, G_4, A_4, E_5, A_3, A_3, A_3, G_4, FS4, A_3, A_3, A_3, A_3, G_5, A_4, A_3, A_5, G_4, FS4, E_5, E_4, A_3, B_4, A_3, A_3, G_4, A_4, E_5, A_3, A_3, A_3, G_4, FS4, A_3, A_3, A_3, A_3, G_5, A_4, A_3, FS5, G_4, FS4, D_5, E_4, A_3, E_5, A_3, A_3, G_4, A_4, A_5, A_3, A_3, A_3, G_5, FS4, A_3, FS5, A_3, A_3, G_4, A_4, E_5, A_3, G_4, FS4, D_5, E_4, A_3, ENDSOUND,
  1, 1680, 480, 480, 480, 480, 1680, 480, 480, 480, 1680, 480, 480, 480, 480, 480, 1440, 480, 480, 1440, 480, 480, 1440, 480, 480, 1680, 480, 480, 480, 480, 1680, 480, 480, 480, 1440, 480, 480, 1680, 480, 480, 480, 480, 1680, 480, 480, 480, 480, 480, 480, 1680, 480, 480, 480, 480, 1680, 480, 480, 480, 1680, 480, 480, 480, 480, 480, 1440, 480, 480, 1440, 480, 480, 1440, 480, 480, 1680, 480, 480, 480, 480, 1680, 480, 480, 480, 1440, 480, 480, 1680, 480, 480, 480, 480, 1680, 480, 480, 480, 1440, 480, 480, 1680, 480, 480, 480, 480, 1680, 480, 480, 480, 480, 480, 480, 480, 480, 480, 1440, 480, 480, 1440, 480, 480, 1440, 480, 480, 1680, 480, 480, 480, 480, 1680, 480, 480, 480, 480, 480, 480, 480, 480, 480, 1440, 480, 480, 1440, 480, 480, 1440, 480, 480, 1680, 480, 480, 480, 480, 1680, 480, 480, 480, 480, 480, 480, 480, 480, 480, 1440, 480, 480, 1440, 480, 480, 1440, 480, 480, 1680, 480, 480, 480, 480, 1440, 480, 480, 480, 1440, 480, 480, 1680, 480, 480, 480, 480, 1680, 480, 480, 480, 1440, 480, 480, 1680, 480, 480, 480, 480, 1680, 480, 480, 480, 1680, 480, 480, 480, 480, 480, 1440, 480, 480, 1440, 480, 480, 1440, 480, 480, 1680, 480, 480, 480, 480, 1680, 480, 480, 480, 1440, 480, 480, 1680, 480, 480, 480, 480, 1680, 480, 480, 480, 480, 480, 480, 1680, 480, 480, 480, 480, 1680, 480, 480, 480, 1680, 480, 480, 480, 480, 480, 1440, 480, 480, 1440, 480, 480, 1440, 480, 480, 1680, 480, 480, 480, 480, 1680, 480, 480, 480, 1440, 480, 480, 1680, 480, 480, 480, 480, 1680, 480, 480, 480, 1440, 480, 480, 1680, 480, 480, 480, 480, 1680, 480, 480, 480, 480, 480, 480, 480, 480, 480, 1440, 480, 480, 1440, 480, 480, 1440, 480, 480, 1680, 480, 480, 480, 480, 1680, 480, 480, 480, 480, 480, 480, 480, 480, 480, 1440, 480, 480, 1440, 480, 480, 1440, 480, 480, 1680, 480, 480, 480, 480, 1680, 480, 480, 480, 480, 480, 480, 480, 480, 480, 1440, 480, 480, 1440, 480, 480, 1440, 480, 480, 1680, 480, 480, 480, 480, 1440, 480, 480, 480, 1440, 480, 480, 1680, 480, 480, 480, 480, 1680, 480, 480, 480, 1440, 480, 480,
  15, 15, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12
};


SoundChannelConfigurationROM INTRO_CHANNEL_1_CONFIGURATION =
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

SoundChannelROM INTRO_CHANNEL_1 =
{
	/// Configuration
	(SoundChannelConfiguration*)&INTRO_CHANNEL_1_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const u8*)INTRO_TRACK_1
	}
};

SoundChannelROM* INTRO_CHANNELS[] =
{
	&INTRO_CHANNEL_1,
	NULL
};

SoundROM INTRO_SONG =
{
	/// Name
	"Intro",

	/// Play in loop
	true,

	/// Target timer resolution in us
	300,

	/// Tracks
	(SoundChannel**)INTRO_CHANNELS
};
