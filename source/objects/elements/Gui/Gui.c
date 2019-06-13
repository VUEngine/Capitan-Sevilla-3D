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
#include <SoundManager.h>
#include <Captain.h>


//---------------------------------------------------------------------------------------------------------
//											DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE GuiItemsTiles[];
extern CharSetSpec GUI_ITEMS_CH;
extern const u16 JUMP_SND[];
extern EntitySpec GAME_OVER_EN;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void Gui::constructor(EntitySpec* animatedEntitySpec, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(animatedEntitySpec, id, internalId, name);

	// init members
	this->active = false;

	// add event listeners
	Object eventManager = Object::safeCast(EventManager::getInstance());
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onHitTaken, kEventHitTaken);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onCaptainDied, kEventCaptainDied);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onSetModeToPaused, kEventSetModeToPaused);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onSetModeToPlaying, kEventSetModeToPlaying);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onCaptainShot, kEventCaptainShot);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onGumsReloaded, kEventGumsReloaded);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onDuckCollected, kEventDuckCollected);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onLiftActivated, kEventLiftActivated);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onExitPointReached, kEventExitPointReached);
}

void Gui::destructor()
{
	// remove event listeners
	Object eventManager = Object::safeCast(EventManager::getInstance());
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onHitTaken, kEventHitTaken);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onCaptainDied, kEventCaptainDied);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onSetModeToPaused, kEventSetModeToPaused);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onSetModeToPlaying, kEventSetModeToPlaying);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onCaptainShot, kEventCaptainShot);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onGumsReloaded, kEventGumsReloaded);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onDuckCollected, kEventDuckCollected);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onLiftActivated, kEventLiftActivated);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onExitPointReached, kEventExitPointReached);

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void Gui::ready(bool recursive)
{
	Base::ready(this, recursive);

	Gui::printAll(this);
}

void Gui::resume()
{
	Base::resume(this);

	Gui::printAll(this);
}

