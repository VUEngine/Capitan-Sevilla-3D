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

#include <PostProcessingEffects.h>
#include <Optics.h>
#include <Utilities.h>
#include <Hero.h>
#include <DirectDraw.h>
#include <Game.h>
#include <Container.h>
#include <Entity.h>
#include <VIPManager.h>
#include <Camera.h>


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

#define SIZE_OF_U16_POWER		1
#define SIZE_OF_S16_POWER		1
#define Y_STEP_SIZE				16
#define Y_STEP_SIZE_2_EXP		4
#define __MODULO(n, m)			(n & (m - 1))


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------


u32 PostProcessingEffects_writeToFrameBuffer(u16 y, u16 shift, u32* columnSourcePointer, u32 previousSourcePointerValue);
void PostProcessingEffects_drawRhombus(int radius, u32 color, PixelVector screenPixelPosition, int parallax);


//---------------------------------------------------------------------------------------------------------
//												FUNCTIONS
//---------------------------------------------------------------------------------------------------------

void PostProcessingEffects_waterStream(u32 currentDrawingFrameBufferSet,
								s16 xStart, s16 xEnd, s16 xDisplacement, u16 xStep,
								s16 yStart, s16 yEnd, s16 yDisplacement,
								const u16 yStep[], u16 numberOfYSpeeds, u16* yStepIndex, s16 yStepThrottle,
								s16 y[], u16 numberOfYs,
								const u16 dropletLength[], u16 numberOfDropletSize, u16* dropletLengthIndex, int minimumDropletLength,
								const s16 dropletParallax[], u16 numberOfDropletParallax)
{
	int yIndex = 0;

	if(xStart < _cameraFrustum->x0)
	{
		xStart = _cameraFrustum->x0;
	}

	if(xEnd > _cameraFrustum->x1 - 1)
	{
		xEnd = _cameraFrustum->x1 - 1;
	}

	if(yStart < _cameraFrustum->y0)
	{
		yStart = _cameraFrustum->y0;
	}

	if(yEnd > _cameraFrustum->y1 - 1)
	{
		yEnd = _cameraFrustum->y1 - 1;
	}

	int x = xDisplacement + xStart;

	if(x < _cameraFrustum->x0)
	{
		x = xEnd + x % xEnd;
	}

	if(x > xEnd)
	{
		x = x % xEnd;
	}

	// write to framebuffers for both screens
	int counter = 1;

	for(; counter <= xEnd; counter += xStep)
	{
		if(++yIndex >= numberOfYs)
		{
			yIndex = 0;
		}

		x += xStep;

		if(x >= xEnd)
		{
			x -= xEnd;
			x += xStart;
		}

		int leftColumn = x;
		int rightColumn = x;

		s16 dropletParallaxValue = dropletParallax[counter % numberOfDropletParallax];

		leftColumn -= dropletParallaxValue;
		rightColumn += dropletParallaxValue;

		if(0 >= leftColumn || 0 >= rightColumn)
		{
			continue;
		}
		else if(leftColumn >= xEnd || rightColumn >= xEnd)
		{
			continue;
		}

		// get pointer to currently manipulated 32 bits of framebuffer
		u32* columnSourcePointerLeft = (u32*) (currentDrawingFrameBufferSet) + (leftColumn << 4);
		u32* columnSourcePointerRight = (u32*) (currentDrawingFrameBufferSet | 0x00010000) + (rightColumn << 4);

		if(_cameraFrustum->y0 > y[yIndex] + yStart)
		{
			continue;
		}

		// loop current column in steps of 16 pixels (32 bits)
		// ignore the bottom 16 pixels of the screen (gui)
		u32 yStep = (y[yIndex] + yStart) >> Y_STEP_SIZE_2_EXP;
		u32 subY = __MODULO((y[yIndex] + yStart), Y_STEP_SIZE);
		u32 dropletMask = 0xFFFFFFFF << (subY << 1);

		if(++*dropletLengthIndex >= numberOfDropletSize)
		{
			*dropletLengthIndex = 0;
		}

		int effectiveDropletLength = (signed)dropletLength[*dropletLengthIndex] + yStepThrottle;

		if(minimumDropletLength > effectiveDropletLength)
		{
			continue;
		}

		if(effectiveDropletLength >= (signed)Y_STEP_SIZE)
		{
			effectiveDropletLength = Y_STEP_SIZE - 1;
		}

		int dropletLengthDifference = (Y_STEP_SIZE - (subY + effectiveDropletLength)) << 1;

		if(0 < dropletLengthDifference)
		{
			dropletMask &= (0xFFFFFFFF >> dropletLengthDifference);
		}

		u32* sourcePointerLeft = columnSourcePointerLeft + yStep;
		u32* sourcePointerRight = columnSourcePointerRight + yStep;
		u32 sourceValue = *sourcePointerLeft;

		if(!sourceValue)
		{
			if(__MODULO((int)dropletLengthDifference, Y_STEP_SIZE_2_EXP))
			{
				continue;
			}

			u32 content = 0x55555555 & ((dropletMask & ~sourceValue) | (sourceValue & ~dropletMask));
			*sourcePointerLeft = content;
			*sourcePointerRight = content;
		}
		else
		{
			u32 content = (dropletMask & ~sourceValue) | (sourceValue & ~dropletMask);
			*sourcePointerLeft = content;
			*sourcePointerRight = content;

			if(0 > dropletLengthDifference)
			{
				dropletMask = (0xFFFFFFFF << -dropletLengthDifference);
				sourceValue = *(sourcePointerLeft + 1);
				content = (~dropletMask & ~sourceValue) | (sourceValue & dropletMask);
				*(sourcePointerLeft + 1) = content;
				*(sourcePointerRight + 1) = content;
			}
		}
	}

	u16 i = 0;

	for(; i < numberOfYs; i++)
	{
		if(++*yStepIndex >= numberOfYSpeeds)
		{
			*yStepIndex = 0;
		}

		y[i] += yStep[*yStepIndex] + yStepThrottle;

		int cumulativeY = y[i] + yStart + yDisplacement;

		if(yEnd - (Y_STEP_SIZE >> 1) < cumulativeY)
		{
			y[i] = 0;
		}
	}
}

