/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef CAR_H_
#define CAR_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <MovingOneWayEntity.h>
#include <SoundWrapper.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

class Car : MovingOneWayEntity
{
	SoundWrapper engineSound;

	void constructor(MovingOneWayEntitySpec* movingOneWayEntitySpec, s16 internalId, const char* const name);
	override void ready(bool recursive);
}


#endif
