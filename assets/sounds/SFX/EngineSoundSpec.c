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
  PAU, 0x016 + ENGINE_FREQ, 0x024 + ENGINE_FREQ, 0x032 + ENGINE_FREQ, 0x040 + ENGINE_FREQ, 0x032 + ENGINE_FREQ, 0x024 + ENGINE_FREQ, 0x016 + ENGINE_FREQ, ENDSOUND,
  50, ENGINE_DURATION * 4, ENGINE_DURATION * 3, ENGINE_DURATION * 2, ENGINE_DURATION * 1, ENGINE_DURATION * 2, ENGINE_DURATION * 3, ENGINE_DURATION * 4,
  0, ENGINE_VOLUME_DELTA, ENGINE_VOLUME_DELTA, ENGINE_VOLUME_DELTA, ENGINE_VOLUME_DELTA, ENGINE_VOLUME_DELTA, ENGINE_VOLUME_DELTA, ENGINE_VOLUME_DELTA,
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
	kChannelModulation,

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