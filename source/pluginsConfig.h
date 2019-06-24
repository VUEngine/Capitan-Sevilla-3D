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

#ifndef PLUGINS_CONFIG_H_
#define PLUGINS_CONFIG_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <I18n.h>


//---------------------------------------------------------------------------------------------------------
//												PLUGINS
//---------------------------------------------------------------------------------------------------------

#define __SAVE_DATA_MANAGER_SAVE_STAMP							"CSevilla"

#define __SPLASH_SCREENS_USE_LOW_POWER_ENTITY					1

#define __AUTOMATIC_PAUSE_SELECTION_SCREEN_TITLE_TEXT			__TRANSLATE(STR_AUTOMATIC_PAUSE)
#define __AUTOMATIC_PAUSE_SELECTION_SCREEN_TITLE_TEXT_FONT		"DefaultFont"
#define __AUTOMATIC_PAUSE_SELECTION_SCREEN_BODY_TEXT			__TRANSLATE(STR_AUTO_PAUSE_EXPLANATION)
#define __AUTOMATIC_PAUSE_SELECTION_SCREEN_BODY_TEXT_FONT		"DefaultFont"
#define __AUTOMATIC_PAUSE_SELECTION_SCREEN_ON_TEXT				__TRANSLATE(STR_ON)
#define __AUTOMATIC_PAUSE_SELECTION_SCREEN_OFF_TEXT				__TRANSLATE(STR_OFF)
#define __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_TEXT_FONT	"DefaultFont"
#define __LANGUAGE_SELECTION_SCREEN_VARIANT						1
#define __LANGUAGE_SELECTION_SCREEN_TITLE_TEXT					__TRANSLATE(STR_LANGUAGE_SELECT)
#define __LANGUAGE_SELECTION_SCREEN_TITLE_TEXT_FONT				"DefaultFont"
#define __LANGUAGE_SELECTION_SCREEN_LANGUAGE_NAME_FONT			"DefaultFont"
#define __PRECAUTION_SCREEN_TEXT								__TRANSLATE(STR_PRECAUTION_SCREEN_TEXT)
#define __PRECAUTION_SCREEN_TEXT_FONT							"DefaultFont"

#define __AUTOMATIC_PAUSE_SCREEN_TITLE_TEXT						__TRANSLATE(STR_AUTOMATIC_PAUSE)
#define __AUTOMATIC_PAUSE_SCREEN_TITLE_TEXT_FONT				"DefaultFont"
#define __AUTOMATIC_PAUSE_SCREEN_BODY_TEXT						__TRANSLATE(STR_TAKE_A_REST)
#define __AUTOMATIC_PAUSE_SCREEN_BODY_TEXT_FONT					"DefaultFont"


#endif
