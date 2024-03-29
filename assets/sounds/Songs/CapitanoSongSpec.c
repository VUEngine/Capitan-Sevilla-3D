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

// Instrument: 0 patchchange ch: 1 drawbar organ;
const uint16 CAPITANO_TRACK_1[] =
{
  PAU, E_6, PAU, GS6, PAU, FS6, PAU, A_6, PAU, GS6, PAU, DS6, PAU, E_6, PAU, CS6, PAU, FS6, PAU, GS6, PAU, CS6, PAU, B_5, PAU, FS6, PAU, GS6, PAU, B_6, PAU, GS6, PAU, CS7, PAU, B_6, PAU, FS6, PAU, E_6, PAU, GS6, PAU, FS6, PAU, A_6, PAU, GS6, PAU, DS6, PAU, E_6, PAU, CS6, PAU, FS6, PAU, GS6, PAU, B_6, PAU, A_6, PAU, GS6, PAU, A_6, PAU, GS6, PAU, DS6, PAU, GS6, PAU, F_6, PAU, FS6, PAU, CS6, PAU, FS6, PAU, DS6, PAU, E_6, PAU, GS5, PAU, CS6, PAU, DS6, PAU, B_5, PAU, CS6, PAU, DS6, PAU, E_6, PAU, FS6, PAU, GS6, PAU, FS6, PAU, GS6, PAU, CS6, PAU, DS6, PAU, E_6, PAU, E_6, PAU, GS6, PAU, FS6, PAU, A_6, PAU, GS6, PAU, DS6, PAU, E_6, PAU, CS6, PAU, FS6, PAU, GS6, PAU, CS6, PAU, B_5, PAU, FS6, PAU, GS6, PAU, B_6, PAU, GS6, PAU, CS7, PAU, B_6, PAU, FS6, PAU, E_6, PAU, GS6, PAU, FS6, PAU, A_6, PAU, GS6, PAU, DS6, PAU, E_6, PAU, CS6, PAU, FS6, PAU, GS6, PAU, B_6, PAU, A_6, PAU, GS6, PAU, A_6, PAU, GS6, PAU, DS6, PAU, GS6, PAU, F_6, PAU, FS6, PAU, CS6, PAU, FS6, PAU, DS6, PAU, E_6, PAU, GS5, PAU, CS6, PAU, DS6, PAU, B_5, PAU, CS6, PAU, DS6, PAU, E_6, PAU, FS6, PAU, GS6, PAU, FS6, PAU, GS6, PAU, CS6, PAU, DS6, PAU, E_6, PAU, ENDSOUND,
  1921, 936, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 936, 24, 456, 24, 456, 24, 1416, 504, 936, 24, 456, 24, 456, 24, 1416, 504, 936, 24, 456, 24, 456, 24, 1416, 504, 936, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 504, 456, 24, 456, 24, 456, 24, 936, 264, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 1896, 24, 936, 24, 1416, 2424, 936, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 936, 24, 456, 24, 456, 24, 1416, 504, 936, 24, 456, 24, 456, 24, 1416, 504, 936, 24, 456, 24, 456, 24, 1416, 504, 936, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 504, 456, 24, 456, 24, 456, 24, 936, 264, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 1896, 24, 936, 24, 1416, 378,
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5
};

