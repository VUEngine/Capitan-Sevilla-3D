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

#include <Entity.h>
#include <I18n.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern EntitySpec FLAG_UNITED_KINGDOM_EN;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

/*
 * IMPORTANT: Ensure that this file is encoded in Windows-1252 or ISO-8859-1 ("ANSI") to make use
 * of the full extended ASCII character set including special characters of European languages.
 */

const char* const LANGUAGE_EN_STRINGS[] =
{
	/* Plugins */

	/* STR_AUTOMATIC_PAUSE */			"AUTOMATIC PAUSE",
	/* STR_AUTO_PAUSE_EXPLANATION */	"THE AUTOMATIC PAUSE FEATURE WILL\nREMIND YOU TO TAKE A BREAK FROM\nPLAYING APPROX. EVERY 30 MINUTES",
	/* STR_LANGUAGE_SELECT */			"LANGUAGE SELECT",
	/* STR_OFF */						"OFF",
	/* STR_ON */						"ON",
	/* STR_PRECAUTION_SCREEN_TEXT */	"     IMPORTANT\n\nREAD INSTRUCTION AND\n\nPRECAUTION BOOKLETS\n\n  BEFORE OPERATING",

    /* General */

	/* STR_ARE_YOU_SURE */				"ARE YOU SURE?",
	/* STR_BACK */						"BACK",
	/* STR_CONTINUE */					"CONTINUE",
	/* STR_CREDITS */					"CREDITS",
	/* STR_LANGUAGE */					"LANGUAGE",
	/* STR_LEVEL */						"LEVEL",
	/* STR_NEW_BEST */					"NEW BEST!",
	/* STR_NEW_GAME */					"NEW GAME",
	/* STR_NO */						"NO",
	/* STR_OPTIONS */					"OPTIONS",
	/* STR_PAUSE */						"PAUSE",
	/* STR_PRESENTS */					"PRESENTS",
	/* STR_PRESS_START_BUTTON */		"PRESS START BUTTON",
	/* STR_QUIT_GAME */					"QUIT GAME",
	/* STR_SELECT */					"SELECT",
	/* STR_TAKE_A_REST */				"PLEASE TAKE A REST!",
	/* STR_YES */						"YES",

	/* Levels */

	/* STR_LEVEL_1_NAME */				"SEVILLA,\nMISSION:\nRETRIEVE THE BOOK",
};

const LangROMSpec LANGUAGE_EN =
{
	// Language Name
	"ENGLISH",

	// Flag Entity
	&FLAG_UNITED_KINGDOM_EN,

	// Strings
	(const char**)LANGUAGE_EN_STRINGS
};