void PostProcessingEffects_calculateRainPrecipitation(fix19_13* yStepThrottle, fix19_13* xStep, fix19_13 maximumYThrottle, fix19_13 minimumYThrottle, fix19_13 maximumXStep, fix19_13 minimumXStep)
{
	static u32 previousTime = 0;
	static u8 timePeriodIndex = 0;
	static u8 rainAccelerationIndex = 0;

	const u8 timePeriod[] =
	{
		30, 25, 40, 35, 50, 50, 40, 45,
		30, 30, 35, 40, 50, 60, 20, 45,
	};

	const s8 rainAcceleration[] =
	{
		1, 0, -1, 0,
	};

	u32 currentTime = Clock_getTime(PlatformerLevelState_getClock(PlatformerLevelState_getInstance()));

	if((currentTime - previousTime) / 1000 > timePeriod[timePeriodIndex])
	{
		previousTime = currentTime;

		if(++timePeriodIndex >= sizeof(timePeriod) / sizeof(u8))
		{
			timePeriodIndex = 0;
		}

		if(++rainAccelerationIndex >= sizeof(rainAcceleration) / sizeof(s8))
		{
			rainAccelerationIndex = 0;
		}
	}

	// multiply by the game cycle per second
	int rainPeriod =  __I_TO_FIX19_13(((int)timePeriod[timePeriodIndex] + previousTime % timePeriod[timePeriodIndex]) * 50);

	*yStepThrottle += __FIX19_13_DIV(rainAcceleration[rainAccelerationIndex] * (maximumYThrottle - minimumYThrottle), rainPeriod);
	*xStep -= __FIX19_13_DIV(rainAcceleration[rainAccelerationIndex] * (maximumXStep - minimumXStep), rainPeriod);

	if(*yStepThrottle < minimumYThrottle)
	{
		*yStepThrottle = minimumYThrottle;
	}
	else if(*yStepThrottle > maximumYThrottle)
	{
		*yStepThrottle = maximumYThrottle;
	}

	if(*xStep < minimumXStep)
	{
		*xStep = minimumXStep;
	}
	else if(*xStep > maximumXStep)
	{
		*xStep = maximumXStep;
	}
}

