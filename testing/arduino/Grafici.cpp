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

void Grafici::plot(PlotFunction plotFunction, Dataset *dataset, ColorScheme *colorScheme, Boundaries *boundaries)
{
	Boundaries _boundaries;

	if (boundaries == NULL)
	{
		_boundaries.begin(_displayDriver);
		boundaries = &_boundaries;
	}

	plotFunction(&_displayDriver, dataset, boundaries, colorScheme);
}

void Grafici::clear(ColorScheme *colorScheme, Boundaries *boundaries)
{
	Boundaries _boundaries;

	if (boundaries == NULL)
	{
		_boundaries.begin(_displayDriver);
		boundaries = &_boundaries;
	}

	Datapoint a(0.0, 0.0);
	Datapoint b(1.0, 1.0);

	_displayDriver.fillRectangle(boundaries->project(a).setColor(colorScheme->bkg),
								 boundaries->project(b).setColor(colorScheme->bkg));
}
