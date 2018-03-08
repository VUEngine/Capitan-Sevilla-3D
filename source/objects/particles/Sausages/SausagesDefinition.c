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

#include <libgccvb.h>
#include <SolidParticle.h>
#include <ParticleSystem.h>
#include <ObjectAnimatedSprite.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern AnimationDescriptionROMDef SAUSAGE_ANIM;
extern ObjectSpriteROMDef SAUSAGE_SPRITE;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

ObjectSpriteROMDef* const SAUSAGE_SPRITES[] =
{
	&SAUSAGE_SPRITE,
	NULL
};

// particle's definition
SolidParticleROMDef SAUSAGE_PARTICLE =
{
	{
		// allocator
		__TYPE(SolidParticle),

		// particle's minimum life span in milliseconds
		3500,

		// particle's maximum life span in milliseconds
		0,

		// particle's minimum mass
		__I_TO_FIX10_6(1),

		// particle's maximum mass
		__I_TO_FIX10_6(1),

		// axis subject to gravity (bitwise or of __X_AXIS, __Y_AXIS, __Z_AXIS, or false to disable)
		__NO_AXIS,

		// function pointer to control particle's behavior
		NULL,

		// animation description (used only if sprite is animated)
		(AnimationDescription*)&SAUSAGE_ANIM,

		// name of animation to play
		"Default"
	},

	// ball's radius
	__F_TO_FIX10_6(0.25f),

	// friction for physics
	__F_TO_FIX10_6(0.0f),

	// elasticity for physics
	__F_TO_FIX10_6(0.6f),

	// object's in-game type
	kSausage,

	// layers in which I live
	kParticlesLayer,

	// layers to ignore when checking for collisions
	kParticlesLayer | kTriggersLayer,

	// disable collision detection when the particle stops
	true,
};

ParticleSystemROMDef SAUSAGE_PS =
{
	{
		// class allocator
		__TYPE(ParticleSystem),

		// sprites
		(SpriteROMDef**)NULL,

		// collision shapes
		(ShapeDefinition*)NULL,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kNotShape,

		// physical specification
		(PhysicalSpecification*)NULL,
	},

	// reuse expired particles?
	true,

	// minimum generation delay in milliseconds
	0,

	// generation delay delta in milliseconds
	0,

	// maximum total particles
	1,

	// array of textures
	(const ObjectSpriteDefinition**)SAUSAGE_SPRITES,

	// auto start
	true,

	// particle definition
	(ParticleDefinition*)&SAUSAGE_PARTICLE,

	// minimum relative spawn position (x, y, z)
	{__I_TO_FIX10_6(0), __I_TO_FIX10_6(0), __I_TO_FIX10_6(0)},

	// maximum relative spawn position (x, y, z)
	{__I_TO_FIX10_6(0), __I_TO_FIX10_6(0), __I_TO_FIX10_6(0)},

	// minimum force to apply (x, y, z)
	// (use int values in the definition to avoid overflow)
	{__F_TO_FIX10_6(6.0f), __I_TO_FIX10_6(0), __I_TO_FIX10_6(0)},

	// maximum force to apply (x, y, z)
	// (use int values in the definition to avoid overflow)
	{__F_TO_FIX10_6(6.0f), __I_TO_FIX10_6(0), __I_TO_FIX10_6(0)},

	// movement type (__UNIFORM_MOVEMENT or __ACCELERATED_MOVEMENT)
	__UNIFORM_MOVEMENT
};