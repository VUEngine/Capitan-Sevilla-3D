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

extern EntityDefinition FLAG_FRANCE_EN;


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

	/* STR_AUTOMATIC_PAUSE */			"Pause Automatique",
	/* STR_AUTO_PAUSE_EXPLANATION */	"  La fonction Pause automatique va\nvous rappelerez de prendre une pause\n  de jeu chaque 30 minutes environ",
	/* STR_LANGUAGE_SELECT */			"Choix de la langue",
	/* STR_OFF */						"Desactivé",
	/* STR_ON */						"Activé",
	/* STR_PRECAUTION_SCREEN_TEXT */	"        Important\n\nPrenez conaissance de la\n\nnotice et des précautions\n\na avant de jouer",

    /* General */

	/* STR_ARE_YOU_SURE */				"Es tu sûr?",
	/* STR_BACK */						"Arrière",
	/* STR_CHECKPOINT */				"Poste de contrôle",
	/* STR_CONTINUE */					"Continuer",
	/* STR_CREDITS */					"Crédits",
	/* STR_LANGUAGE */					"Langue",
	/* STR_LEVEL */						"Niveau",
	/* STR_LEVEL_CONQUERED */			"Niveau conquis!",
	/* STR_LEVEL_DONE */				"Niveau terminé!",
	/* STR_NEW_BEST */					"Nouveau Record!",
	/* STR_NEW_GAME */					"Nouveau Jeu",
	/* STR_NO */						"Non",
	/* STR_OPTIONS */					"Options",
	/* STR_PAUSE */						"Pause",
	/* STR_PRESENTS */					"Présente",
	/* STR_PRESS_START_BUTTON */		"Appuyer sur Start",
	/* STR_PROGRESS_WILL_BE_ERASED */	"Tout vôtre progrès sera effacé.",
	/* STR_QUIT_LEVEL */				"Quitter Niveau",
	/* STR_SELECT */					"Sélectionner",
	/* STR_TAKE_A_REST */				"Se il vous plaît, prendre un repos!",
	/* STR_YES */						"Oui",

	/* Levels */

	/* STR_LEVEL_1_NAME */				"Sevilla, Mission:\nRetrieve the book",
};

const LangROMDef LANGUAGE_FR =
{
	// Language Name
	"Français",

	// Flag Entity
	&FLAG_FRANCE_EN,

	// Strings
	(const char**)LANGUAGE_FR_STRINGS
};