void Gui::printGums()
{
	u8 gums = Captain::getGums(Captain::getInstance());

	VirtualList sprites = Entity::getSprites(this);
	VirtualNode node = VirtualList::begin(sprites);
	Sprite sprite = Sprite::safeCast(VirtualNode::getData(node));

	// print gum icons
	u8 i = CAPTAIN_MAX_GUMS;
	u8 hasGumOffset = 0;
	for(; i > 0; i--)
	{
		hasGumOffset = (i <= gums) ? 8 : 0;
		Sprite::putChar(sprite, &(Point){36 + ((i-1)<<1), 3}, &((BYTE*)GuiItemsTiles)[(20 + ((i-1)<<1) + hasGumOffset) << 4]);
		Sprite::putChar(sprite, &(Point){37 + ((i-1)<<1), 3}, &((BYTE*)GuiItemsTiles)[(21 + ((i-1)<<1) + hasGumOffset) << 4]);
		Sprite::putChar(sprite, &(Point){36 + ((i-1)<<1), 4}, &((BYTE*)GuiItemsTiles)[(20 + ((i-1)<<1) + hasGumOffset + 42) << 4]);
		Sprite::putChar(sprite, &(Point){37 + ((i-1)<<1), 4}, &((BYTE*)GuiItemsTiles)[(21 + ((i-1)<<1) + hasGumOffset + 42) << 4]);
	}

	// "reload"
	if(gums == 0)
	{
		Sprite::putChar(sprite, &(Point){37, 1}, &((BYTE*)GuiItemsTiles)[(36 + 42) << 4]);
		Sprite::putChar(sprite, &(Point){38, 1}, &((BYTE*)GuiItemsTiles)[(37 + 42) << 4]);
		Sprite::putChar(sprite, &(Point){39, 1}, &((BYTE*)GuiItemsTiles)[(38 + 42) << 4]);
		Sprite::putChar(sprite, &(Point){40, 1}, &((BYTE*)GuiItemsTiles)[(39 + 42) << 4]);
		Sprite::putChar(sprite, &(Point){41, 1}, &((BYTE*)GuiItemsTiles)[(40 + 42) << 4]);
		Sprite::putChar(sprite, &(Point){42, 1}, &((BYTE*)GuiItemsTiles)[(41 + 42) << 4]);
	}
	else
	{
		Sprite::putChar(sprite, &(Point){37, 1}, &((BYTE*)GuiItemsTiles)[(36) << 4]);
		Sprite::putChar(sprite, &(Point){38, 1}, &((BYTE*)GuiItemsTiles)[(37) << 4]);
		Sprite::putChar(sprite, &(Point){39, 1}, &((BYTE*)GuiItemsTiles)[(38) << 4]);
		Sprite::putChar(sprite, &(Point){40, 1}, &((BYTE*)GuiItemsTiles)[(39) << 4]);
		Sprite::putChar(sprite, &(Point){41, 1}, &((BYTE*)GuiItemsTiles)[(40) << 4]);
		Sprite::putChar(sprite, &(Point){42, 1}, &((BYTE*)GuiItemsTiles)[(41) << 4]);
	}
/*
	// gum 1 (empty)
	Sprite::putChar(sprite, &(Point){36, 3}, &((BYTE*)GuiItemsTiles)[(20) << 4]);
	Sprite::putChar(sprite, &(Point){37, 3}, &((BYTE*)GuiItemsTiles)[(21) << 4]);
	Sprite::putChar(sprite, &(Point){36, 4}, &((BYTE*)GuiItemsTiles)[(20 + 42) << 4]);
	Sprite::putChar(sprite, &(Point){37, 4}, &((BYTE*)GuiItemsTiles)[(21 + 42) << 4]);
	// gum 2 (empty)
	Sprite::putChar(sprite, &(Point){38, 3}, &((BYTE*)GuiItemsTiles)[(22) << 4]);
	Sprite::putChar(sprite, &(Point){39, 3}, &((BYTE*)GuiItemsTiles)[(23) << 4]);
	Sprite::putChar(sprite, &(Point){38, 4}, &((BYTE*)GuiItemsTiles)[(22 + 42) << 4]);
	Sprite::putChar(sprite, &(Point){39, 4}, &((BYTE*)GuiItemsTiles)[(23 + 42) << 4]);
	// gum 3 (empty)
	Sprite::putChar(sprite, &(Point){40, 3}, &((BYTE*)GuiItemsTiles)[(24) << 4]);
	Sprite::putChar(sprite, &(Point){41, 3}, &((BYTE*)GuiItemsTiles)[(25) << 4]);
	Sprite::putChar(sprite, &(Point){40, 4}, &((BYTE*)GuiItemsTiles)[(24 + 42) << 4]);
	Sprite::putChar(sprite, &(Point){41, 4}, &((BYTE*)GuiItemsTiles)[(25 + 42) << 4]);
	// gum 4 (empty)
	Sprite::putChar(sprite, &(Point){42, 3}, &((BYTE*)GuiItemsTiles)[(26) << 4]);
	Sprite::putChar(sprite, &(Point){43, 3}, &((BYTE*)GuiItemsTiles)[(27) << 4]);
	Sprite::putChar(sprite, &(Point){42, 4}, &((BYTE*)GuiItemsTiles)[(26 + 42) << 4]);
	Sprite::putChar(sprite, &(Point){43, 4}, &((BYTE*)GuiItemsTiles)[(27 + 42) << 4]);

	// gum 1
	Sprite::putChar(sprite, &(Point){36, 3}, &((BYTE*)GuiItemsTiles)[(20 + 8) << 4]);
	Sprite::putChar(sprite, &(Point){37, 3}, &((BYTE*)GuiItemsTiles)[(21 + 8) << 4]);
	Sprite::putChar(sprite, &(Point){36, 4}, &((BYTE*)GuiItemsTiles)[(20 + 42 + 8) << 4]);
	Sprite::putChar(sprite, &(Point){37, 4}, &((BYTE*)GuiItemsTiles)[(21 + 42 + 8) << 4]);
	// gum 2
	Sprite::putChar(sprite, &(Point){38, 3}, &((BYTE*)GuiItemsTiles)[(22 + 8) << 4]);
	Sprite::putChar(sprite, &(Point){39, 3}, &((BYTE*)GuiItemsTiles)[(23 + 8) << 4]);
	Sprite::putChar(sprite, &(Point){38, 4}, &((BYTE*)GuiItemsTiles)[(22 + 42 + 8) << 4]);
	Sprite::putChar(sprite, &(Point){39, 4}, &((BYTE*)GuiItemsTiles)[(23 + 42 + 8) << 4]);
	// gum 3
	Sprite::putChar(sprite, &(Point){40, 3}, &((BYTE*)GuiItemsTiles)[(24 + 8) << 4]);
	Sprite::putChar(sprite, &(Point){41, 3}, &((BYTE*)GuiItemsTiles)[(25 + 8) << 4]);
	Sprite::putChar(sprite, &(Point){40, 4}, &((BYTE*)GuiItemsTiles)[(24 + 42 + 8) << 4]);
	Sprite::putChar(sprite, &(Point){41, 4}, &((BYTE*)GuiItemsTiles)[(25 + 42 + 8) << 4]);
	// gum 4
	Sprite::putChar(sprite, &(Point){42, 3}, &((BYTE*)GuiItemsTiles)[(26 + 8) << 4]);
	Sprite::putChar(sprite, &(Point){43, 3}, &((BYTE*)GuiItemsTiles)[(27 + 8) << 4]);
	Sprite::putChar(sprite, &(Point){42, 4}, &((BYTE*)GuiItemsTiles)[(26 + 42 + 8) << 4]);
	Sprite::putChar(sprite, &(Point){43, 4}, &((BYTE*)GuiItemsTiles)[(27 + 42 + 8) << 4]);
*/
}

