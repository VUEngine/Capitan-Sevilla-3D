/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
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
const uint16 GAME_OVER_TRACK_1[] =
{
  PAU, GS5, PAU, GS5, PAU, B_5, PAU, GS5, PAU, B_5, PAU, A_5, PAU, A_5, PAU, CS6, PAU, A_5, PAU, CS6, PAU, B_5, PAU, B_5, PAU, E_6, PAU, DS6, PAU, CS6, PAU, B_5, PAU, ENDSOUND,
  1, 94, 2, 46, 2, 94, 2, 46, 2, 94, 2, 94, 2, 46, 2, 94, 2, 46, 2, 94, 2, 94, 2, 46, 2, 94, 2, 46, 2, 94, 2, 94, 96,
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};

// Instrument: 0 patchchange ch: 2 electric guitar(jazz);
const uint16 GAME_OVER_TRACK_2[] =
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
		(const uint8*)GAME_OVER_TRACK_1
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
		(const uint8*)GAME_OVER_TRACK_2
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
