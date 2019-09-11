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

void Grafici::plot(PlotFunction plotFunction, Dataset &dataset, ColorPalette &colorScheme)
{
	Boundaries boundaries;
	boundaries.begin(_displayDriver);
	plot( plotFunction,  dataset,  colorScheme,  boundaries);
}

void Grafici::plot(PlotFunction plotFunction, Dataset &dataset, ColorPalette &colorScheme, Boundaries &boundaries)
{
	plotFunction(&_displayDriver, &dataset, &boundaries, &colorScheme);
}

void Grafici::clear(ColorPalette &colorScheme)
{
	Boundaries boundaries;
	boundaries.begin(_displayDriver);
	
	clear(colorScheme, boundaries);
}

void Grafici::clear(ColorPalette &colorScheme, Boundaries &boundaries)
{
	Datapoint a(0.0, 0.0);
	Datapoint b(1.0, 1.0);

	_displayDriver.fillRectangle(boundaries.project(a).setColor(colorScheme.bkg),
								 boundaries.project(b).setColor(colorScheme.bkg));
}