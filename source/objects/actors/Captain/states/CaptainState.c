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

#include "CaptainState.h"
#include <VirtualList.h>
#include <Entity.h>
#include <Shape.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void CaptainState::constructor()
{
	// construct base
	Base::constructor();
}

void CaptainState::destructor()
{
	// destroy base
	Base::destructor();
}

void CaptainState::onKeyHold(void* owner __attribute__ ((unused)), const UserInput* userInput __attribute__ ((unused)))
{
}

void CaptainState::onKeyPressed(void* owner __attribute__ ((unused)), const UserInput* userInput __attribute__ ((unused)))
{
}

void CaptainState::onKeyReleased(void* owner __attribute__ ((unused)), const UserInput* userInput __attribute__ ((unused)))
{
}

void CaptainState::toggleShapes(void* owner, bool kneeling)
{
	VirtualList shapes = Entity::getShapes(owner);
	Shape shapeStanding = Shape::safeCast(VirtualList::front(shapes));
	Shape shapeKneeling = Shape::safeCast(VirtualList::back(shapes));
	Shape::enable(shapeStanding, !kneeling);
	Shape::enable(shapeKneeling, kneeling);
}