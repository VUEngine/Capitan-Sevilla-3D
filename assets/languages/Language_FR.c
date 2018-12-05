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

extern EntitySpec FLAG_FRANCE_EN;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

/*
 * IMPORTANT: Ensure that this file is encoded in Windows-1252 or ISO-8859-1 ("ANSI") to make use
 * of the full extended ASCII character set including special characters of European languages.
 */

const char* const LANGUAGE_FR_STRINGS[] =
{
	/* Plugins */

	/* STR_AUTOMATIC_PAUSE */			"PAUSE AUTOMATIQUE",
	/* STR_AUTO_PAUSE_EXPLANATION */	"  LA FONCTION PAUSE AUTOMATIQUE VA\nVOUS RAPPELEREZ DE PRENDRE UNE PAUSE\n  DE JEU CHAQUE 30 MINUTES ENVIRON",
	/* STR_LANGUAGE_SELECT */			"CHOIX DE LA LANGUE",
	/* STR_OFF */						"DESACTIVÉ",
	/* STR_ON */						"ACTIVÉ",
	/* STR_PRECAUTION_SCREEN_TEXT */	"        IMPORTANT\n\nPRENEZ CONAISSANCE DE LA\n\nNOTICE ET DES PRÉCAUTIONS\n\n    A AVANT DE JOUER",

    /* General */

	/* STR_ARE_YOU_SURE */				"ES TU SÛR?",
	/* STR_BACK */						"ARRIÈRE",
	/* STR_CONTINUE */					"CONTINUER",
	/* STR_CREDITS */					"CRÉDITS",
	/* STR_LANGUAGE */					"LANGUE",
	/* STR_LEVEL */						"NIVEAU",
	/* STR_NEW_BEST */					"NOUVEAU RECORD!",
	/* STR_NEW_GAME */					"NOUVEAU JEU",
	/* STR_NO */						"NON",
	/* STR_OPTIONS */					"OPTIONS",
	/* STR_PAUSE */						"PAUSE",
	/* STR_PRESENTS */					"PRÉSENTE",
	/* STR_PRESS_START_BUTTON */		"APPUYER SUR START",
	/* STR_QUIT_GAME */					"QUITTER JEU",
	/* STR_SELECT */					"SÉLECTIONNER",
	/* STR_TAKE_A_REST */				"SE IL VOUS PLAÎT, PRENDRE UN REPOS!",
	/* STR_YES */						"OUI",

	/* LEVELS */

	/* STR_LEVEL_1_NAME */				"SEVILLA, MISSION:\nRETRIEVE THE BOOK",
};

const LangROMSpec LANGUAGE_FR =
{
	// Language Name
	"FRANÇAIS",

	// Flag Entity
	&FLAG_FRANCE_EN,

	// Strings
	(const char**)LANGUAGE_FR_STRINGS
};
