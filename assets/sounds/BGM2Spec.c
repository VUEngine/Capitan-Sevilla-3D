/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

const u16 KRISSE_BGM[][2] =
{
	{
		//songlength
		68,
		//stdwait
		0x12,
	},
	{
		//stdSxLRV
		0x33,
		//stdSxEV0
		0x31,
	},
	{
		//stdSxEV1
		0x00,
		//stdSxRAM
		0x01,
	},
	//stdS5SWP
	//0x00,
	//song's notes
	{NONE,NONE,},
	{NONE,NONE,},
	{NONE,NONE,},
	{NONE,NONE,},
	{F_4,F_5,},
	{NONE,NONE,},
	{NONE,NONE,},
	{NONE,D_4,},
	{NONE,F_6,},
	{NONE,NONE,},
	{NONE,E_3,},
	{NONE,F_5,},
	{NONE,NONE,},
	{NONE,C_4,},
	{NONE,F_6,},
	{NONE,NONE,},
	{C_4,F_5,},
	{NONE,NONE,},
	{NONE,C_4,},
	{NONE,NONE,},
	{F_4,F_5,},
	{NONE,NONE,},
	{NONE,NONE,},
	{NONE,D_4,},
	{NONE,F_6,},
	{NONE,NONE,},
	{NONE,E_4,},
	{NONE,F_5,},
	{NONE,NONE,},
	{NONE,C_4,},
	{NONE,F_6,},
	{NONE,NONE,},
	{C_4,F_5,},
	{NONE,NONE,},
	{NONE,C_4,},
	{NONE,NONE,},
	{F_4,F_6,},
	{NONE,F_5,},
	{NONE,NONE,},
	{NONE,D_4,},
	{NONE,NONE,},
	{NONE,NONE,},
	{NONE,E_4,},
	{NONE,NONE,},
	{NONE,NONE,},
	{NONE,C_4,},
	{NONE,NONE,},
	{NONE,NONE,},
	{NONE,C_4,},
	{NONE,NONE,},
	{NONE,C_4,},
	{NONE,NONE,},
	{NONE,F_4,},
	{NONE,NONE,},
	{NONE,NONE,},
	{NONE,D_4,},
	{NONE,NONE,},
	{NONE,NONE,},
	{NONE,E_4,},
	{NONE,NONE,},
	{NONE,NONE,},
	{NONE,C_4,},
	{NONE,NONE,},
	{NONE,NONE,},
	{NONE,C_4,},
	{NONE,NONE,},
	{NONE,C_4,},
	{NONE,NONE},
};
