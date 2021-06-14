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

// Instrument: square;
const u16 CREDITS_TRACK_1[] =
{
  PAU, E_5, G_4, FS4, G_4, C_5, E_5, G_5, C_6, C_6, G_5, A_5, A_5, G_5, F_5, A_5, G_5, G_4, GS4, A_4, GS4, G_4, PAU, E_5, G_4, FS4, G_4, C_5, E_5, G_5, C_6, C_6, G_5, A_5, A_5, G_5, F_5, A_5, G_5, C_5, A_4, GS4, G_4, E_4, E_4, G_4, B_4, D_5, F_5, PAU, B_5, B_4, D_5, F_5, E_5, G_5, C_6, B_4, A_4, D_5, FS5, A_5, PAU, D_6, PAU, D_5, PAU, B_4, B_5, B_4, B_4, B_3, B_3, C_4, D_4, PAU, E_5, G_4, FS4, G_4, C_5, E_5, G_5, C_6, C_6, G_5, A_5, A_5, G_5, F_5, A_5, G_5, G_4, GS4, A_4, GS4, G_4, PAU, E_5, G_4, FS4, G_4, C_5, E_5, G_5, C_6, C_6, G_5, A_5, A_5, G_5, F_5, A_5, G_5, C_5, A_4, GS4, G_4, E_4, E_4, G_4, B_4, D_5, F_5, PAU, B_5, B_4, D_5, F_5, E_5, G_5, C_6, B_4, A_4, D_5, FS5, A_5, PAU, D_6, PAU, D_5, PAU, B_4, B_5, B_4, B_4, B_3, B_3, C_4, D_4, ENDSOUND,
  61, 30, 90, 60, 30, 60, 30, 60, 90, 180, 30, 60, 30, 90, 90, 90, 90, 60, 30, 60, 30, 90, 60, 30, 90, 60, 30, 60, 30, 60, 90, 180, 30, 60, 30, 90, 90, 90, 90, 30, 30, 30, 60, 90, 30, 30, 30, 30, 60, 30, 90, 30, 30, 30, 90, 90, 150, 30, 30, 30, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 90, 60, 30, 60, 30, 60, 90, 180, 30, 60, 30, 90, 90, 90, 90, 60, 30, 60, 30, 90, 60, 30, 90, 60, 30, 60, 30, 60, 90, 180, 30, 60, 30, 90, 90, 90, 90, 30, 30, 30, 60, 90, 30, 30, 30, 30, 60, 30, 90, 30, 30, 30, 90, 90, 150, 30, 30, 30, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30,
  11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11
};

// Instrument: square;
const u16 CREDITS_TRACK_2[] =
{
  PAU, E_5, G_4, FS4, G_4, C_5, E_5, G_5, C_6, C_6, G_5, A_5, A_5, G_5, F_5, A_5, G_5, G_4, GS4, A_4, GS4, G_4, PAU, E_5, G_4, FS4, G_4, C_5, E_5, G_5, C_6, C_6, G_5, A_5, A_5, G_5, F_5, A_5, G_5, PAU, G_4, B_4, D_5, F_5, PAU, B_5, B_4, D_5, F_5, E_5, G_5, C_6, B_4, A_4, D_5, FS5, A_5, PAU, D_6, PAU, D_5, PAU, B_4, B_5, B_4, B_4, B_3, B_3, C_4, PAU, E_5, G_4, FS4, G_4, C_5, E_5, G_5, C_6, C_6, G_5, A_5, A_5, G_5, F_5, A_5, G_5, G_4, GS4, A_4, GS4, G_4, PAU, E_5, G_4, FS4, G_4, C_5, E_5, G_5, C_6, C_6, G_5, A_5, A_5, G_5, F_5, A_5, G_5, PAU, G_4, B_4, D_5, F_5, PAU, B_5, B_4, D_5, F_5, E_5, G_5, C_6, B_4, A_4, D_5, FS5, A_5, PAU, D_6, PAU, D_5, PAU, B_4, B_5, B_4, B_4, B_3, B_3, C_4, PAU, ENDSOUND,
  87, 30, 90, 60, 30, 60, 30, 60, 90, 180, 30, 60, 30, 90, 90, 90, 90, 60, 30, 60, 30, 90, 60, 30, 90, 60, 30, 60, 30, 60, 90, 180, 30, 60, 30, 90, 90, 90, 90, 270, 30, 30, 30, 60, 30, 90, 30, 30, 30, 90, 90, 150, 30, 30, 30, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 90, 30, 90, 60, 30, 60, 30, 60, 90, 180, 30, 60, 30, 90, 90, 90, 90, 60, 30, 60, 30, 90, 60, 30, 90, 60, 30, 60, 30, 60, 90, 180, 30, 60, 30, 90, 90, 90, 90, 270, 30, 30, 30, 60, 30, 90, 30, 30, 30, 90, 90, 150, 30, 30, 30, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 4,
  11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11
};

