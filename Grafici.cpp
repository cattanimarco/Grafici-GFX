#include "Grafici.h"


void Grafici::begin(Adafruit_GFX &tft)
{
	_displayDriver.begin(&tft); 
}

Boundaries Grafici::baseBoundaries(void)
{
	Boundaries boundaries;

	boundaries.begin(_displayDriver);

	return boundaries;
	
}

void Grafici::plot(PlotFunction plotFunction, Dataset *dataset,  ColorScheme *colorScheme, Boundaries *boundaries)
{
	Boundaries _boundaries;

	if (boundaries == NULL)
	{
		_boundaries.begin(_displayDriver);
		boundaries = &_boundaries;
	}

	plotFunction(&_displayDriver, dataset, boundaries, colorScheme);
}

