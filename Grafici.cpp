#include "Grafici.h"

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

Grafici grafici;

void Grafici::begin(Adafruit_GFX &tft)
{
	displayDriver.begin(&tft);
	colorTheme =  new ColorTheme(csBw, ColorSource::computeFromX); 
}

/* use default boundaries and theme */
void Grafici::plot(PlotObj &plotObj, DataSet &dataSet)
{
	DisplayBoundaries boundaries;
	//boundaries.begin();

	plot(plotObj, dataSet, boundaries);
}

/* use default theme */
void Grafici::plot(PlotObj &plotObj, DataSet &dataSet, DisplayBoundaries &customBoundaries)
{
	(&plotObj)->plot(&displayDriver, &dataSet, &customBoundaries, colorTheme);
}

/* use default boundaries and theme */
void Grafici::clear()
{
	DisplayBoundaries boundaries;
	//boundaries.begin();

	clear(boundaries);
}

/* use default theme */
void Grafici::clear(DisplayBoundaries &boundaries)
{
	DataPoint bl(0.0, 0.0);
	DataPoint tr(1.0, 1.0);

	displayDriver.fillRectangle(boundaries.project(bl),
								boundaries.project(tr),
								colorTheme->getColor(0.0));
}