// Instrument: 0 patchchange ch: 3 pan flute;
const uint16 CAPITANO_TRACK_2[] =
{
  PAU, B_3, PAU, B_3, PAU, A_3, PAU, A_3, PAU, GS3, PAU, GS3, PAU, FS3, PAU, FS3, PAU, E_4, PAU, E_4, PAU, GS4, PAU, B_4, PAU, E_5, PAU, GS5, PAU, E_5, PAU, B_4, PAU, E_5, PAU, A_4, PAU, A_4, PAU, CS5, PAU, E_5, PAU, A_5, PAU, CS6, PAU, A_5, PAU, E_5, PAU, A_5, PAU, FS4, PAU, FS4, PAU, A_4, PAU, CS5, PAU, FS5, PAU, A_5, PAU, FS5, PAU, CS6, PAU, FS5, PAU, FS4, PAU, FS4, PAU, A_4, PAU, CS5, PAU, FS5, PAU, A_5, PAU, FS5, PAU, CS6, PAU, FS5, PAU, B_3, PAU, B_3, PAU, DS4, PAU, FS4, PAU, B_4, PAU, DS5, PAU, B_4, PAU, FS4, PAU, B_4, PAU, B_3, PAU, B_3, PAU, DS4, PAU, FS4, PAU, B_4, PAU, DS5, PAU, B_4, PAU, FS4, PAU, B_4, PAU, E_4, PAU, E_4, PAU, GS4, PAU, B_4, PAU, E_5, PAU, GS5, PAU, E_5, PAU, B_4, PAU, E_5, PAU, B_3, PAU, B_3, PAU, DS4, PAU, FS4, PAU, B_4, PAU, DS5, PAU, B_4, PAU, FS4, PAU, B_4, PAU, E_4, PAU, E_4, PAU, GS4, PAU, B_4, PAU, E_5, PAU, GS5, PAU, E_5, PAU, B_4, PAU, E_5, PAU, A_4, PAU, A_4, PAU, CS5, PAU, E_5, PAU, A_5, PAU, CS6, PAU, A_5, PAU, E_5, PAU, A_5, PAU, FS4, PAU, FS4, PAU, A_4, PAU, CS5, PAU, FS5, PAU, A_5, PAU, FS5, PAU, CS6, PAU, FS5, PAU, B_3, PAU, B_3, PAU, DS4, PAU, FS4, PAU, B_4, PAU, DS5, PAU, B_4, PAU, FS4, PAU, B_4, PAU, GS4, PAU, FS4, PAU, A_4, PAU, GS4, PAU, FS4, PAU, FS4, PAU, E_4, PAU, E_4, PAU, GS4, PAU, B_4, PAU, E_5, PAU, GS5, PAU, E_5, PAU, B_4, PAU, E_5, PAU, B_3, PAU, B_3, PAU, A_3, PAU, A_3, PAU, GS3, PAU, GS3, PAU, FS3, PAU, FS3, PAU, E_4, PAU, E_4, PAU, GS4, PAU, B_4, PAU, E_5, PAU, GS5, PAU, E_5, PAU, B_4, PAU, E_5, PAU, A_4, PAU, A_4, PAU, CS5, PAU, E_5, PAU, A_5, PAU, CS6, PAU, A_5, PAU, E_5, PAU, A_5, PAU, FS4, PAU, FS4, PAU, A_4, PAU, CS5, PAU, FS5, PAU, A_5, PAU, FS5, PAU, CS6, PAU, FS5, PAU, FS4, PAU, FS4, PAU, A_4, PAU, CS5, PAU, FS5, PAU, A_5, PAU, FS5, PAU, CS6, PAU, FS5, PAU, B_3, PAU, B_3, PAU, DS4, PAU, FS4, PAU, B_4, PAU, DS5, PAU, B_4, PAU, FS4, PAU, B_4, PAU, B_3, PAU, B_3, PAU, DS4, PAU, FS4, PAU, B_4, PAU, DS5, PAU, B_4, PAU, FS4, PAU, B_4, PAU, E_4, PAU, E_4, PAU, GS4, PAU, B_4, PAU, E_5, PAU, GS5, PAU, E_5, PAU, B_4, PAU, E_5, PAU, B_3, PAU, B_3, PAU, DS4, PAU, FS4, PAU, B_4, PAU, DS5, PAU, B_4, PAU, FS4, PAU, B_4, PAU, E_4, PAU, E_4, PAU, GS4, PAU, B_4, PAU, E_5, PAU, GS5, PAU, E_5, PAU, B_4, PAU, E_5, PAU, A_4, PAU, A_4, PAU, CS5, PAU, E_5, PAU, A_5, PAU, CS6, PAU, A_5, PAU, E_5, PAU, A_5, PAU, FS4, PAU, FS4, PAU, A_4, PAU, CS5, PAU, FS5, PAU, A_5, PAU, FS5, PAU, CS6, PAU, FS5, PAU, B_3, PAU, B_3, PAU, DS4, PAU, FS4, PAU, B_4, PAU, DS5, PAU, B_4, PAU, FS4, PAU, B_4, PAU, GS4, PAU, FS4, PAU, A_4, PAU, GS4, PAU, FS4, PAU, FS4, PAU, E_4, PAU, E_4, PAU, GS4, PAU, B_4, PAU, E_5, PAU, GS5, PAU, E_5, PAU, B_4, PAU, E_5, ENDSOUND,
  1, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 228, 732, 228, 732, 228, 732, 228, 732, 228, 3132, 228, 252, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 228, 732, 228, 732, 228, 732, 228, 732, 228, 3132, 228, 252, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114,
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5
};

// Instrument: 0 patchchange ch: 10 acoustic grand;
const uint16 CAPITANO_TRACK_3[] =
{
  PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, GS3, PAU, ENDSOUND,
  481, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 732, 228, 12, 228, 492, 228, 126,
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
};


SoundChannelConfigurationROM CAPITANO_CHANNEL_1_CONFIGURATION =
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

SoundChannelROM CAPITANO_CHANNEL_1 =
{
	/// Configuration
	(SoundChannelConfiguration*)&CAPITANO_CHANNEL_1_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const uint8*)CAPITANO_TRACK_1
	}
};

SoundChannelConfigurationROM CAPITANO_CHANNEL_2_CONFIGURATION =
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
	ViolinWaveForm,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelROM CAPITANO_CHANNEL_2 =
{
	/// Configuration
	(SoundChannelConfiguration*)&CAPITANO_CHANNEL_2_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const uint8*)CAPITANO_TRACK_2
	}
};

SoundChannelConfigurationROM CAPITANO_CHANNEL_3_CONFIGURATION =
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
	SawSquareWaveForm,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelROM CAPITANO_CHANNEL_3 =
{
	/// Configuration
	(SoundChannelConfiguration*)&CAPITANO_CHANNEL_3_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const uint8*)CAPITANO_TRACK_3
	}
};


SoundChannelROM* CAPITANOChannels[] =
{
	&CAPITANO_CHANNEL_1,
	&CAPITANO_CHANNEL_2,
	&CAPITANO_CHANNEL_3,
	NULL
};

SoundROM CapitanoSong =
{
	/// Name
	"Capitano",

	/// Play in loop
	true,

	/// Target timer resolution in us
	820,

	/// Tracks
	(SoundChannel**)CAPITANOChannels
};
