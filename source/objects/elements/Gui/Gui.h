/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef GUI_H_
#define GUI_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Entity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

class Gui : Entity
{
	bool active;

	void constructor(EntitySpec* animatedEntitySpec, s16 internalId, const char* const name);
	override void ready(bool recursive);
	override void resume();
	void printClock();
	void printLives();
	void printGums();
	void printAll();
}


#endif