void PostProcessingEffects_rain(u32 currentDrawingFrameBufferSet __attribute__ ((unused)), SpatialObject spatialObject __attribute__ ((unused)))
{
 	#define RAIN_X_RANGE_1					383
 	#define RAIN_MINIMUM_DROPLET_LENGTH		3
 	#define RAIN_MINIMUM_Y_THROTTLE_1		__I_TO_FIX19_13(-5)
 	#define RAIN_MAXIMUM_Y_THROTTLE_1		__I_TO_FIX19_13(2)
 	#define RAIN_MINIMUM_X_STEP_1			__I_TO_FIX19_13(15)
 	#define RAIN_MAXIMUM_X_STEP_1			__I_TO_FIX19_13(90)
	static u16 yStepIndex = 0;
	static u16 dropletLengthIndex = 0;
	static fix19_13 yStepThrottle = RAIN_MINIMUM_Y_THROTTLE_1;
	static fix19_13 xStep = RAIN_MAXIMUM_X_STEP_1;
 	static Vector3D cameraPreviousPosition = {0, 0, 0};
 	static int cumulativeX = 0;
 	fix19_13 yScreenDisplacement = __I_TO_FIX19_13(__METERS_TO_PIXELS(_cameraPosition->y - cameraPreviousPosition.y));

 	cumulativeX += __METERS_TO_PIXELS(_cameraPosition->x - cameraPreviousPosition.x);
	PostProcessingEffects_calculateRainPrecipitation(&yStepThrottle, &xStep, RAIN_MAXIMUM_Y_THROTTLE_1, RAIN_MINIMUM_Y_THROTTLE_1, RAIN_MAXIMUM_X_STEP_1, RAIN_MINIMUM_X_STEP_1);
	cameraPreviousPosition = *_cameraPosition;

 	const s16 dropletParallax[] =
 	{
 		0, 5, -2, 3, -3, 6, 9, -4, 0, 0, 8,
		7, -3, 2, -2, 0, 5, -3, 4, -4, 6, -7,
		0, 6, -6, 1, 0, 0, 5, -5, -7, 8, 9, 0
		,
 	};

 	const u16 dropletLength[] =
 	{
 		3, 4, 5, 5, 4, 3, 6, 6, 5, 6, 8, 5, 5,
 	};

	static s16 y[] =
	{
		12, 30, 85, 21, 74, 59, 14, 97, 62, 92, 44, 2,
		14, 97, 62, 92, 44, 2, 12, 30, 85, 21, 74, 59,
		12, 30, 85, 92, 44, 2, 74, 59, 14, 97, 62, 92,
		12, 30, 85, 21, 21, 74, 59, 14, 97, 62, 44, 2,
	};

	const u16 yStep[] =
	{
		4, 5, 6, 6, 7, 8, 8, 6, 5, 4, 4, 5,
		6, 7, 8, 4, 5, 5, 5, 6, 7, 5, 4, 8,
		4, 4, 7, 8, 8, 5, 7, 3, 4, 7, 5, 3,
		6, 7, 4, 5, 6, 8, 5, 5, 6, 7, 8, 6,
		6, 7, 8, 4, 5, 6, 5, 4, 8, 5, 4, 4,
		8, 5, 7, 3, 4, 4, 7, 8, 4, 7, 5, 3,


/*		9, 7, 8, 7, 6, 7, 8, 5, 6, 8, 4, 5,
		5, 6, 8, 7, 7, 6, 5, 5, 6, 4, 7, 8,
		8, 7, 9, 6, 8, 7, 6, 6, 5, 7, 8, 7,
		7, 6, 7, 7, 6, 5, 6, 7, 6, 6, 5, 8,
		5, 6, 8, 4, 4, 6, 5, 5, 6, 6, 7, 8,
		6, 7, 8, 7, 6, 7, 8, 4, 6, 8, 6, 5,
		7, 6, 7, 5, 6, 5, 6, 7, 6, 9, 5, 8,
		*/
	};

	// must account for the camera displacement
	yStepThrottle -= yScreenDisplacement;

	PostProcessingEffects_waterStream(currentDrawingFrameBufferSet,
										0, __SCREEN_WIDTH -1, -cumulativeX, __FIX19_13_TO_I(xStep),
										_cameraFrustum->y0, _cameraFrustum->y1, 0,
										yStep, sizeof(yStep) >> SIZE_OF_U16_POWER, &yStepIndex, __FIX19_13_TO_I(yStepThrottle),
										y, sizeof(y) >> SIZE_OF_S16_POWER,
										dropletLength, sizeof(dropletLength) >> SIZE_OF_U16_POWER, &dropletLengthIndex, RAIN_MINIMUM_DROPLET_LENGTH,
										dropletParallax, sizeof(dropletParallax) >> SIZE_OF_S16_POWER);
	yStepThrottle += yScreenDisplacement;
}

void PostProcessingEffects_waterFall(u32 currentDrawingFrameBufferSet, Vector3D position, int width, int height, int yStepThrottle)
{
	static u16 yStepIndex = 0;
	static u16 dropletLengthIndex = 0;

 	const s16 dropletParallax[] =
 	{
 		-2
		,
 	};

 	const u16 dropletLength[] =
 	{
 		5, 6, 9, 11, 4, 13, 11, 4, 7, 9, 5, 12, 9,
 		11, 10, 4, 7, 12, 12, 10, 8, 5, 4, 8, 10
 	};

	static s16 y[] =
	{
		12, 30, 85, 21, 74, 59, 14, 97, 62, 92, 44, 2,
		14, 97, 62, 92, 44, 2, 12, 30, 85, 21, 74, 59,
		12, 30, 85, 92, 44, 2, 74, 59, 14, 97, 62, 92,
		12, 30, 85, 21, 21, 74, 59, 14, 97, 62, 44, 2,
		12, 30, 85, 21, 74, 59, 14, 97, 62, 92, 44, 2,
		14, 97, 62, 92, 44, 2, 12, 30, 85, 21, 74, 59,
		12, 30, 85, 92, 44, 2, 74, 59, 14, 97, 62, 92,
		12, 30, 85, 21, 21, 74, 59, 14, 97, 62, 44, 2,

	};

	const u16 yStep[] =
	{
		4, 5, 6, 6, 7, 8, 8, 6, 5, 4, 4, 5,
		6, 7, 8, 4, 5, 5, 5, 6, 7, 5, 4, 8,
		4, 4, 7, 8, 8, 5, 7, 3, 4, 7, 5, 3,
		6, 7, 4, 5, 6, 8, 5, 5, 6, 7, 8, 6,
		6, 7, 8, 4, 5, 6, 5, 4, 8, 5, 4, 4,
		8, 5, 7, 3, 4, 4, 7, 8, 4, 7, 5, 3,
	};

	PostProcessingEffects_waterStream(currentDrawingFrameBufferSet,
										__FIX10_6_TO_I(position.x) - (width >> 1), __FIX10_6_TO_I(position.x) + (width >> 1), 0, 1,
										__FIX10_6_TO_I(position.y) - (height >> 1), __FIX10_6_TO_I(position.y) + (height >> 1), 0,
										yStep, sizeof(yStep) >> SIZE_OF_U16_POWER, &yStepIndex, yStepThrottle,
										y, sizeof(y) >> SIZE_OF_S16_POWER,
										dropletLength, sizeof(dropletLength) >> SIZE_OF_U16_POWER, &dropletLengthIndex, 1,
										dropletParallax, sizeof(dropletParallax) >> SIZE_OF_S16_POWER);
}

