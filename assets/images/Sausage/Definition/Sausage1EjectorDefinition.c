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

#include <BgmapAnimatedSprite.h>
#include <macros.h>
#include <ProjectileEjector.h>
#include <Actor.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern ActorDefinition SAUSAGE_1_PR;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

ProjectileEjectorROMDef SAUSAGE_EJECTOR_PE =
{
	// animated entity
	{
		{
			// class allocator
			__TYPE(ProjectileEjector),

			// sprites
			(SpriteROMDef**)NULL,

			// collision shapes
			(ShapeDefinition*)NULL,

			// size
			// if 0, width and height will be inferred from the first sprite's texture's size
			{0, 0, 0},

			// gameworld's character's type
			kNoType,

			// physical specification
			(PhysicalSpecification*)NULL,
		},

		// pointer to the animation definition for the character
		(AnimationDescription*)NULL,

		// initial animation
		NULL
	},

	// projectile
    {(EntityDefinition*)&SAUSAGE_1_PR, {0, 0, 0, 0}, 0, NULL, NULL, NULL, true},

	// delay of the first projectile ejection (only relevant if initially active)
	0,

	// pause between projectile ejections
	1000,

	// whether the ejector should be active on creation
	false,

	// maximum number of projectiles on screen at the same time
	3,

	// name of animation to play on projectile ejection
	NULL,

	// name of animation to play when idle
	NULL,
};
