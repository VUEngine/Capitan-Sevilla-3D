/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
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

extern uint32 GuiItemsTiles[];
extern CharSetSpec GuiItemsCharset;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void Gui::constructor(EntitySpec* animatedEntitySpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor(animatedEntitySpec, internalId, name);

	// init members
	this->active = false;

	// add event listeners
	Object eventManager = Object::safeCast(EventManager::getInstance());
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onHitTaken, kEventHitTaken);
	Object::addEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onCaptainSpawned, kEventCaptainSpawned);
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
	Object::removeEventListener(eventManager, Object::safeCast(this), (EventListener)Gui::onCaptainSpawned, kEventCaptainSpawned);
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

	if(!isDeleted(Captain::getInstance()))
	{
		Gui::printAll(this);
	}

	VirtualList sprites = Entity::getSprites(this);
	VirtualNode node = VirtualList::begin(sprites);
	Sprite sprite = Sprite::safeCast(VirtualNode::getData(node));

	Texture::addEventListener(Sprite::getTexture(sprite), Object::safeCast(this), (EventListener)Gui::onSpriteTextureRewritten, kEventTextureRewritten);
}

void Gui::resume()
{
	Base::resume(this);

	NM_ASSERT(!isDeleted(Captain::getInstance()), "Gui::resume: no Captain");

	// TODO: this does not work
	Gui::printAll(this);
}

