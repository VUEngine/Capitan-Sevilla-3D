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

extern EntityDefinition FLAG_SPAIN_EN;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

/*
 * IMPORTANT: Ensure that this file is encoded in Windows-1252 or ISO-8859-1 ("ANSI") to make use
 * of the full extended ASCII character set including special characters of European languages.
 */

const char* const LANGUAGE_ES_STRINGS[] =
{
	/* Plugins */

	/* STR_AUTOMATIC_PAUSE */			"PAUSA AUTOMÁTICA",
	/* STR_AUTO_PAUSE_EXPLANATION */	"  LA FUNCIÓN AUTOMÁTICA DE PAUSA TE\nRECORDARÁ QUE DEBES TOMAR UN DESCANSO\n  APPROXIMADAMENTE CADA 30 MINUTOS",
	/* STR_LANGUAGE_SELECT */			"SELECCIONAR IDIOMA",
	/* STR_OFF */						"APAGADO",
	/* STR_ON */						"ENCENDIDO",
	/* STR_PRECAUTION_SCREEN_TEXT */	"     IMPORTANTE\n\n  ANTES DE COMENZAR  \n\nLEER LAS INDICACIONES\n\nDEL MANUAL DE USUARIO",

    /* General */

	/* STR_ARE_YOU_SURE */				"¿ESTÁS SEGURO?",
	/* STR_BACK */						"REGRESAR",
	/* STR_CONTINUE */					"CONTINUAR",
	/* STR_CREDITS */					"CRÉDITOS",
	/* STR_LANGUAGE */					"IDIOMA",
	/* STR_LEVEL */						"NIVEL",
	/* STR_NEW_BEST */					"¡NUEVO RÉCORD!",
	/* STR_NEW_GAME */					"NUEVO JUEGO",
	/* STR_NO */						"NO",
	/* STR_OPTIONS */					"OPCIONES",
	/* STR_PAUSE */						"PAUSA",
	/* STR_PRESENTS */					"PRESENTA",
	/* STR_PRESS_START_BUTTON */		"PRESIONAR START",
	/* STR_QUIT_GAME */					"SALIR DEL JUEGO",
	/* STR_SELECT */					"SELECCIONAR",
	/* STR_TAKE_A_REST */				"¡POR FAVOR, TÓMATE UN DESCANSO!",
	/* STR_YES */						"SÍ",

	/* LEVELS */

	/* STR_LEVEL_1_NAME */				"SEVILLA,\nMISION:\nRECUPERAR EL LIBRO",
};

const LangROMDef LANGUAGE_ES =
{
	// Language Name
	"ESPAÑOL",

	// Flag Entity
	&FLAG_SPAIN_EN,

	// Strings
	(const char**)LANGUAGE_ES_STRINGS
};
