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

#include <Game.h>
#include <CollisionManager.h>
#include <I18n.h>
#include <Utilities.h>
#include <PlatformerLevelState.h>
#include "Message.h"


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void Message::constructor(AnimatedEntitySpec* animatedEntitySpec, s16 id, s16 internalId, const char* const name)
{
	Base::constructor(animatedEntitySpec, id, internalId, name);
}

void Message::destructor()
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

bool Message::handleMessage(Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kGameEnterCollision:
		{
			char* language = Utilities::itoa(I18n::getActiveLanguage(I18n::getInstance()), 10, 1);
			AnimatedEntity::playAnimation(this, language);
			break;
		}
		case kGameExitCollision:
		{
			AnimatedEntity::playAnimation(this, "Hide");
			break;
		}
	}

	return false;
}