void Gui::printGums()
{
	uint8 gums = Captain::getGums(Captain::getInstance());

	VirtualList sprites = Entity::getSprites(this);
	VirtualNode node = VirtualList::begin(sprites);
	Sprite sprite = Sprite::safeCast(VirtualNode::getData(node));

	// prgum icons
	uint8 i = CAPTAIN_MAX_GUMS;
	uint8 hasGumOffset = 0;
	for(; i > 0; i--)
	{
		hasGumOffset = (i <= gums) ? 8 : 0;

			void putChar(Point* texturePixel, uint32* newChar);

		Sprite::putChar(sprite, &(Point){1 + ((i-1)<<1), 3}, &((uint32*)GuiItemsTiles)[(20 + ((i-1)<<1) + hasGumOffset) << 0]);
		Sprite::putChar(sprite, &(Point){2 + ((i-1)<<1), 3}, &((uint32*)GuiItemsTiles)[(21 + ((i-1)<<1) + hasGumOffset) << 0]);
		Sprite::putChar(sprite, &(Point){1 + ((i-1)<<1), 4}, &((uint32*)GuiItemsTiles)[(20 + ((i-1)<<1) + hasGumOffset + 42) << 0]);
		Sprite::putChar(sprite, &(Point){2 + ((i-1)<<1), 4}, &((uint32*)GuiItemsTiles)[(21 + ((i-1)<<1) + hasGumOffset + 42) << 0]);
	}

	// "reload"
	if(gums == 0)
	{
		Sprite::putChar(sprite, &(Point){2, 1}, &((uint32*)GuiItemsTiles)[(36 + 42) << 0]);
		Sprite::putChar(sprite, &(Point){3, 1}, &((uint32*)GuiItemsTiles)[(37 + 42) << 0]);
		Sprite::putChar(sprite, &(Point){4, 1}, &((uint32*)GuiItemsTiles)[(38 + 42) << 0]);
		Sprite::putChar(sprite, &(Point){5, 1}, &((uint32*)GuiItemsTiles)[(39 + 42) << 0]);
		Sprite::putChar(sprite, &(Point){6, 1}, &((uint32*)GuiItemsTiles)[(40 + 42) << 0]);
		Sprite::putChar(sprite, &(Point){7, 1}, &((uint32*)GuiItemsTiles)[(41 + 42) << 0]);
	}
	else
	{
		Sprite::putChar(sprite, &(Point){2, 1}, &((uint32*)GuiItemsTiles)[(36) << 0]);
		Sprite::putChar(sprite, &(Point){3, 1}, &((uint32*)GuiItemsTiles)[(37) << 0]);
		Sprite::putChar(sprite, &(Point){4, 1}, &((uint32*)GuiItemsTiles)[(38) << 0]);
		Sprite::putChar(sprite, &(Point){5, 1}, &((uint32*)GuiItemsTiles)[(39) << 0]);
		Sprite::putChar(sprite, &(Point){6, 1}, &((uint32*)GuiItemsTiles)[(40) << 0]);
		Sprite::putChar(sprite, &(Point){7, 1}, &((uint32*)GuiItemsTiles)[(41) << 0]);
	}
/*
	// gum 1 (empty)
	Sprite::putChar(sprite, &(Point){1, 3}, &((uint32*)GuiItemsTiles)[(20) << 0]);
	Sprite::putChar(sprite, &(Point){2, 3}, &((uint32*)GuiItemsTiles)[(21) << 0]);
	Sprite::putChar(sprite, &(Point){1, 4}, &((uint32*)GuiItemsTiles)[(20 + 42) << 0]);
	Sprite::putChar(sprite, &(Point){2, 4}, &((uint32*)GuiItemsTiles)[(21 + 42) << 0]);
	// gum 2 (empty)
	Sprite::putChar(sprite, &(Point){3, 3}, &((uint32*)GuiItemsTiles)[(22) << 0]);
	Sprite::putChar(sprite, &(Point){4, 3}, &((uint32*)GuiItemsTiles)[(23) << 0]);
	Sprite::putChar(sprite, &(Point){3, 4}, &((uint32*)GuiItemsTiles)[(22 + 42) << 0]);
	Sprite::putChar(sprite, &(Point){4, 4}, &((uint32*)GuiItemsTiles)[(23 + 42) << 0]);
	// gum 3 (empty)
	Sprite::putChar(sprite, &(Point){5, 3}, &((uint32*)GuiItemsTiles)[(24) << 0]);
	Sprite::putChar(sprite, &(Point){6, 3}, &((uint32*)GuiItemsTiles)[(25) << 0]);
	Sprite::putChar(sprite, &(Point){5, 4}, &((uint32*)GuiItemsTiles)[(24 + 42) << 0]);
	Sprite::putChar(sprite, &(Point){6, 4}, &((uint32*)GuiItemsTiles)[(25 + 42) << 0]);
	// gum 4 (empty)
	Sprite::putChar(sprite, &(Point){7, 3}, &((uint32*)GuiItemsTiles)[(26) << 0]);
	Sprite::putChar(sprite, &(Point){8, 3}, &((uint32*)GuiItemsTiles)[(27) << 0]);
	Sprite::putChar(sprite, &(Point){7, 4}, &((uint32*)GuiItemsTiles)[(26 + 42) << 0]);
	Sprite::putChar(sprite, &(Point){8, 4}, &((uint32*)GuiItemsTiles)[(27 + 42) << 0]);

	// gum 1
	Sprite::putChar(sprite, &(Point){1, 3}, &((uint32*)GuiItemsTiles)[(20 + 8) << 0]);
	Sprite::putChar(sprite, &(Point){2, 3}, &((uint32*)GuiItemsTiles)[(21 + 8) << 0]);
	Sprite::putChar(sprite, &(Point){1, 4}, &((uint32*)GuiItemsTiles)[(20 + 42 + 8) << 0]);
	Sprite::putChar(sprite, &(Point){2, 4}, &((uint32*)GuiItemsTiles)[(21 + 42 + 8) << 0]);
	// gum 2
	Sprite::putChar(sprite, &(Point){3, 3}, &((uint32*)GuiItemsTiles)[(22 + 8) << 0]);
	Sprite::putChar(sprite, &(Point){4, 3}, &((uint32*)GuiItemsTiles)[(23 + 8) << 0]);
	Sprite::putChar(sprite, &(Point){3, 4}, &((uint32*)GuiItemsTiles)[(22 + 42 + 8) << 0]);
	Sprite::putChar(sprite, &(Point){4, 4}, &((uint32*)GuiItemsTiles)[(23 + 42 + 8) << 0]);
	// gum 3
	Sprite::putChar(sprite, &(Point){5, 3}, &((uint32*)GuiItemsTiles)[(24 + 8) << 0]);
	Sprite::putChar(sprite, &(Point){6, 3}, &((uint32*)GuiItemsTiles)[(25 + 8) << 0]);
	Sprite::putChar(sprite, &(Point){5, 4}, &((uint32*)GuiItemsTiles)[(24 + 42 + 8) << 0]);
	Sprite::putChar(sprite, &(Point){6, 4}, &((uint32*)GuiItemsTiles)[(25 + 42 + 8) << 0]);
	// gum 4
	Sprite::putChar(sprite, &(Point){7, 3}, &((uint32*)GuiItemsTiles)[(26 + 8) << 0]);
	Sprite::putChar(sprite, &(Point){8, 3}, &((uint32*)GuiItemsTiles)[(27 + 8) << 0]);
	Sprite::putChar(sprite, &(Point){7, 4}, &((uint32*)GuiItemsTiles)[(26 + 42 + 8) << 0]);
	Sprite::putChar(sprite, &(Point){8, 4}, &((uint32*)GuiItemsTiles)[(27 + 42 + 8) << 0]);
*/
}

void Gui::printLives()
{
	uint8 lives = Captain::getEnergy(Captain::getInstance());

	VirtualList sprites = Entity::getSprites(this);
	VirtualNode node = VirtualList::begin(sprites);
	Sprite sprite = Sprite::safeCast(VirtualNode::getData(node));

	Sprite::putChar(sprite, &(Point){8, 1}, &((uint32*)GuiItemsTiles)[(lives + 10) << 0]);
	Sprite::putChar(sprite, &(Point){8, 2}, &((uint32*)GuiItemsTiles)[(lives + 10 + 42) << 0]);
}

void Gui::printAll()
{
	Gui::printLives(this);
	Gui::printGums(this);
}

void Gui::onSpriteTextureRewritten(Object eventFirer __attribute__ ((unused)))
{
	Gui::printAll(this);
}

void Gui::onHitTaken(Object eventFirer __attribute__ ((unused)))
{
	Gui::printLives(this);
}

void Gui::onCaptainSpawned(Object eventFirer __attribute__ ((unused)))
{
	Gui::printAll(this);
}

void Gui::onCaptainDied(Object eventFirer __attribute__ ((unused)))
{
	Container::deleteMyself(this);
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
