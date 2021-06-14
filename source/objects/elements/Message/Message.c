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

#include <Game.h>
#include <CollisionManager.h>
#include <I18n.h>
#include <Utilities.h>
#include <PlatformerLevelState.h>
#include "Message.h"


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void Message::constructor(AnimatedEntitySpec* animatedEntitySpec, s16 internalId, const char* const name)
{
	Base::constructor(animatedEntitySpec, internalId, name);
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
