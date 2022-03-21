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

	Sprite sprite = Sprite::safeCast(VirtualList::front(Entity::getSprites(this)));

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

	Sprite sprite = Sprite::safeCast(VirtualList::front(Entity::getSprites(this)));

	// prgum icons
	uint8 i = CAPTAIN_MAX_GUMS;
	uint8 hasGumOffset = 0;
	for(; i > 0; i--)
	{
		hasGumOffset = (i <= gums) ? 8 : 0;

		Sprite::putChar(sprite, &(Point){1 + ((i - 1) << 1), 3}, &GuiItemsTiles[(20 + ((i - 1) << 1) + hasGumOffset) << 2] + 1);
		Sprite::putChar(sprite, &(Point){2 + ((i - 1) << 1), 3}, &GuiItemsTiles[(21 + ((i - 1) << 1) + hasGumOffset) << 2] + 1);
		Sprite::putChar(sprite, &(Point){1 + ((i - 1) << 1), 4}, &GuiItemsTiles[(20 + ((i - 1) << 1) + hasGumOffset + 42) << 2] + 1);
		Sprite::putChar(sprite, &(Point){2 + ((i - 1) << 1), 4}, &GuiItemsTiles[(21 + ((i - 1) << 1) + hasGumOffset + 42) << 2] + 1);
	}

	// "reload"
	if(gums == 0)
	{
		Sprite::putChar(sprite, &(Point){2, 1}, &GuiItemsTiles[(36 + 42) << 2] + 1);
		Sprite::putChar(sprite, &(Point){3, 1}, &GuiItemsTiles[(37 + 42) << 2] + 1);
		Sprite::putChar(sprite, &(Point){4, 1}, &GuiItemsTiles[(38 + 42) << 2] + 1);
		Sprite::putChar(sprite, &(Point){5, 1}, &GuiItemsTiles[(39 + 42) << 2] + 1);
		Sprite::putChar(sprite, &(Point){6, 1}, &GuiItemsTiles[(40 + 42) << 2] + 1);
		Sprite::putChar(sprite, &(Point){7, 1}, &GuiItemsTiles[(41 + 42) << 2] + 1);
	}
	else
	{
		Sprite::putChar(sprite, &(Point){2, 1}, &GuiItemsTiles[(36) << 2] + 1);
		Sprite::putChar(sprite, &(Point){3, 1}, &GuiItemsTiles[(37) << 2] + 1);
		Sprite::putChar(sprite, &(Point){4, 1}, &GuiItemsTiles[(38) << 2] + 1);
		Sprite::putChar(sprite, &(Point){5, 1}, &GuiItemsTiles[(39) << 2] + 1);
		Sprite::putChar(sprite, &(Point){6, 1}, &GuiItemsTiles[(40) << 2] + 1);
		Sprite::putChar(sprite, &(Point){7, 1}, &GuiItemsTiles[(41) << 2] + 1);
	}
