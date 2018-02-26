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

#include <GameEvents.h>
#include <Game.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Box.h>
#include <PhysicalWorld.h>
#include "Gui.h"
#include <PlatformerLevelState.h>
#include <ProgressManager.h>
#include <EventManager.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Gui, Entity);


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void Gui_printAll(Gui this);
static void Gui_onSecondChange(Gui this, Object eventFirer);
static void Gui_onHitTaken(Gui this, Object eventFirer);


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern CharSetDefinition GUI_CH;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Gui, EntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(Gui, animatedEntityDefinition, id, internalId, name);

// class's constructor
void Gui_constructor(Gui this, EntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(Entity, animatedEntityDefinition, id, internalId, name);

	// add event listeners
	Object_addEventListener(__SAFE_CAST(Object, PlatformerLevelState_getClock(PlatformerLevelState_getInstance())), __SAFE_CAST(Object, this), (EventListener)Gui_onSecondChange, kEventSecondChanged);
	Object_addEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)Gui_onHitTaken, kEventHitTaken);
}

// class's destructor
void Gui_destructor(Gui this)
{
	// remove event listeners
	Object_removeEventListener(__SAFE_CAST(Object, PlatformerLevelState_getClock(PlatformerLevelState_getInstance())), __SAFE_CAST(Object, this), (EventListener)Gui_onSecondChange, kEventSecondChanged);
	Object_removeEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)Gui_onHitTaken, kEventHitTaken);

	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

void Gui_ready(Gui this, bool recursive)
{
	ASSERT(this, "Gui::ready: null this");

	Gui_printAll(this);

	// call base
	__CALL_BASE_METHOD(Entity, ready, this, recursive);
}

void Gui_printClock(Gui this __attribute__ ((unused)))
{
	Printing_text(Printing_getInstance(), "00", GUI_X_POS + 37, GUI_Y_POS, NULL);
	//Clock_print(PlatformerLevelState_getClock(PlatformerLevelState_getInstance()), GUI_X_POS + 37, GUI_Y_POS, NULL);
}

void Gui_printSausages(Gui this __attribute__ ((unused)))
{
	Printing_text(Printing_getInstance(), "X00", GUI_X_POS + 28, GUI_Y_POS, NULL);
}

void Gui_printLives(Gui this __attribute__ ((unused)))
{
	Printing_text(Printing_getInstance(), "X00", GUI_X_POS + 44, GUI_Y_POS, NULL);
	Printing_int(Printing_getInstance(), 3, GUI_X_POS + 46, GUI_Y_POS, NULL);
}

void Gui_printAll(Gui this)
{
	Gui_printClock(this);
	Gui_printLives(this);
	Gui_printSausages(this);
}

// handle event
static void Gui_onSecondChange(Gui this, Object eventFirer __attribute__ ((unused)))
{
#ifdef __DEBUG_TOOLS
	if(!Game_isInSpecialMode(Game_getInstance()))
#endif
#ifdef __STAGE_EDITOR
	if(!Game_isInSpecialMode(Game_getInstance()))
#endif
#ifdef __ANIMATION_INSPECTOR
	if(!Game_isInSpecialMode(Game_getInstance()))
#endif

	Gui_printClock(this);
}

// handle event
static void Gui_onHitTaken(Gui this, Object eventFirer __attribute__ ((unused)))
{
	Gui_printLives(this);
}