void PostProcessingEffects_waterFall20x100(u32 currentDrawingFrameBufferSet __attribute__ ((unused)), SpatialObject spatialObject __attribute__ ((unused)))
{
	if(!__IS_OBJECT_ALIVE(spatialObject))
	{
		return;
	}

	Vector3D spatialObjectPosition = Vector3D_getRelativeToCamera(*__VIRTUAL_CALL(SpatialObject, getPosition, spatialObject));

	PostProcessingEffects_waterFall(currentDrawingFrameBufferSet, spatialObjectPosition, 20, 100, 0);
}

void PostProcessingEffects_applyMask(u32 currentDrawingFrameBufferSet, int xStart, int xEnd, int yStart, int yEnd, u32 mask)
{
	if(xEnd < xStart || yEnd < yStart)
	{
		return;
	}

	if(xStart < _cameraFrustum->x0)
	{
		xStart = _cameraFrustum->x0;
	}

	if(xEnd > _cameraFrustum->x1)
	{
		xEnd = _cameraFrustum->x1;
	}

	if(yStart < _cameraFrustum->y0)
	{
		yStart = _cameraFrustum->y0;
	}

	if(yEnd > _cameraFrustum->y1)
	{
		yEnd = _cameraFrustum->y1;
	}

	for(; xStart <= xEnd; xStart++)
	{
		// get pointer to currently manipulated 32 bits of framebuffer
		u32* columnSourcePointerLeft = (u32*) (currentDrawingFrameBufferSet) + (xStart << 4);
		u32* columnSourcePointerRight = (u32*) (currentDrawingFrameBufferSet | 0x00010000) + (xStart << 4);

		int y = yStart;

		for(; y < yEnd; y++)
		{
			u32* sourcePointerLeft = columnSourcePointerLeft + y;
			u32* sourcePointerRight = columnSourcePointerRight + y;
			*sourcePointerLeft &= mask;
			*sourcePointerRight &= mask;
		}
	}
}

