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


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// Instrument: square;
const uint16 INTRO_TRACK_1[] =
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
	SquareWaveForm,

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
		(const uint8*)INTRO_TRACK_1
	}
};

SoundChannelROM* INTROChannels[] =
{
	&INTRO_CHANNEL_1,
	NULL
};

SoundROM IntroSong =
{
	/// Name
	"Intro",

	/// Play in loop
	true,

	/// Target timer resolution in us
	300,

	/// Tracks
	(SoundChannel**)INTROChannels
};