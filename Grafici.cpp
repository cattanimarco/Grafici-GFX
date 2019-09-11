#include "Grafici.h"

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

void Grafici::begin(Adafruit_GFX &tft, ColorPalette &colorScheme)
{
	_displayDriver.begin(&tft);
	_theme.colorScheme = &colorScheme;
	_theme.drawColor = ColorTheme::COLOR_THEME;
	_theme.markerSize = min(_displayDriver.height, _displayDriver.width) * 0.05;
}

Boundaries Grafici::baseBoundaries(void)
{
	Boundaries boundaries;

	boundaries.begin(_displayDriver);

	return boundaries;
}

/* use default boundaries and theme */
void Grafici::plot(PlotFunction plotFunction, Dataset &dataset)
{
	Boundaries boundaries;
	boundaries.begin(_displayDriver);

	plot(plotFunction, dataset, boundaries, _theme);
}

/* use default theme */
void Grafici::plot(PlotFunction plotFunction, Dataset &dataset, Boundaries &customBoundaries)
{
	plot(plotFunction, dataset, customBoundaries, _theme);
}

/* use default boundaries */
void Grafici::plot(PlotFunction plotFunction, Dataset &dataset, ColorTheme &customSettings)
{
	Boundaries boundaries;
	boundaries.begin(_displayDriver);

	plot(plotFunction, dataset, boundaries, customSettings);
}

/* no default parameters */
void Grafici::plot(PlotFunction plotFunction, Dataset &dataset, Boundaries &customBoundaries, ColorTheme &customSettings)
{
	plotFunction(&_displayDriver, &dataset, &customBoundaries, &customSettings);
}

/* use default boundaries and theme */
void Grafici::clear()
{
	Boundaries boundaries;
	boundaries.begin(_displayDriver);

	clear(boundaries, _theme);
}

/* use default theme */
void Grafici::clear(Boundaries &boundaries)
{
	clear(boundaries, _theme);
}

/* use default boundaries */
void Grafici::clear(ColorTheme &customSettings)
{
	Boundaries boundaries;
	boundaries.begin(_displayDriver);

	clear(boundaries, customSettings);
}

/* no default parameters */
void Grafici::clear(Boundaries &boundaries, ColorTheme &customSettings)
{
	Datapoint a(0.0, 0.0);
	Datapoint b(1.0, 1.0);

	_displayDriver.fillRectangle(boundaries.project(a).setColor(customSettings.colorScheme->getBkgColor()),
								 boundaries.project(b).setColor(customSettings.colorScheme->getBkgColor()));
}

void Grafici::clear()
{
	Boundaries boundaries;
	boundaries.begin(_displayDriver);

	clear(boundaries);
}

void Grafici::clear(Boundaries &boundaries)
{
}