void PostProcessingEffects_ellipticalWindow(u32 currentDrawingFrameBufferSet, Vector3D position, s16 ellipsisArc[], u16 ellipsisHorizontalAxisSize, u32 penumbraMask, bool roundBorder)
{
 	int xPosition = __METERS_TO_PIXELS(position.x);
 	int yPosition = __METERS_TO_PIXELS(position.y);
	// move y position to the closest 16 multiple
	int tempYPosition = yPosition + (Y_STEP_SIZE >> 1);
	yPosition = tempYPosition - __MODULO(tempYPosition, Y_STEP_SIZE);

	int ellipsisArcIndex = 0 > xPosition - ellipsisHorizontalAxisSize ? (ellipsisHorizontalAxisSize - xPosition) : 0;
	int ellipsisArcIndexDelta = 1;
	int x = 0;

	for(x = _cameraFrustum->x0; x < _cameraFrustum->x1; x++)
	{
		// get pointer to currently manipulated 32 bits of framebuffer
		u32* columnSourcePointerLeft = (u32*) (currentDrawingFrameBufferSet) + (x << 4);
		u32* columnSourcePointerRight = (u32*) (currentDrawingFrameBufferSet | 0x00010000) + (x << 4);

		int yStart = _cameraFrustum->y0 >> Y_STEP_SIZE_2_EXP;
		int yEnd = _cameraFrustum->y1 >> Y_STEP_SIZE_2_EXP;
		int y = yStart;

		int ellipsisY = ellipsisArc[ellipsisArcIndex];
		int maskDisplacement = __MODULO(ellipsisY, Y_STEP_SIZE) << 1;
		u32 upperMask = roundBorder ? ~(0xFFFFFFFF >> maskDisplacement) : 0xFFFFFFFF;
		u32 lowerMask = roundBorder ? ~(0xFFFFFFFF << maskDisplacement) : 0xFFFFFFFF;

		int yLowerLimit =  (yPosition + ellipsisY) >> Y_STEP_SIZE_2_EXP;
		int yUpperLimit = (yPosition >> Y_STEP_SIZE_2_EXP) - (yLowerLimit - (yPosition >> Y_STEP_SIZE_2_EXP));

		if(yUpperLimit > yEnd)
		{
			yUpperLimit = yEnd;
		}

		if(yLowerLimit < yStart)
		{
			yLowerLimit = yStart;
		}

		u32* sourcePointerLeft = columnSourcePointerLeft + y;
		u32* sourcePointerRight = columnSourcePointerRight + y;

		if((unsigned)(x - (xPosition - ellipsisHorizontalAxisSize)) < (unsigned)(ellipsisHorizontalAxisSize << 1))
		{
			for(; y < yUpperLimit; y++)
			{
				sourcePointerLeft = columnSourcePointerLeft + y;
				sourcePointerRight = columnSourcePointerRight + y;
				*sourcePointerLeft = 0;
				*sourcePointerRight = 0;
			}

			if(y == yUpperLimit && y < yEnd)
			{
				sourcePointerLeft = columnSourcePointerLeft + y;
				sourcePointerRight = columnSourcePointerRight + y;
				*sourcePointerLeft &= upperMask & penumbraMask;
				*sourcePointerRight &= upperMask & penumbraMask;
			}

			if(penumbraMask)
			{
				y = yUpperLimit + 1;

				if(y >= yStart && y < yEnd)
				{
					u32* sourcePointerLeft = columnSourcePointerLeft + y;
					u32* sourcePointerRight = columnSourcePointerRight + y;
					*sourcePointerLeft &= penumbraMask | upperMask;
					*sourcePointerRight &= penumbraMask | upperMask;
				}

				y = yLowerLimit - 1;

				if(y >= yStart && y < yEnd)
				{
					u32* sourcePointerLeft = columnSourcePointerLeft + y;
					u32* sourcePointerRight = columnSourcePointerRight + y;
					*sourcePointerLeft &= penumbraMask | lowerMask;
					*sourcePointerRight &= penumbraMask | lowerMask;
				}
			}

			y = yLowerLimit;

			if(y >= yStart && y < yEnd)
			{
				sourcePointerLeft = columnSourcePointerLeft + y;
				sourcePointerRight = columnSourcePointerRight + y;
				*sourcePointerLeft &= lowerMask & penumbraMask;
				*sourcePointerRight &= lowerMask & penumbraMask;
			}

			for(; ++y < yEnd;)
			{
				u32* sourcePointerLeft = columnSourcePointerLeft + y;
				u32* sourcePointerRight = columnSourcePointerRight + y;
				*sourcePointerLeft = 0;
				*sourcePointerRight = 0;
			}

			ellipsisArcIndex += ellipsisArcIndexDelta;

			if(ellipsisArcIndex >= ellipsisHorizontalAxisSize)
			{
				ellipsisArcIndexDelta = -1;
				ellipsisArcIndex = ellipsisHorizontalAxisSize - 1;
			}
			else if(0 > ellipsisArcIndex)
			{
				ellipsisArcIndexDelta = 1;
				ellipsisArcIndex = 0;
			}
		}
		else
		{
			for(; y < yEnd; y++)
			{
				sourcePointerLeft = columnSourcePointerLeft + y ;
				sourcePointerRight = columnSourcePointerRight + y;
				*sourcePointerLeft = 0;
				*sourcePointerRight = 0;
			}
		}
	}
}

void PostProcessingEffects_lantern(u32 currentDrawingFrameBufferSet __attribute__ ((unused)), SpatialObject spatialObject __attribute__ ((unused)))
{
 	static bool ellipsisArcCalculated = false;

	Hero hero = Hero_getInstance();

 	if(!hero)
 	{
 		if(ellipsisArcCalculated)
 		{
 			PostProcessingEffects_applyMask(currentDrawingFrameBufferSet, _cameraFrustum->x0, _cameraFrustum->x1, _cameraFrustum->y0, _cameraFrustum->y1, 0);
 		}
 		return;
 	}

 	Vector3D heroPosition = *Container_getGlobalPosition(__SAFE_CAST(Container, hero));
 	heroPosition.y -= __PIXELS_TO_METERS(10);

	heroPosition = Vector3D_getRelativeToCamera(heroPosition);

 	#define ELLIPSIS_X_AXIS_LENGTH		55
 	#define ELLIPSIS_Y_AXIS_LENGTH		60
	#define PENUMBRA_MASK				0x55555555

 	static s16 ellipsisArc[ELLIPSIS_X_AXIS_LENGTH];

 	if(!ellipsisArcCalculated)
	{
		ellipsisArcCalculated = true;

		u16 i = 0;
		float x = 0;

		for(i = sizeof(ellipsisArc) >> SIZE_OF_S16_POWER; --i; x++)
		{
			ellipsisArc[i] = ELLIPSIS_Y_AXIS_LENGTH * Math_squareRoot(((ELLIPSIS_X_AXIS_LENGTH * ELLIPSIS_X_AXIS_LENGTH) - (x * x)) / (ELLIPSIS_X_AXIS_LENGTH * ELLIPSIS_X_AXIS_LENGTH));
		}
	}

	PostProcessingEffects_ellipticalWindow(currentDrawingFrameBufferSet, heroPosition, ellipsisArc, ELLIPSIS_X_AXIS_LENGTH, PENUMBRA_MASK, true);
}

