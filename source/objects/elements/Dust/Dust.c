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
#include <PlatformerLevelState.h>
#include "Dust.h"


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void Dust::constructor(AnimatedEntitySpec* animatedEntitySpec, int16 internalId, const char* const name)
{
	Base::constructor(animatedEntitySpec, internalId, name);
}

void Dust::destructor()
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void Dust::showAnimation()
{
	AnimatedEntity::playAnimation(this, "Show");
	Container::setInheritEnvironment(this, __INHERIT_NONE);
}

void Dust::onShowAnimationComplete()
{
	Container::setInheritEnvironment(this, __INHERIT_POSITION);
}
