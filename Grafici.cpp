#include "Grafici.h"

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

void Grafici::begin(Adafruit_GFX &tft, ColorTheme &colorTheme)
{
	displayDriver.begin(&tft);
	this->colorTheme = &colorTheme;
}

/* use default boundaries and theme */
void Grafici::plot(PlotObject &plotObject, DataSet &dataSet)
{
	DisplayBoundaries boundaries;
	//boundaries.begin();

	plot(plotObject, dataSet, boundaries, *colorTheme);
}

/* use default theme */
void Grafici::plot(PlotObject &plotObject, DataSet &dataSet, DisplayBoundaries &customBoundaries)
{
	plot(plotObject, dataSet, customBoundaries, *colorTheme);
}

/* use default boundaries */
void Grafici::plot(PlotObject &plotObject, DataSet &dataSet, ColorTheme &customTheme)
{
	DisplayBoundaries boundaries;
	//boundaries.begin();

	plot(plotObject, dataSet, boundaries, customTheme);
}

/* no default parameters */
void Grafici::plot(PlotObject &plotObject, DataSet &dataSet, DisplayBoundaries &customBoundaries, ColorTheme &customTheme)
{
	plotObject.plot(&displayDriver, &dataSet, &customBoundaries, &customTheme);
}

/* use default boundaries and theme */
void Grafici::clear()
{
	DisplayBoundaries boundaries;
	//boundaries.begin();

	clear(boundaries, *colorTheme);
}

/* use default theme */
void Grafici::clear(DisplayBoundaries &boundaries)
{
	clear(boundaries, *colorTheme);
}

/* use default boundaries */
void Grafici::clear(ColorTheme &customTheme)
{
	DisplayBoundaries boundaries;
	//boundaries.begin();

	clear(boundaries, customTheme);
}

/* no default parameters */
void Grafici::clear(DisplayBoundaries &boundaries, ColorTheme &customTheme)
{
	DataPoint bl(0.0, 0.0);
	DataPoint tr(1.0, 1.0);

	displayDriver.fillRectangle(boundaries.project(bl),
								boundaries.project(tr),
								customTheme.getColor(0.0));
}
