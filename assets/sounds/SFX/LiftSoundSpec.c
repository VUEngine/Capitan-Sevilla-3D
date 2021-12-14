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

#define LIFT_FREQ				MINIMUM_AUDIBLE_NOTE + 480
#define LIFT_DURATION			140
#define LIFT_VOLUME_DELTA		6


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

const uint16 LIFT_TRACK_1[] =
{
  PAU, 0x016 + LIFT_FREQ, 0x024 + LIFT_FREQ, 0x032 + LIFT_FREQ, 0x040 + LIFT_FREQ, 0x032 + LIFT_FREQ, 0x024 + LIFT_FREQ, 0x016 + LIFT_FREQ, ENDSOUND,
  50, LIFT_DURATION * 4, LIFT_DURATION * 3, LIFT_DURATION * 2, LIFT_DURATION * 1, LIFT_DURATION * 2, LIFT_DURATION * 3, LIFT_DURATION * 4,
  0, LIFT_VOLUME_DELTA, LIFT_VOLUME_DELTA, LIFT_VOLUME_DELTA, LIFT_VOLUME_DELTA, LIFT_VOLUME_DELTA, LIFT_VOLUME_DELTA, LIFT_VOLUME_DELTA,
};

SoundChannelConfigurationROM LiftChannel1Configuration =
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
	kChannelModulation,

	/// Volume
	__SOUND_LR
};

SoundChannelROM LiftChannel1 =
{
	/// Configuration
	(SoundChannelConfiguration*)&LiftChannel1Configuration,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const uint8*)LIFT_TRACK_1
	}
};


SoundChannelROM* LiftChannels[] =
{
	&LiftChannel1,
	NULL
};

SoundROM LiftSound =
{
	/// Name
	"Lift",

	/// Play in loop
	true,

	/// Target timer resolution in us
	3000,

	/// Tracks
	(SoundChannel**)LiftChannels
};