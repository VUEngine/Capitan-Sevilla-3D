/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2019 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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

// Instrument: 0 patchchange ch: 1 drawbar organ;
const u16 CAPITANO_TRACK_1[] =
{
  PAU, E_6, PAU, GS6, PAU, FS6, PAU, A_6, PAU, GS6, PAU, DS6, PAU, E_6, PAU, CS6, PAU, FS6, PAU, GS6, PAU, CS6, PAU, B_5, PAU, FS6, PAU, GS6, PAU, B_6, PAU, GS6, PAU, CS7, PAU, B_6, PAU, FS6, PAU, E_6, PAU, GS6, PAU, FS6, PAU, A_6, PAU, GS6, PAU, DS6, PAU, E_6, PAU, CS6, PAU, FS6, PAU, GS6, PAU, B_6, PAU, A_6, PAU, GS6, PAU, A_6, PAU, GS6, PAU, DS6, PAU, GS6, PAU, F_6, PAU, FS6, PAU, CS6, PAU, FS6, PAU, DS6, PAU, E_6, PAU, GS5, PAU, CS6, PAU, DS6, PAU, B_5, PAU, CS6, PAU, DS6, PAU, E_6, PAU, FS6, PAU, GS6, PAU, FS6, PAU, GS6, PAU, CS6, PAU, DS6, PAU, E_6, PAU, E_6, PAU, GS6, PAU, FS6, PAU, A_6, PAU, GS6, PAU, DS6, PAU, E_6, PAU, CS6, PAU, FS6, PAU, GS6, PAU, CS6, PAU, B_5, PAU, FS6, PAU, GS6, PAU, B_6, PAU, GS6, PAU, CS7, PAU, B_6, PAU, FS6, PAU, E_6, PAU, GS6, PAU, FS6, PAU, A_6, PAU, GS6, PAU, DS6, PAU, E_6, PAU, CS6, PAU, FS6, PAU, GS6, PAU, B_6, PAU, A_6, PAU, GS6, PAU, A_6, PAU, GS6, PAU, DS6, PAU, GS6, PAU, F_6, PAU, FS6, PAU, CS6, PAU, FS6, PAU, DS6, PAU, E_6, PAU, GS5, PAU, CS6, PAU, DS6, PAU, B_5, PAU, CS6, PAU, DS6, PAU, E_6, PAU, FS6, PAU, GS6, PAU, FS6, PAU, GS6, PAU, CS6, PAU, DS6, PAU, E_6, PAU, ENDSOUND,
  1921, 936, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 936, 24, 456, 24, 456, 24, 1416, 504, 936, 24, 456, 24, 456, 24, 1416, 504, 936, 24, 456, 24, 456, 24, 1416, 504, 936, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 504, 456, 24, 456, 24, 456, 24, 936, 264, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 1896, 24, 936, 24, 1416, 2424, 936, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 936, 24, 456, 24, 456, 24, 1416, 504, 936, 24, 456, 24, 456, 24, 1416, 504, 936, 24, 456, 24, 456, 24, 1416, 504, 936, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 24, 456, 504, 456, 24, 456, 24, 456, 24, 936, 264, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 1896, 24, 936, 24, 1416, 378,
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5
};

