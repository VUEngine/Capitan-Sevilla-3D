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


const u16 ReloadTrack[] =
{
  A_3, B_3, E_4, HOLD, ENDSOUND,
  80, 80, 80, 1, 1,
  15, 15, 15, 15, 0,
};

SoundChannelConfigurationROM RELOAD_SND_CHANNEL_1_CONFIGURATION =
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
	sineWaveForm,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelROM RELOAD_SND_CHANNEL_1 =
{
	/// Configuration
	(SoundChannelConfiguration*)&RELOAD_SND_CHANNEL_1_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const u8*)ReloadTrack
	}
};


SoundChannelROM* RELOAD_SND_CHANNELS[] =
{
	&RELOAD_SND_CHANNEL_1,
	NULL
};

SoundROM RELOAD_SND =
{
	/// Name
	"Reload",

	/// Play in loop
	false,

	/// Target timer resolution in us
	500,

	/// Tracks
	(SoundChannel**)RELOAD_SND_CHANNELS
};