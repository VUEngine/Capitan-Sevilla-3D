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

extern EntitySpec FLAG_GERMANY_EN;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

/*
 * IMPORTANT: Ensure that this file is encoded in Windows-1252 or ISO-8859-1 ("ANSI") to make use
 * of the full extended ASCII character set including special characters of European languages.
 */

const char* const LANGUAGE_DE_STRINGS[] =
{
	/* Plugins */

	/* STR_AUTOMATIC_PAUSE */			"AUTOMATISCHE PAUSE",
	/* STR_AUTO_PAUSE_EXPLANATION */	" DIE AUTOMATISCHE PAUSE FUNKTION\nERINNERT DICH DARAN, DAS SPIEL CA.\n  ALLE 30 MINUTEN ZU PAUSIEREN",
	/* STR_LANGUAGE_SELECT */			"SPRACHAUSWAHL",
	/* STR_OFF */						"AUS",
	/* STR_ON */						"AN",
	/* STR_PRECAUTION_SCREEN_TEXT */	"        WICHTIG\n\nBITTE LESEN SIE VOR DEM\n\n SPIELEN DIE ANLEITUNG\n\nUND SICHERHEITSHINWEISE",


	/* General */

	/* STR_ARE_YOU_SURE */				"BIST DU SICHER?",
	/* STR_BACK */						"ZURÜCK",
	/* STR_CONTINUE */					"FORTSETZEN",
	/* STR_CREDITS */					"MITWIRKENDE",
	/* STR_LANGUAGE */					"SPRACHE",
	/* STR_LEVEL */						"LEVEL",
	/* STR_NEW_BEST */					"NEUE BESTLEISTUNG!",
	/* STR_NEW_GAME */					"NEUES SPIEL",
	/* STR_NO */						"NEIN",
	/* STR_OPTIONS */					"OPTIONEN",
	/* STR_PAUSE */						"PAUSE",
	/* STR_PRESENTS */					"PRÄSENTIERT",
	/* STR_PRESS_START_BUTTON */		"START-KNOPF DRÜCKEN",
	/* STR_QUIT_GAME */					"SPIEL BEENDEN",
	/* STR_SELECT */					"AUSWÄHLEN",
	/* STR_TAKE_A_REST */				"BITTE MACHE EINE PAUSE!",
	/* STR_YES */						"JA",

	/* LEVELS */

	/* STR_LEVEL_1_NAME */				"SEVILLA, MISSION:\nBESORGE DAS BUCH",
};

const LangROMSpec LANGUAGE_DE =
{
	// Language Name
	"DEUTSCH",

	// Flag Entity
	&FLAG_GERMANY_EN,

	// Strings
	(const char**)LANGUAGE_DE_STRINGS
};

