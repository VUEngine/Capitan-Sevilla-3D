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

#ifndef MOVING_ENTITY_H_
#define MOVING_ENTITY_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Actor.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

#define MOVING_ENTITY_WAIT_DELAY				1000
#define MOVING_ENTITY_DIRECTION_CHECK_DELAY		75


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------


// definition in ROM memory
typedef struct MovingEntityDefinition
{
	// It has a Character in the beginning
	ActorDefinition actorDefinition;

	// velocity
	fix10_6 velocity;

	// maximum deviation from initial position
	fix10_6 maximumDisplacement;

	// time to rest idle
	u16 idleDuration;

	// on which axis it moves
	u8 axis;

	// movement direction
	s8 direction;

	// axes on which synchronize shape with direction
	u16 axesForShapeSyncWithDirection;

} MovingEntityDefinition;

typedef const MovingEntityDefinition MovingEntityROMDef;


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

// allocator




class MovingEntity : Actor
{
	/* save my initial position */																	
	int initialPosition;																			
	/* definition pointer */																		
	MovingEntityDefinition* movingEntityDefinition;													
	
	void constructor(MovingEntityDefinition* MovingEntityDefinition, s16 id, s16 internalId, const char* const name);
	void startMovement();
	void checkDisplacement();
	override void ready(bool recursive);
	override bool handleMessage(Telegram telegram);
	override void setDefinition(void* movingEntityDefinition);
	override u16 getAxesForShapeSyncWithDirection();
}


#endif
