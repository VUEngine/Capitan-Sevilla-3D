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
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onDuckCollected, kEventDuckCollected);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onLiftActivated, kEventLiftActivated);
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onExitPointReached, kEventExitPointReached);

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void Gui::resume()
{
	Base::resume(this);

	Gui::printAll(this);
}

void Gui::printGums()
{
	VirtualList sprites = Entity::getSprites(this);
	VirtualNode node = VirtualList::begin(sprites);
	Sprite sprite = Sprite::safeCast(VirtualNode::getData(node));
/*
	Point point1 = {36, 3};
	Sprite::putChar(sprite, &point1, &GuiItemsTiles[0]);

	Point point2 = {37, 3};
	Sprite::putChar(sprite, &point2, &GuiItemsTiles[5]);

	Point point3 = {38, 3};
	Sprite::putChar(sprite, &point3, &GuiItemsTiles[36]);

	Point point4 = {39, 3};
	Sprite::putChar(sprite, &point4, &GuiItemsTiles[37]);
*/
/*
	Point point = {36, 3};
	Pixel pixel = {2, 2};
	Sprite::putPixel(sprite, &point, &pixel, 4);
*/
}

void Gui::printLives()
{
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