// Instrument: 0 patchchange ch: 3 lead 2 (sawtooth);
const u16 CREDITS_TRACK_3[] =
{
  PAU, C_3, PAU, E_2, PAU, G_2, PAU, E_2, PAU, C_3, PAU, E_2, PAU, G_2, PAU, E_2, PAU, F_2, PAU, F_2, PAU, A_2, PAU, F_2, PAU, C_3, PAU, G_2, GS2, A_2, GS2, G_2, PAU, C_3, PAU, E_2, PAU, G_2, PAU, E_2, PAU, C_3, PAU, E_2, PAU, G_2, PAU, E_2, PAU, F_2, PAU, F_2, PAU, A_2, PAU, F_2, PAU, C_3, PAU, C_3, PAU, G_2, PAU, F_2, PAU, B_2, PAU, D_2, PAU, C_3, PAU, E_2, PAU, E_2, PAU, D_3, PAU, FS2, PAU, A_2, PAU, FS2, PAU, G_1, PAU, G_2, PAU, A_2, AS2, B_2, C_3, PAU, E_2, PAU, G_2, PAU, E_2, PAU, C_3, PAU, E_2, PAU, G_2, PAU, E_2, PAU, F_2, PAU, F_2, PAU, A_2, PAU, F_2, PAU, C_3, PAU, G_2, GS2, A_2, GS2, G_2, PAU, C_3, PAU, E_2, PAU, G_2, PAU, E_2, PAU, C_3, PAU, E_2, PAU, G_2, PAU, E_2, PAU, F_2, PAU, F_2, PAU, A_2, PAU, F_2, PAU, C_3, PAU, C_3, PAU, G_2, PAU, F_2, PAU, B_2, PAU, D_2, PAU, C_3, PAU, E_2, PAU, E_2, PAU, D_3, PAU, FS2, PAU, A_2, PAU, FS2, PAU, G_1, PAU, G_2, PAU, A_2, AS2, B_2, ENDSOUND,
  1, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 180, 90, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 120, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 105, 45, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 180, 90, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 120, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 60, 30, 105, 45, 30, 60, 30,
  11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11
};

