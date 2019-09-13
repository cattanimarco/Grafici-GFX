#include "Grafici.h"

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

void Grafici::begin(Adafruit_GFX &tft, ColorPalette &colorScheme)
{
	displayDriver.begin(&tft);
}

/* use default boundaries and theme */
void Grafici::plot(PlotFunction plotFunction, Dataset &dataset)
{
	DisplayBoundaries boundaries;
	boundaries.begin();

	plot(plotFunction, dataset, boundaries, colorTheme);
}

/* use default theme */
void Grafici::plot(PlotFunction plotFunction, Dataset &dataset, DisplayBoundaries &customBoundaries)
{
	plot(plotFunction, dataset, customBoundaries, colorTheme);
}

/* use default boundaries */
void Grafici::plot(PlotFunction plotFunction, Dataset &dataset, ColorTheme &customTheme)
{
	DisplayBoundaries boundaries;
	boundaries.begin();

	plot(plotFunction, dataset, boundaries, customTheme);
}

/* no default parameters */
void Grafici::plot(PlotFunction plotFunction, Dataset &dataset, DisplayBoundaries &customBoundaries, ColorTheme &customTheme)
{
	plotFunction(&displayDriver, &dataset, &customBoundaries, &customTheme);
}

/* use default boundaries and theme */
void Grafici::clear()
{
	DisplayBoundaries boundaries;
	boundaries.begin();

	clear(boundaries, colorTheme);
}

/* use default theme */
void Grafici::clear(DisplayBoundaries &boundaries)
{
	clear(boundaries, colorTheme);
}

/* use default boundaries */
void Grafici::clear(ColorTheme &customTheme)
{
	DisplayBoundaries boundaries;
	boundaries.begin();

	clear(boundaries, customTheme);
}

/* no default parameters */
void Grafici::clear(DisplayBoundaries &boundaries, ColorTheme &customTheme)
{
	DataPoint bl(0.0, 0.0);
	DataPoint tr(1.0, 1.0);

	displayDriver.fillRectangle(boundaries.project(bl,displayDriver),boundaries.project(tr,displayDriver), customTheme.getColor(0.0));
}
