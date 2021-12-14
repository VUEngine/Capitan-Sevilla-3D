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
#include <WaveForms.h>


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// Instrument: ;
const uint16 TITLE_TRACK_1[] =
{
  PAU, E_5, PAU, B_4, PAU, D_5, PAU, E_5, PAU, B_4, PAU, D_5, PAU, E_5, PAU, G_5, PAU, E_5, PAU, D_5, PAU, B_4, PAU, E_5, PAU, B_4, PAU, D_5, PAU, E_5, PAU, B_4, PAU, D_5, PAU, E_5, PAU, A_5, PAU, G_5, PAU, E_5, PAU, D_5, PAU, E_5, ENDSOUND,
  1, 342, 18, 114, 6, 342, 18, 1416, 24, 114, 6, 342, 18, 114, 6, 342, 18, 114, 6, 342, 18, 114, 6, 342, 18, 114, 6, 342, 18, 1416, 24, 114, 6, 342, 18, 114, 6, 342, 18, 114, 6, 342, 18, 114, 6, 456,
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12
};

// Instrument: ;
const uint16 TITLE_TRACK_2[] =
{
  PAU, B_4, PAU, B_4, PAU, CS5, PAU, CS5, PAU, D_5, PAU, D_5, PAU, CS5, PAU, D_5, PAU, B_4, PAU, B_4, PAU, CS5, PAU, CS5, PAU, D_5, PAU, D_5, PAU, CS5, PAU, D_5, PAU, GS4, ENDSOUND,
  1, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 342, 18, 594, 6, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 342, 18, 594, 6, 456,
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12
};

// Instrument: ;
const uint16 TITLE_TRACK_3[] =
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
	SquareWaveForm,

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
		(const uint8*)TITLE_TRACK_1
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
	SquareWaveForm,

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
		(const uint8*)TITLE_TRACK_2
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
	TriangleWaveForm,

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
		(const uint8*)TITLE_TRACK_3
	}
};

SoundChannelROM* TITLEChannels[] =
{
	&TITLE_CHANNEL_1,
	&TITLE_CHANNEL_2,
	&TITLE_CHANNEL_3,
	NULL
};

SoundROM TitleSong =
{
	/// Name
	"Title",

	/// Play in loop
	true,

	/// Target timer resolution in us
	1060,

	/// Tracks
	(SoundChannel**)TITLEChannels
};
