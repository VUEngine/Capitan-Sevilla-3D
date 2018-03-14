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

#include <I18n.h>


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

/*
 * IMPORTANT: Ensure that this file is encoded in Windows-1252 or ISO-8859-1 ("ANSI") to make use
 * of the full extended ASCII character set including special characters of European languages.
 *
 * The following character is meant to prevent editors from loading this file as UTF-8, since it doesn't
 * form part of a valid UTF-8 byte sequence: £
 */

const char* const LANGUAGE_ES_STRINGS[] =
{
	/* General */

	/* STR_ARE_YOU_SURE */				"¿Estás seguro?",
	/* STR_AUTOMATIC_PAUSE */			"Pausa Automatica", //"Pausa Automática",
	/* STR_BACK */						"Regresar",
	/* STR_CHECKPOINT */				"Punto de control",
	/* STR_CONTINUE */					"Continuar",
	/* STR_CREDITS */					"Créditos",
	/* STR_IMPORTANT */					"Importante",
	/* STR_LANGUAGE */					"Idioma",
	/* STR_LANGUAGE_SELECT */			"Seleccionar Idioma",
	/* STR_LEVEL */						"Nivel",
	/* STR_LEVEL_CONQUERED */			"¡Nivel conquistado!",
	/* STR_LEVEL_DONE */				"¡Nivel completo!",
	/* STR_NEW_BEST */					"¡Nuevo récord!",
	/* STR_NEW_GAME */					"Nuevo Juego",
	/* STR_NO */						"No",
	/* STR_OFF */						"Apagado",
	/* STR_ON */						"Encendido",
	/* STR_OPTIONS */					"Opciones",
	/* STR_PAUSE */						"Pausa",
	/* STR_PRESENTS */					"Presenta",
	/* STR_PRESS_START_BUTTON */		"Presionar Start",
	/* STR_PROGRESS_WILL_BE_ERASED */	"Esto eliminará todo tu progreso.",
	/* STR_QUIT_LEVEL */				"Salir del nivel",
	/* STR_SELECT */					"Seleccionar",
	/* STR_TAKE_A_REST */				"¡Por favor, tómate un descanso!",
	/* STR_YES */						"Sí",

	/* Splash Screens */

	/* STR_PRECAUTION_SCREEN_TEXT */	"      Lee los libros de\n\nInstrucciones y Precauciones\n\n       antes de jugar",
	/* STR_AUTO_PAUSE_EXPLANATION */	" La función automática de pausa te\nrecordará que debes tomar un descanso\n  approximadamente cada 30 minutos",

	/* Levels */

	/* STR_LEVEL_1_NAME */				"Montanas Splish Splash", //"Montañas Splish Splash",
	/* STR_LEVEL_1_SLOGAN */			"\"Nublado con pronóstico\n       de lluvia\"",
};

const LangROMDef LANGUAGE_ES =
{
	// Language Name
	"Español",

	// Strings
	(const char**)LANGUAGE_ES_STRINGS
};
