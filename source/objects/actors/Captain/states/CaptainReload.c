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

#include "CaptainReload.h"
#include "../Captain.h"


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void CaptainReload::constructor()
{
	// construct base
	Base::constructor();
}

void CaptainReload::destructor()
{
	// destroy base
	Base::destructor();
}

void CaptainReload::enter(void* owner)
{
	Actor::stopAllMovement(owner);
	Captain::playAnimation(owner, "Reload");
}
