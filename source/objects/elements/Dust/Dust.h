/*
 * Capitán Sevilla 3D, an adventure platforming game demo for Nintendo Virtual Boy
 *
 * (c) Christian Radke, Jorge Eremiev and Rubén Garcerá Soto
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef DUST_H_
#define DUST_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AnimatedEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

class Dust : AnimatedEntity
{
	void constructor(AnimatedEntitySpec* animatedEntitySpec, s16 internalId, const char* const name);
	void showAnimation();
	void onShowAnimationComplete();
}


#endif
