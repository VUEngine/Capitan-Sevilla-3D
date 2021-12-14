
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

const uint16 HoverEngineSoundTrack1[] =
{
  0x016 + HOVER_ENGINE_FREQ, 0x024 + HOVER_ENGINE_FREQ, 0x032 + HOVER_ENGINE_FREQ, 0x040 + HOVER_ENGINE_FREQ, 0x032 + HOVER_ENGINE_FREQ, 0x024 + HOVER_ENGINE_FREQ, 0x016 + HOVER_ENGINE_FREQ, ENDSOUND,
  HOVER_ENGINE_DURATION * 4, HOVER_ENGINE_DURATION * 3, HOVER_ENGINE_DURATION * 2, HOVER_ENGINE_DURATION * 1, HOVER_ENGINE_DURATION * 2, HOVER_ENGINE_DURATION * 3, HOVER_ENGINE_DURATION * 4,
  HOVER_ENGINE_VOLUME_DELTA, HOVER_ENGINE_VOLUME_DELTA, HOVER_ENGINE_VOLUME_DELTA, HOVER_ENGINE_VOLUME_DELTA, HOVER_ENGINE_VOLUME_DELTA, HOVER_ENGINE_VOLUME_DELTA, HOVER_ENGINE_VOLUME_DELTA,
};

SoundChannelConfigurationROM HoverEngineSoundChannel1Configuration =
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
	EngineWaveForm,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelROM HoverEngineSoundChannel1 =
{
	/// Configuration
	(SoundChannelConfiguration*)&HoverEngineSoundChannel1Configuration,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const uint8*)HoverEngineSoundTrack1
	}
};


SoundChannelROM* HoverEngineSoundChannels[] =
{
	&HoverEngineSoundChannel1,
	NULL
};

SoundROM HoverEngineSound =
{
	/// Name
	"Hover Engine",

	/// Play in loop
	true,

	/// Target timer resolution in us
	3000,

	/// Tracks
	(SoundChannel**)HoverEngineSoundChannels
};