/*
	// gum 1 (empty)
	Sprite::putChar(sprite, &(Point){1, 3}, &GuiItemsTiles[(20) << 2] + 1);
	Sprite::putChar(sprite, &(Point){2, 3}, &GuiItemsTiles[(21) << 2] + 1);
	Sprite::putChar(sprite, &(Point){1, 4}, &GuiItemsTiles[(20 + 42) << 2] + 1);
	Sprite::putChar(sprite, &(Point){2, 4}, &GuiItemsTiles[(21 + 42) << 2] + 1);
	// gum 2 (empty)
	Sprite::putChar(sprite, &(Point){3, 3}, &GuiItemsTiles[(22) << 2] + 1);
	Sprite::putChar(sprite, &(Point){4, 3}, &GuiItemsTiles[(23) << 2] + 1);
	Sprite::putChar(sprite, &(Point){3, 4}, &GuiItemsTiles[(22 + 42) << 2] + 1);
	Sprite::putChar(sprite, &(Point){4, 4}, &GuiItemsTiles[(23 + 42) << 2] + 1);
	// gum 3 (empty)
	Sprite::putChar(sprite, &(Point){5, 3}, &GuiItemsTiles[(24) << 2] + 1);
	Sprite::putChar(sprite, &(Point){6, 3}, &GuiItemsTiles[(25) << 2] + 1);
	Sprite::putChar(sprite, &(Point){5, 4}, &GuiItemsTiles[(24 + 42) << 2] + 1);
	Sprite::putChar(sprite, &(Point){6, 4}, &GuiItemsTiles[(25 + 42) << 2] + 1);
	// gum 4 (empty)
	Sprite::putChar(sprite, &(Point){7, 3}, &GuiItemsTiles[(26) << 2] + 1);
	Sprite::putChar(sprite, &(Point){8, 3}, &GuiItemsTiles[(27) << 2] + 1);
	Sprite::putChar(sprite, &(Point){7, 4}, &GuiItemsTiles[(26 + 42) << 2] + 1);
	Sprite::putChar(sprite, &(Point){8, 4}, &GuiItemsTiles[(27 + 42) << 2] + 1);

	// gum 1
	Sprite::putChar(sprite, &(Point){1, 3}, &GuiItemsTiles[(20 + 8) << 2] + 1);
	Sprite::putChar(sprite, &(Point){2, 3}, &GuiItemsTiles[(21 + 8) << 2] + 1);
	Sprite::putChar(sprite, &(Point){1, 4}, &GuiItemsTiles[(20 + 42 + 8) << 2] + 1);
	Sprite::putChar(sprite, &(Point){2, 4}, &GuiItemsTiles[(21 + 42 + 8) << 2] + 1);
	// gum 2
	Sprite::putChar(sprite, &(Point){3, 3}, &GuiItemsTiles[(22 + 8) << 2] + 1);
	Sprite::putChar(sprite, &(Point){4, 3}, &GuiItemsTiles[(23 + 8) << 2] + 1);
	Sprite::putChar(sprite, &(Point){3, 4}, &GuiItemsTiles[(22 + 42 + 8) << 2] + 1);
	Sprite::putChar(sprite, &(Point){4, 4}, &GuiItemsTiles[(23 + 42 + 8) << 2] + 1);
	// gum 3
	Sprite::putChar(sprite, &(Point){5, 3}, &GuiItemsTiles[(24 + 8) << 2] + 1);
	Sprite::putChar(sprite, &(Point){6, 3}, &GuiItemsTiles[(25 + 8) << 2] + 1);
	Sprite::putChar(sprite, &(Point){5, 4}, &GuiItemsTiles[(24 + 42 + 8) << 2] + 1);
	Sprite::putChar(sprite, &(Point){6, 4}, &GuiItemsTiles[(25 + 42 + 8) << 2] + 1);
	// gum 4
	Sprite::putChar(sprite, &(Point){7, 3}, &GuiItemsTiles[(26 + 8) << 2] + 1);
	Sprite::putChar(sprite, &(Point){8, 3}, &GuiItemsTiles[(27 + 8) << 2] + 1);
	Sprite::putChar(sprite, &(Point){7, 4}, &GuiItemsTiles[(26 + 42 + 8) << 2] + 1);
	Sprite::putChar(sprite, &(Point){8, 4}, &GuiItemsTiles[(27 + 42 + 8) << 2] + 1);
*/
}

void Gui::printLives()
{
	uint8 lives = Captain::getEnergy(Captain::getInstance());

	Sprite sprite = Sprite::safeCast(VirtualList::front(Entity::getSprites(this)));

	Sprite::putChar(sprite, &(Point){8, 1}, &GuiItemsTiles[(lives + 10) << 2] + 1);
	Sprite::putChar(sprite, &(Point){8, 2}, &GuiItemsTiles[(lives + 10 + 42) << 2] + 1);
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