void Gui::printLives()
{
	u8 lives = Captain::getEnergy(Captain::getInstance());

	VirtualList sprites = Entity::getSprites(this);
	VirtualNode node = VirtualList::begin(sprites);
	Sprite sprite = Sprite::safeCast(VirtualNode::getData(node));

	Sprite::putChar(sprite, &(Point){43, 1}, &((BYTE*)GuiItemsTiles)[(lives + 10) << 4]);
	Sprite::putChar(sprite, &(Point){43, 2}, &((BYTE*)GuiItemsTiles)[(lives + 10 + 42) << 4]);
}

void Gui::printAll()
{
	Gui::printLives(this);
	Gui::printGums(this);
}

void Gui::onHitTaken(Object eventFirer __attribute__ ((unused)))
{
	Gui::printLives(this);
}

void Gui::onCaptainDied(Object eventFirer __attribute__ ((unused)))
{
	Container::deleteMyself(this);

	// add "game over"
	Vector3D cameraPosition = Camera::getPosition(Camera::getInstance());
	PositionedEntity gameOverPositionedEntity = {&GAME_OVER_EN, {__METERS_TO_PIXELS(cameraPosition.x) + 192, 112, 0, 0}, 0, NULL, NULL, NULL, false};
	Stage::addChildEntity(Game::getStage(Game::getInstance()), &gameOverPositionedEntity, true);
}

void Gui::onSetModeToPaused(Object eventFirer __attribute__ ((unused)))
{
	this->active = false;
}

void Gui::onSetModeToPlaying(Object eventFirer __attribute__ ((unused)))
{
	this->active = true;

	Gui::printAll(this);
}

void Gui::onCaptainShot(Object eventFirer __attribute__ ((unused)))
{
	Gui::printGums(this);
}

void Gui::onGumsReloaded(Object eventFirer __attribute__ ((unused)))
{
	Gui::printGums(this);
}

void Gui::onDuckCollected(Object eventFirer __attribute__ ((unused)))
{
	Gui::printGums(this);
}

void Gui::onLiftActivated(Object eventFirer __attribute__ ((unused)))
{
	this->active = false;
}

void Gui::onExitPointReached(Object eventFirer __attribute__ ((unused)))
{
	this->active = false;
}
