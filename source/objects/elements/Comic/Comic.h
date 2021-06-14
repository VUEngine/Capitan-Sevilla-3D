/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef COMIC_H_
#define COMIC_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <LocalizedEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

#define COMIC_MOVE_DELAY 	8
#define COMIC_MOVE_OFFSET 	12


//---------------------------------------------------------------------------------------------------------
//												ENUMS
//---------------------------------------------------------------------------------------------------------

enum ComicModes
{
	kComicStill = 0,
	kComicMoving,
};


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

class Comic : LocalizedEntity
{
	u8 mode;

	void constructor(LocalizedEntitySpec* localizedEntitySpec, s16 internalId, const char* const name);
	override void ready(bool recursive);
	override bool handleMessage(Telegram telegram);
	override bool respawn();
}


#endif