// Instrument: 0 patchchange ch: 3 pan flute;
const u16 CAPITANO_TRACK_2[] =
{
  PAU, B_3, PAU, B_3, PAU, A_3, PAU, A_3, PAU, GS3, PAU, GS3, PAU, FS3, PAU, FS3, PAU, E_4, PAU, E_4, PAU, GS4, PAU, B_4, PAU, E_5, PAU, GS5, PAU, E_5, PAU, B_4, PAU, E_5, PAU, A_4, PAU, A_4, PAU, CS5, PAU, E_5, PAU, A_5, PAU, CS6, PAU, A_5, PAU, E_5, PAU, A_5, PAU, FS4, PAU, FS4, PAU, A_4, PAU, CS5, PAU, FS5, PAU, A_5, PAU, FS5, PAU, CS6, PAU, FS5, PAU, FS4, PAU, FS4, PAU, A_4, PAU, CS5, PAU, FS5, PAU, A_5, PAU, FS5, PAU, CS6, PAU, FS5, PAU, B_3, PAU, B_3, PAU, DS4, PAU, FS4, PAU, B_4, PAU, DS5, PAU, B_4, PAU, FS4, PAU, B_4, PAU, B_3, PAU, B_3, PAU, DS4, PAU, FS4, PAU, B_4, PAU, DS5, PAU, B_4, PAU, FS4, PAU, B_4, PAU, E_4, PAU, E_4, PAU, GS4, PAU, B_4, PAU, E_5, PAU, GS5, PAU, E_5, PAU, B_4, PAU, E_5, PAU, B_3, PAU, B_3, PAU, DS4, PAU, FS4, PAU, B_4, PAU, DS5, PAU, B_4, PAU, FS4, PAU, B_4, PAU, E_4, PAU, E_4, PAU, GS4, PAU, B_4, PAU, E_5, PAU, GS5, PAU, E_5, PAU, B_4, PAU, E_5, PAU, A_4, PAU, A_4, PAU, CS5, PAU, E_5, PAU, A_5, PAU, CS6, PAU, A_5, PAU, E_5, PAU, A_5, PAU, FS4, PAU, FS4, PAU, A_4, PAU, CS5, PAU, FS5, PAU, A_5, PAU, FS5, PAU, CS6, PAU, FS5, PAU, B_3, PAU, B_3, PAU, DS4, PAU, FS4, PAU, B_4, PAU, DS5, PAU, B_4, PAU, FS4, PAU, B_4, PAU, GS4, PAU, FS4, PAU, A_4, PAU, GS4, PAU, FS4, PAU, FS4, PAU, E_4, PAU, E_4, PAU, GS4, PAU, B_4, PAU, E_5, PAU, GS5, PAU, E_5, PAU, B_4, PAU, E_5, PAU, B_3, PAU, B_3, PAU, A_3, PAU, A_3, PAU, GS3, PAU, GS3, PAU, FS3, PAU, FS3, PAU, E_4, PAU, E_4, PAU, GS4, PAU, B_4, PAU, E_5, PAU, GS5, PAU, E_5, PAU, B_4, PAU, E_5, PAU, A_4, PAU, A_4, PAU, CS5, PAU, E_5, PAU, A_5, PAU, CS6, PAU, A_5, PAU, E_5, PAU, A_5, PAU, FS4, PAU, FS4, PAU, A_4, PAU, CS5, PAU, FS5, PAU, A_5, PAU, FS5, PAU, CS6, PAU, FS5, PAU, FS4, PAU, FS4, PAU, A_4, PAU, CS5, PAU, FS5, PAU, A_5, PAU, FS5, PAU, CS6, PAU, FS5, PAU, B_3, PAU, B_3, PAU, DS4, PAU, FS4, PAU, B_4, PAU, DS5, PAU, B_4, PAU, FS4, PAU, B_4, PAU, B_3, PAU, B_3, PAU, DS4, PAU, FS4, PAU, B_4, PAU, DS5, PAU, B_4, PAU, FS4, PAU, B_4, PAU, E_4, PAU, E_4, PAU, GS4, PAU, B_4, PAU, E_5, PAU, GS5, PAU, E_5, PAU, B_4, PAU, E_5, PAU, B_3, PAU, B_3, PAU, DS4, PAU, FS4, PAU, B_4, PAU, DS5, PAU, B_4, PAU, FS4, PAU, B_4, PAU, E_4, PAU, E_4, PAU, GS4, PAU, B_4, PAU, E_5, PAU, GS5, PAU, E_5, PAU, B_4, PAU, E_5, PAU, A_4, PAU, A_4, PAU, CS5, PAU, E_5, PAU, A_5, PAU, CS6, PAU, A_5, PAU, E_5, PAU, A_5, PAU, FS4, PAU, FS4, PAU, A_4, PAU, CS5, PAU, FS5, PAU, A_5, PAU, FS5, PAU, CS6, PAU, FS5, PAU, B_3, PAU, B_3, PAU, DS4, PAU, FS4, PAU, B_4, PAU, DS5, PAU, B_4, PAU, FS4, PAU, B_4, PAU, GS4, PAU, FS4, PAU, A_4, PAU, GS4, PAU, FS4, PAU, FS4, PAU, E_4, PAU, E_4, PAU, GS4, PAU, B_4, PAU, E_5, PAU, GS5, PAU, E_5, PAU, B_4, PAU, E_5, ENDSOUND,
  1, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 228, 732, 228, 732, 228, 732, 228, 732, 228, 3132, 228, 252, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 228, 12, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 228, 732, 228, 732, 228, 732, 228, 732, 228, 3132, 228, 252, 114, 126, 114, 6, 114, 6, 114, 126, 114, 126, 114, 126, 114, 126, 114, 126, 114,
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5
};

// Instrument: 0 patchchange ch: 10 acoustic grand;
const u16 CAPITANO_TRACK_3[] =
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
	squareWaveForm,

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
		(const u8*)CAPITANO_TRACK_1
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
	violinWaveForm,

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
		(const u8*)CAPITANO_TRACK_2
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
	sawSquareWaveForm,

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
		(const u8*)CAPITANO_TRACK_3
	}
};


SoundChannelROM* CAPITANO_CHANNELS[] =
{
	&CAPITANO_CHANNEL_1,
	&CAPITANO_CHANNEL_2,
	&CAPITANO_CHANNEL_3,
	NULL
};

SoundROM CAPITANO_SONG =
{
	/// Name
	"Capitano",

	/// Play in loop
	true,

	/// Target timer resolution in us
	820,

	/// Tracks
	(SoundChannel**)CAPITANO_CHANNELS
};
