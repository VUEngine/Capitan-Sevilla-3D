/**
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
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


const uint16 CONFIRM_TRACK_1[] =
{
  A_4, B_4, E_5, HOLD, ENDSOUND,
  80, 80, 80, 1, 1,
  15, 15, 15, 15 , 0
};

SoundChannelConfigurationROM ConfirmSoundChannel1Configuration =
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
	SawtoothWaveForm,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelROM ConfirmSoundChannel1 =
{
	/// Configuration
	(SoundChannelConfiguration*)&ConfirmSoundChannel1Configuration,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const uint8*)CONFIRM_TRACK_1
	}
};


SoundChannelROM* const ConfirmSoundChannels[] =
{
	&ConfirmSoundChannel1,
	NULL
};

SoundROM ConfirmSound =
{
	/// Name
	"Confirm",

	/// Play in loop
	false,

	/// Target timer resolution in us
	500,

	/// Tracks
	(SoundChannel**)ConfirmSoundChannels
};