/**
 * Uses directdraw to draw a rhombus around the spatialObject.
 * This effect only writes to the framebuffers, but does not read them. Since write access is much quicker
 * than reading, and since only a few pixels are affected, this effect runs well on hardware.
 *
 * @param currentDrawingFrameBufferSet	The framebuffer set that's currently being accessed
 */
void PostProcessingEffects_rhombusEmitter(u32 currentDrawingFrameBufferSet __attribute__ ((unused)), SpatialObject spatialObject)
{
	// runtime working variable
	static int radius = 4;

	if(!__IS_OBJECT_ALIVE(spatialObject))
	{
		return;
	}

	PixelVector screenPixelPosition = Vector3D_projectToPixelVector(Vector3D_getRelativeToCamera(*__VIRTUAL_CALL(SpatialObject, getPosition, spatialObject)), 0);

	// increase radius by 1 in each cycle
	radius++;

	if(radius > 184)
	{
		// reset radius when reaching a certain length
		radius = 4;
	}
	else if(radius > 64)
	{
		// pause for a little bit before restarting
		return;
	}

	// draw a rhombus around object with given radius and color
	PostProcessingEffects_drawRhombus((radius), __COLOR_BLACK, screenPixelPosition, -((radius + 4) >> 5));
//	PostProcessingEffects_drawRhombus((radius >> 1), __COLOR_BLACK, screenPixelPosition, -(((radius >> 1) + 4) >> 5));
}

/**
 * Applies a full screen wobble distortion that is reminiscent of water waves. This effect reads and write
 * almost the whole screen and is therefore not feasible on hardware.
 *
 * @param currentDrawingFrameBufferSet	The framebuffer set that's currently being accessed
 */
void PostProcessingEffects_wobble(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject __attribute__ ((unused)))
{
	u16 x = 0, y = 0;
	u32 previousSourcePointerValueLeft = 0;
	u32 previousSourcePointerValueRight = 0;

	// runtime working variables
	static int waveLutIndex = 0;

	// look up table of bitshifts performed on rows
	// values must be multiples of 2
	const u32 waveLut[128] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
		6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
		8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
		8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
		6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};

	// write to framebuffers for both screens
	// loop columns
	for(x = 0; x < 384; x++)
	{
		// get pointer to currently manipulated 32 bits of framebuffer
		u32* columnSourcePointerLeft = (u32*) (currentDrawingFrameBufferSet) + (x << 4);
		u32* columnSourcePointerRight = (u32*) (currentDrawingFrameBufferSet | 0x00010000) + (x << 4);

		// the shifted out pixels on top should be black
		previousSourcePointerValueLeft = 0;
		previousSourcePointerValueRight = 0;

		// increase look up table index, wrap around if necessary
		waveLutIndex += (waveLutIndex < 127) ? 1 : -127;

		// we can skip further processing for the current column if no shifting would be done on it
		if(waveLut[waveLutIndex] == 0)
		{
			continue;
		}

		// loop current column in steps of 16 pixels (32 bits)
		// ignore the bottom 16 pixels of the screen (gui)
		for(y = 0; y < 13; y++)
		{
			previousSourcePointerValueLeft = PostProcessingEffects_writeToFrameBuffer(y, waveLut[waveLutIndex], columnSourcePointerLeft, previousSourcePointerValueLeft);
			previousSourcePointerValueRight = PostProcessingEffects_writeToFrameBuffer(y, waveLut[waveLutIndex], columnSourcePointerRight, previousSourcePointerValueRight);
		}
	}

	// move the wave one pixel in the next frame
	waveLutIndex++;
}

/**
 * "Tilts" the game image by a few percent by gradually shifting columns. This effect reads and write
 * almost the whole screen and is therefore not feasible on hardware.
 *
 * @param currentDrawingFrameBufferSet	The framebuffer set that's currently being accessed
 */
void PostProcessingEffects_tiltScreen(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject __attribute__ ((unused)))
{
	u8 buffer = 0, currentShift = 0;
	u16 x = 0, y = 0;
	u32 previousSourcePointerValue = 0;

	// write to framebuffers for both screens
	for(; buffer < 2; buffer++)
	{
		// loop columns that shall be shifted
		for(x = 0; x < 360; x++)
		{
			// get pointer to currently manipulated 32 bits of framebuffer
			u32* columnSourcePointer = (u32*) (currentDrawingFrameBufferSet | (buffer ? 0x00010000 : 0)) + (x << 4);

			// the shifted out pixels on top should be black
			previousSourcePointerValue = 0;

			// get shift for current column
			currentShift = 30 - ((x / 24) << 1);

			// loop current column in steps of 16 pixels (32 bits)
			// ignore the bottom 16 pixels of the screen (gui)
			for(y = 0; y < 13; y++)
			{
				previousSourcePointerValue = PostProcessingEffects_writeToFrameBuffer(y, currentShift, columnSourcePointer, previousSourcePointerValue);
			}
		}
	}
}

