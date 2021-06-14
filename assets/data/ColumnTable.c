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

#include <VIPManager.h>


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

ColumnTableROMSpec SQUARE_SCREEN_TEST_COLUMN_TABLE =
{
	// mirror spec?
	true,

	// column table spec
	{
		0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe,
		0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe,
		0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe,
		0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe,
		0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe,
		0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe,
		0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe,
		0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe,
		0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c,
		0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c,
		0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c,
		0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c,
		0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c,
		0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c,
		0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c,
		0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c,
	}
};

BrightnessRepeatROMSpec EDGE_FADE_OUT_BRIGHTNESS_REPEAT =
{
	// mirror spec?
	true,

	// brightness repeat values
	{
		 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
		16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
		16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
	}
};

BrightnessRepeatROMSpec EDGE_FADE_OUT_WIDE_BRIGHTNESS_REPEAT =
{
	// mirror spec?
	true,

	// brightness repeat values
	{
		 0,  0,  1,  1,  2,  2,  3,  3,  4,  4,  5,  5,  6,  6,  7,  7,
		 8,  8,  9,  9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15,
		16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
	}
};

BrightnessRepeatROMSpec EDGE_FADE_OUT_VERY_WIDE_BRIGHTNESS_REPEAT =
{
	// mirror spec?
	true,

	// brightness repeat values
	{
		 0,  0,  0,  1,  1,  1,  2,  2,  2,  3,  3,  3,  4,  4,  4,  5,
		 5,  5,  6,  6,  6,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10, 10,
		10, 11, 11, 11, 12, 12, 12, 13, 13, 13, 14, 14, 14, 15, 15, 15,
	}
};
