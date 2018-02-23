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

#ifndef POST_PROCESSING_EFFECTS_H_
#define POST_PROCESSING_EFFECTS_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <SpatialObject.h>


//---------------------------------------------------------------------------------------------------------
//										FUNCTIONS
//---------------------------------------------------------------------------------------------------------

void PostProcessingEffects_waterFall20x100(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject);
void PostProcessingEffects_rain(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject);
void PostProcessingEffects_lantern(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject);
void PostProcessingEffects_wobble(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject);
void PostProcessingEffects_rhombusEmitter(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject);
void PostProcessingEffects_tiltScreen(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject);
void PostProcessingEffects_dwarfPlanet(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject);
void PostProcessingEffects_lightingTest(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject);
void PostProcessingEffects_dummy(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject);

#endif
