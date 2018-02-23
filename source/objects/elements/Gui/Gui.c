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

__CLASS_DEFINITION(Gui, AnimatedEntity);


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void Gui_printAll(Gui this);
static void Gui_onSecondChange(Gui this, Object eventFirer);
static void Gui_onHitTaken(Gui this, Object eventFirer);
static void Gui_onCoinTaken(Gui this, Object eventFirer);
static void Gui_onKeyTaken(Gui this, Object eventFirer);
static void Gui_onPowerUp(Gui this, Object eventFirer);


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern CharSetDefinition GUI_CH;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Gui, AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(Gui, animatedEntityDefinition, id, internalId, name);

// class's constructor
void Gui_constructor(Gui this, AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(AnimatedEntity, animatedEntityDefinition, id, internalId, name);

	// add event listeners
	Object_addEventListener(__SAFE_CAST(Object, PlatformerLevelState_getClock(PlatformerLevelState_getInstance())), __SAFE_CAST(Object, this), (EventListener)Gui_onSecondChange, kEventSecondChanged);
	Object_addEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)Gui_onHitTaken, kEventHitTaken);
	Object_addEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)Gui_onCoinTaken, kEventCoinTaken);
	Object_addEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)Gui_onKeyTaken, kEventKeyTaken);
	Object_addEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)Gui_onPowerUp, kEventPowerUp);
}

// class's destructor
void Gui_destructor(Gui this)
{
	// remove event listeners
	Object_removeEventListener(__SAFE_CAST(Object, PlatformerLevelState_getClock(PlatformerLevelState_getInstance())), __SAFE_CAST(Object, this), (EventListener)Gui_onSecondChange, kEventSecondChanged);
	Object_removeEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)Gui_onHitTaken, kEventHitTaken);
	Object_removeEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)Gui_onCoinTaken, kEventCoinTaken);
	Object_removeEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)Gui_onKeyTaken, kEventKeyTaken);
	Object_removeEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)Gui_onPowerUp, kEventPowerUp);

	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

void Gui_ready(Gui this, bool recursive)
{
	ASSERT(this, "Gui::ready: null this");

	// call base
	__CALL_BASE_METHOD(AnimatedEntity, ready, this, recursive);
}

// print elapsed time to gui
void Gui_printClock(Gui this __attribute__ ((unused)))
{
	Clock_print(PlatformerLevelState_getClock(PlatformerLevelState_getInstance()), GUI_X_POS + 36, GUI_Y_POS, GUI_FONT);
}

// print best time to gui
void Gui_printBestTime(Gui this __attribute__ ((unused)))
{
	u32 bestTime = ProgressManager_getCurrentLevelBestTime(ProgressManager_getInstance());

	if(bestTime)
	{
		Clock clock = __NEW(Clock);
		Clock_setTimeInMilliSeconds(clock, bestTime);
		Clock_print(clock, GUI_X_POS + 42, GUI_Y_POS + 1, NULL);
		__DELETE(clock);
	}
	else
	{
		Printing_text(Printing_getInstance(), "--:--", GUI_X_POS + 42, GUI_Y_POS + 1, NULL);
	}
}

// print number of coins to gui
void Gui_printCoins(Gui this __attribute__ ((unused)))
{
	u8 coins = ProgressManager_getCurrentLevelNumberOfCollectedCoins(ProgressManager_getInstance());

	// bound to 64
	if(coins > 64)
	{
		coins = 64;
	}

	// compute x position
	u8 printPos = GUI_X_POS + (coins >= 10) ? 11 : 12;

	// print
	Printing_text(Printing_getInstance(), "00/64", GUI_X_POS + 11, GUI_Y_POS, GUI_FONT);
	Printing_int(Printing_getInstance(), coins, printPos, GUI_Y_POS, GUI_FONT);
}

// print hero's energy to gui
void Gui_printEnergy(Gui this __attribute__ ((unused)))
{
	Printing_text(Printing_getInstance(), "\x7B\x7B\x7B", GUI_X_POS + 4, GUI_Y_POS, GUI_FONT);
	u8 i;
	ASSERT(Hero_getInstance(), "Gui::printEnergy: null hero");

	for(i=0; i < Hero_getEnergy(Hero_getInstance()); i++)
	{
		Printing_text(Printing_getInstance(), "\x60", GUI_X_POS + 4 + i, GUI_Y_POS, GUI_FONT);
	}
}

// print keys icon to gui
void Gui_printKey(Gui this __attribute__ ((unused)))
{
	if(Hero_hasKey(Hero_getInstance()))
	{
		Printing_text(Printing_getInstance(), "\x7E\x7F", GUI_X_POS + 21, GUI_Y_POS, GUI_FONT);
	}
	else
	{
		Printing_text(Printing_getInstance(), "  ", GUI_X_POS + 21, GUI_Y_POS, GUI_FONT);
	}
}

// print current level to gui
void Gui_printLevel(Gui this __attribute__ ((unused)))
{
	PlatformerLevelDefinition* platformerLevelDefinition = PlatformerLevelState_getCurrentLevelDefinition(PlatformerLevelState_getInstance());
	Printing_text(Printing_getInstance(), platformerLevelDefinition->identifier, GUI_X_POS + 29, GUI_Y_POS, GUI_FONT);
}

// update sprite, e.g. after collecting a power-up
void Gui_updateSprite(Gui this)
{
	CharSet charSet = Texture_getCharSet(Sprite_getTexture(__SAFE_CAST(Sprite, VirtualList_front(this->sprites))), true);

	CharSetDefinition* charSetDefinition = NULL;

	switch(Hero_getPowerUp(Hero_getInstance()))
	{
		case kPowerUpBandana:

			//charSetDefinition = &GUI_BANDANA_CH;
			break;

		default:
		case kPowerUpNone:

			charSetDefinition = &GUI_CH;
			break;
	}

	CharSet_setCharSetDefinition(charSet, charSetDefinition);
	CharSet_rewrite(charSet);
}

// print current level to gui
void Gui_printAll(Gui this)
{
	// calls Gui_updateSprite, which modifies Sprites. These are not yet available in the entity's
	// construction phase, so we need to utilize the ready method.
	Gui_updateSprite(this);

	Gui_printClock(this);
	Gui_printBestTime(this);
	Gui_printCoins(this);
	Gui_printEnergy(this);
	Gui_printKey(this);
	Gui_printLevel(this);
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
	Gui_printEnergy(this);
}

// handle event
static void Gui_onCoinTaken(Gui this, Object eventFirer __attribute__ ((unused)))
{
	Gui_printCoins(this);
}

// handle event
static void Gui_onKeyTaken(Gui this, Object eventFirer __attribute__ ((unused)))
{
	Gui_printKey(this);
}

// handle event
static void Gui_onPowerUp(Gui this, Object eventFirer __attribute__ ((unused)))
{
	Gui_updateSprite(this);
}

bool Gui_handlePropagatedMessage(Gui this, int message)
{
	ASSERT(this, "Gui::handlePropagatedMessage: null this");

	switch(message)
	{
		case kLevelSetUp:
		case kLevelResumed:

			Gui_printAll(this);
			break;
	}

	return false;
}