/**
 * "Bends down" the left and right edges of the screen to make the world look like a very small planet.
 * This effect reads and write a fourth of the screen and is therefore running OK-ish on hardware, but
 * still cutting the frame rate in half.
 *
 * @param currentDrawingFrameBufferSet	The framebuffer set that's currently being accessed
 */
void PostProcessingEffects_dwarfPlanet(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject __attribute__ ((unused)))
{
	// look up table of bitshifts performed on rows
	const u32 lut[96] =
	{
		2,
		4,
		6,	6,
		8,	8,
		10, 10, 10,
		12, 12, 12,
		14, 14, 14, 14,
		16, 16, 16, 16, 16,
		18, 18, 18, 18, 18, 18,
		20, 20, 20, 20, 20, 20, 20,
		22, 22, 22, 22, 22, 22, 22, 22,
		24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
		26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
		28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
		30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
	};

	int lutEntries = sizeof(lut) / sizeof(u32);
	// runtime working variables

	int counter = lutEntries;

	// loop columns of left fourth of screen
	for(; --counter;)
	{
		int x1 = (lutEntries - counter);
		int x2 = __SCREEN_WIDTH - counter;

		// get pointer to currently manipulated 32 bits of framebuffer
		u32* columnSourcePointerLeft1 = (u32*) (currentDrawingFrameBufferSet) + (x1 << 4);
		u32* columnSourcePointerRight1 = (u32*) (currentDrawingFrameBufferSet | 0x00010000) + (x1 << 4);
		u32* columnSourcePointerLeft2 = (u32*) (currentDrawingFrameBufferSet) + (x2 << 4);
		u32* columnSourcePointerRight2 = (u32*) (currentDrawingFrameBufferSet | 0x00010000) + (x2 << 4);

		// the shifted out pixels on top should be black
		u32 previousSourcePointerValueLeft1 = 0;
		u32 previousSourcePointerValueRight1 = 0;
		u32 previousSourcePointerValueLeft2 = 0;
		u32 previousSourcePointerValueRight2 = 0;

		u16 y = 0;

		// loop current column in steps of 16 pixels (32 bits)
		// ignore the bottom 16 pixels of the screen (gui)
		for(y = 0; y < 13; y++)
		{
			previousSourcePointerValueLeft1 = PostProcessingEffects_writeToFrameBuffer(y, 32 - lut[lutEntries - counter], columnSourcePointerLeft1, previousSourcePointerValueLeft1);
			previousSourcePointerValueRight1 = PostProcessingEffects_writeToFrameBuffer(y, 32 - lut[lutEntries - counter], columnSourcePointerRight1, previousSourcePointerValueRight1);
			previousSourcePointerValueLeft2 = PostProcessingEffects_writeToFrameBuffer(y, 32 - lut[counter], columnSourcePointerLeft2, previousSourcePointerValueLeft2);
			previousSourcePointerValueRight2 = PostProcessingEffects_writeToFrameBuffer(y, 32 - lut[counter], columnSourcePointerRight2, previousSourcePointerValueRight2);
		}
	}
}

/**
 * Increases the palette index within a square area around the hero, effectively "lightening" it up.
 * This effect reads and write only a small portion of the screen and is therefore semi-feasible on
 * hardware.
 *
 * @param currentDrawingFrameBufferSet	The framebuffer set that's currently being accessed
 */
void PostProcessingEffects_lightingTest(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject __attribute__ ((unused)))
{
	// the frameBufferSetToModify dictates which frame buffer set (remember that there are 4 frame buffers,
	// 2 per eye) has been written by the VPU and you can work on

	// will add a post processing effect around the hero
	Hero hero = Hero_getInstance();

	if(!hero)
	{
		return;
	}

	Vector3D heroPosition = Vector3D_getRelativeToCamera(*Container_getGlobalPosition(__SAFE_CAST(Container, hero)));
	heroPosition.x = __FIX10_6_TO_I(heroPosition.x);
	heroPosition.y = __FIX10_6_TO_I(heroPosition.y);

	// the pixel in screen coordinates (x: 0 - 383, y: 0 - 223)
	int x = 0;
	int y = 0;

	// these will be used to dictate the size of the screen portion to be affected
	int xCounter = 0;
	int yCounter = 0;

	// this is just a test, so that's why these are static
	static bool vibrate = false;
	static int wait = 0;

	// write to framebuffers for both screens
	u32 buffer = 0;
	for(; buffer < 2; buffer++)
	{
		for(xCounter = 48, x = heroPosition.x - (xCounter >> 1); xCounter--; x++)
		{
			for(yCounter = 48, y = heroPosition.y - (yCounter >> 1); yCounter >= 0; yCounter -= 4, y += 4)
			{
				BYTE* sourcePointer = (BYTE*) (currentDrawingFrameBufferSet | (buffer ? 0x00010000 : 0));
				sourcePointer += ((x << 6) + (y >> 2));

				/*
				// negative
				*sourcePointer = ~*sourcePointer;
				*/

				// noise
				if(vibrate)
				{
					if(xCounter & 1)
					{
						// shift down one pixel
						*sourcePointer = (*sourcePointer & 0x03) | (*sourcePointer << 2);
					}
					else
					{
						// shift up one pixel
						*sourcePointer = (*sourcePointer & 0xC0) | (*sourcePointer >> 2);
					}
				}

				// add 1 to each pixel's color to "light it up"
				*sourcePointer |= 0x55;
			}
		}
	}

	// this just create a simple delay to not shift the pixels on each cycle
	if(--wait < 0)
	{
		wait = 4;
		vibrate = !vibrate;
	}
}