// Instrument: 0 patchchange ch: 10 acoustic grand;
const u16 CREDITS_TRACK_4[] =
{
  PAU, E_2, PAU, AS2, FS2, PAU, AS2, DS2, PAU, AS2, FS2, PAU, AS2, DS2, PAU, AS2, FS2, PAU, AS2, DS2, PAU, AS2, FS2, PAU, FS2, DS2, PAU, AS2, FS2, PAU, AS2, DS2, PAU, AS2, FS2, PAU, AS2, E_2, PAU, AS2, FS2, PAU, AS2, E_2, PAU, E_2, FS2, PAU, FS2, E_2, PAU, AS2, FS2, PAU, AS2, DS2, PAU, AS2, FS2, PAU, AS2, DS2, PAU, AS2, FS2, PAU, AS2, DS2, PAU, AS2, FS2, PAU, FS2, DS2, PAU, AS2, FS2, PAU, AS2, DS2, PAU, AS2, FS2, PAU, AS2, E_2, PAU, AS2, FS2, PAU, AS2, E_2, PAU, E_2, FS2, PAU, FS2, E_2, PAU, AS2, FS2, PAU, AS2, DS2, PAU, AS2, FS2, PAU, AS2, DS2, PAU, AS2, FS2, PAU, AS2, DS2, PAU, AS2, FS2, PAU, FS2, DS2, PAU, AS2, FS2, PAU, AS2, DS2, PAU, AS2, FS2, PAU, AS2, E_2, PAU, AS2, FS2, PAU, AS2, E_2, PAU, E_2, FS2, PAU, FS2, E_2, PAU, AS2, FS2, PAU, AS2, DS2, PAU, AS2, FS2, PAU, AS2, DS2, PAU, AS2, FS2, PAU, AS2, DS2, PAU, AS2, FS2, PAU, FS2, DS2, PAU, AS2, FS2, PAU, AS2, DS2, PAU, AS2, FS2, PAU, AS2, E_2, PAU, AS2, FS2, PAU, AS2, E_2, PAU, E_2, FS2, PAU, FS2, E_2, PAU, AS2, FS2, PAU, AS2, DS2, PAU, AS2, FS2, PAU, AS2, DS2, PAU, AS2, FS2, PAU, AS2, DS2, PAU, AS2, FS2, PAU, FS2, DS2, PAU, AS2, FS2, PAU, AS2, DS2, PAU, AS2, FS2, PAU, AS2, E_2, PAU, AS2, FS2, PAU, AS2, E_2, PAU, E_2, FS2, PAU, FS2, E_2, PAU, AS2, FS2, PAU, AS2, DS2, PAU, AS2, FS2, PAU, AS2, DS2, PAU, AS2, FS2, PAU, AS2, DS2, PAU, AS2, FS2, PAU, FS2, DS2, PAU, AS2, FS2, PAU, AS2, DS2, PAU, AS2, FS2, PAU, AS2, E_2, PAU, AS2, FS2, PAU, AS2, E_2, PAU, E_2, FS2, PAU, FS2, ENDSOUND,
  1, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
  11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11
};


SoundChannelConfigurationROM CREDITS_CHANNEL_1_CONFIGURATION =
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
	squareWaveForm,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelROM CREDITS_CHANNEL_1 =
{
	/// Configuration
	(SoundChannelConfiguration*)&CREDITS_CHANNEL_1_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const u8*)CREDITS_TRACK_1
	}
};

SoundChannelConfigurationROM CREDITS_CHANNEL_2_CONFIGURATION =
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
	squareWaveForm,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelROM CREDITS_CHANNEL_2 =
{
	/// Configuration
	(SoundChannelConfiguration*)&CREDITS_CHANNEL_2_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const u8*)CREDITS_TRACK_2
	}
};

SoundChannelConfigurationROM CREDITS_CHANNEL_3_CONFIGURATION =
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
	sawtoothWaveForm,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelROM CREDITS_CHANNEL_3 =
{
	/// Configuration
	(SoundChannelConfiguration*)&CREDITS_CHANNEL_3_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const u8*)CREDITS_TRACK_3
	}
};


SoundChannelConfigurationROM CREDITS_CHANNEL_4_CONFIGURATION =
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
	pianoWaveForm,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelROM CREDITS_CHANNEL_4 =
{
	/// Configuration
	(SoundChannelConfiguration*)&CREDITS_CHANNEL_4_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const u8*)CREDITS_TRACK_4
	}
};


SoundChannelROM* CREDITS_CHANNELS[] =
{
	&CREDITS_CHANNEL_1,
	&CREDITS_CHANNEL_2,
	&CREDITS_CHANNEL_3,
	&CREDITS_CHANNEL_4,
	NULL
};

SoundROM CREDITS_SONG =
{
	/// Name
	"Credits",

	/// Play in loop
	true,

	/// Target timer resolution in us
	3340,

	/// Tracks
	(SoundChannel**)CREDITS_CHANNELS
};


