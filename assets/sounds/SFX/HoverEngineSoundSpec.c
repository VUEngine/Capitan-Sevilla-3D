
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

#define HOVER_ENGINE_FREQ				MINIMUM_AUDIBLE_NOTE + 0xAAA + 256
#define HOVER_ENGINE_DURATION			17
#define HOVER_ENGINE_VOLUME_DELTA		15


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

const u16 HoverEngineSoundTrack1[] =
{
  0x016 + HOVER_ENGINE_FREQ, 0x024 + HOVER_ENGINE_FREQ, 0x032 + HOVER_ENGINE_FREQ, 0x040 + HOVER_ENGINE_FREQ, 0x032 + HOVER_ENGINE_FREQ, 0x024 + HOVER_ENGINE_FREQ, 0x016 + HOVER_ENGINE_FREQ, ENDSOUND,
  HOVER_ENGINE_DURATION * 4, HOVER_ENGINE_DURATION * 3, HOVER_ENGINE_DURATION * 2, HOVER_ENGINE_DURATION * 1, HOVER_ENGINE_DURATION * 2, HOVER_ENGINE_DURATION * 3, HOVER_ENGINE_DURATION * 4,
  HOVER_ENGINE_VOLUME_DELTA, HOVER_ENGINE_VOLUME_DELTA, HOVER_ENGINE_VOLUME_DELTA, HOVER_ENGINE_VOLUME_DELTA, HOVER_ENGINE_VOLUME_DELTA, HOVER_ENGINE_VOLUME_DELTA, HOVER_ENGINE_VOLUME_DELTA,
};

SoundChannelConfigurationROM HOVER_ENGINE_SOUND_CHANNEL_1_CONFIGURATION =
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

SoundChannelROM HOVER_ENGINE_SOUND_CHANNEL_1 =
{
	/// Configuration
	(SoundChannelConfiguration*)&HOVER_ENGINE_SOUND_CHANNEL_1_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const u8*)HoverEngineSoundTrack1
	}
};


SoundChannelROM* HOVER_ENGINE_SOUND_CHANNELS[] =
{
	&HOVER_ENGINE_SOUND_CHANNEL_1,
	NULL
};

SoundROM HOVER_ENGINE_SND =
{
	/// Name
	"Hover Engine",

	/// Play in loop
	true,

	/// Target timer resolution in us
	3000,

	/// Tracks
	(SoundChannel**)HOVER_ENGINE_SOUND_CHANNELS
};