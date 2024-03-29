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


const uint16 LIFT_BREAK_TRACK_1[] =
{
  A_4, B_4, E_5, HOLD, A_4, B_4, E_5, HOLD, ENDSOUND,
  100,  80, 100,    1, 100,  80, 100,    1, 1,
   12,  12,  12,   12 , 12,  12,  12,   12, 0,
};

SoundChannelConfigurationROM LiftBreakSoundChannel1Configuration =
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
	0x00,

	/// SxFQH
	0x00,

	/// SxFQL
	0x00,

	/// Ch. 5 only
	0x00,

	/// Waveform data pointer
	SawtoothWaveForm,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNoise,

	/// Volume
	__SOUND_LR
};

SoundChannelROM LiftBreakSoundChannel1 =
{
	/// Configuration
	(SoundChannelConfiguration*)&LiftBreakSoundChannel1Configuration,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const uint8*)LIFT_BREAK_TRACK_1
	}
};


SoundChannelROM* LiftBreakSoundChannels[] =
{
	&LiftBreakSoundChannel1,
	NULL
};

SoundROM LiftBreakSound =
{
	/// Name
	"Lift break",

	/// Play in loop
	false,

	/// Target timer resolution in us
	5000,

	/// Tracks
	(SoundChannel**)LiftBreakSoundChannels
};