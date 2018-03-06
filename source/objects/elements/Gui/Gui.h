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

#ifndef GUI_H_
#define GUI_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Entity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Gui_METHODS(ClassName)																			\
		Entity_METHODS(ClassName)																		\

#define Gui_SET_VTABLE(ClassName)																		\
		Entity_SET_VTABLE(ClassName)																	\
		__VIRTUAL_SET(ClassName, Gui, ready);															\
		__VIRTUAL_SET(ClassName, Gui, resume);															\

__CLASS(Gui);

#define Gui_ATTRIBUTES																					\
		Entity_ATTRIBUTES																				\
		u8 timeRemaining;																				\


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define GUI_X_POS	0
#define GUI_Y_POS	25


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(Gui, EntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name);

void Gui_constructor(Gui this, EntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name);
void Gui_destructor(Gui this);
void Gui_ready(Gui this, bool recursive);
void Gui_resume(Gui this);
void Gui_printClock(Gui this);
void Gui_printLives(Gui this);
void Gui_printSausages(Gui this);
void Gui_printAll(Gui this);


#endif