/**
 * Helper function used by various post processing effects to write a 32 bit value to the framebuffer
 * (16 pixels)
 *
 * @param y								Y coordinate (true y value = y * 16)
 * @param shift							Number of bits to shift the pixels by
 * @param columnSourcePointer			Framebuffer address of the current column (x value)
 * @param previousSourcePointerValue	Value from the loop's previous cycle (effectively where y - 1)
 */
inline u32 PostProcessingEffects_writeToFrameBuffer(u16 y, u16 shift, u32* columnSourcePointer, u32 previousSourcePointerValue)
{
	// pointer to currently manipulated 32 bits of framebuffer
	u32* sourcePointer = columnSourcePointer + y;

	// save current pointer value to temp var and shift highest x bits of it, according to lut,
	// to the lowest bits, since we want to insert these
	u32 sourcePointerCurrentValue = *sourcePointer;
	u32 previousSourcePointerLeftValueTemp = sourcePointerCurrentValue >> (32 - shift);

	// manipulate current 32 bits in frame buffer
	*sourcePointer =
		// shift bits according to wave lut
		// it's two bits per pixel, so 2 bits shifted left = 1 pixel shifted down on screen
		(sourcePointerCurrentValue << shift)

		// since the above shifting creates black pixels, we need to carry over these pixels
		// from the previous loop
		| previousSourcePointerValue;

	// we need the current source pointer value from _before_ we modified it, therefore we save it
	// it to a temp variable while modifying
	return previousSourcePointerLeftValueTemp;
}

/**
 * Helper function used by the rhombus emitter effect that prints a rhombus shape to the frame buffer
 *
 * @param radius
 * @param color
 * @param screenPixelPosition
 */
void PostProcessingEffects_drawRhombus(int radius, u32 color, PixelVector screenPixelPosition, int parallax)
{
	DirectDraw directDraw = DirectDraw_getInstance();

	DirectDraw_drawLine(
		directDraw,
		(PixelVector) {screenPixelPosition.x - radius,	screenPixelPosition.y,			0, parallax},
		(PixelVector) {screenPixelPosition.x,				screenPixelPosition.y - radius,	0, parallax},
		color
	);

	DirectDraw_drawLine(
		directDraw,
		(PixelVector) {screenPixelPosition.x + radius,	screenPixelPosition.y,			0, parallax},
		(PixelVector) {screenPixelPosition.x,				screenPixelPosition.y - radius,	0, parallax},
		color
	);

	DirectDraw_drawLine(
		directDraw,
		(PixelVector) {screenPixelPosition.x + radius,	screenPixelPosition.y,			0, parallax},
		(PixelVector) {screenPixelPosition.x,				screenPixelPosition.y + radius,	0, parallax},
		color
	);

	DirectDraw_drawLine(
		directDraw,
		(PixelVector) {screenPixelPosition.x - radius,	screenPixelPosition.y,			0, parallax},
		(PixelVector) {screenPixelPosition.x,				screenPixelPosition.y + radius,	0, parallax},
		color
	);
}

void PostProcessingEffects_dummy(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject __attribute__ ((unused)))
{
	u16 x = 0, y = 0;
	u32 previousSourcePointerValueLeft = 0;
	u32 previousSourcePointerValueRight = 0;

	// write to framebuffers for both screens
	// loop columns
	for(x = 0; x < 384; x++)
	{
		// get pointer to currently manipulated 32 bits of framebuffer
		u32* columnSourcePointerLeft = (u32*) (currentDrawingFrameBufferSet) + (x << 4);
		u32* columnSourcePointerRight = (u32*) (currentDrawingFrameBufferSet | 0x00010000) + (x << 4);

		// the shifted out pixels on top should be black
		previousSourcePointerValueLeft = 0;
		previousSourcePointerValueRight = 0;

		// loop current column in steps of 16 pixels (32 bits)
		// ignore the bottom 16 pixels of the screen (gui)
		for(y = 0; y < 13; y++)
		{
			previousSourcePointerValueLeft = PostProcessingEffects_writeToFrameBuffer(y, 1, columnSourcePointerLeft, previousSourcePointerValueLeft);
			previousSourcePointerValueRight = PostProcessingEffects_writeToFrameBuffer(y, 1, columnSourcePointerRight, previousSourcePointerValueRight);
		}
	}
}

