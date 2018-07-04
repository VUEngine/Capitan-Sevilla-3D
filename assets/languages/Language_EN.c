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

extern EntityDefinition FLAG_UNITED_KINGDOM_EN;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

/*
 * IMPORTANT: Ensure that this file is encoded in Windows-1252 or ISO-8859-1 ("ANSI") to make use
 * of the full extended ASCII character set including special characters of European languages.
 */

const char* const LANGUAGE_EN_STRINGS[] =
{
	/* Components */

	/* STR_AUTOMATIC_PAUSE */			"Automatic Pause",
	/* STR_AUTO_PAUSE_EXPLANATION */	"The Automatic Pause feature will\nremind you to take a break from\nplaying approx. every 30 minutes",
	/* STR_LANGUAGE_SELECT */			"Language Select",
	/* STR_OFF */						"Off",
	/* STR_ON */						"On",
	/* STR_PRECAUTION_SCREEN_TEXT */	"     Important\n\nRead Instruction and\n\nPrecaution Booklets\n\n  before operating",

    /* General */

	/* STR_ARE_YOU_SURE */				"Are you sure?",
	/* STR_BACK */						"Back",
	/* STR_CHECKPOINT */				"Checkpoint",
	/* STR_CONTINUE */					"Continue",
	/* STR_CREDITS */					"Credits",
	/* STR_LANGUAGE */					"Language",
	/* STR_LEVEL */						"Level",
	/* STR_LEVEL_CONQUERED */			"Level Conquered!",
	/* STR_LEVEL_DONE */				"Level Completed!",
	/* STR_NEW_BEST */					"New Best!",
	/* STR_NEW_GAME */					"New Game",
	/* STR_NO */						"No",
	/* STR_OPTIONS */					"Options",
	/* STR_PAUSE */						"Pause",
	/* STR_PRESENTS */					"Presents",
	/* STR_PRESS_START_BUTTON */		"Press Start Button",
	/* STR_PROGRESS_WILL_BE_ERASED */	"All your progress will be erased.",
	/* STR_QUIT_LEVEL */				"Quit Level",
	/* STR_SELECT */					"Select",
	/* STR_TAKE_A_REST */				"Please take a rest!",
	/* STR_YES */						"Yes",

	/* Levels */

	/* STR_LEVEL_1_NAME */				"Sevilla,\nMission:\nRetrieve the book",
};

const LangROMDef LANGUAGE_EN =
{
	// Language Name
	"English",

	// Flag Entity
	&FLAG_UNITED_KINGDOM_EN,

	// Strings
	(const char**)LANGUAGE_EN_STRINGS
};
