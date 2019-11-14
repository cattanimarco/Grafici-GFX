#include "Grafici.h"

Grafici grafici;

void Grafici::begin(Adafruit_GFX &tft)
{
	displayDriver.begin(&tft);
	backgroundColor =  colorBlack;
}

/* use default boundaries and theme */
void Grafici::plot(PlotObj &plotObj, DataSet &dataSet)
{
	plot(plotObj, dataSet, boundaries);
}

/* use default theme */
void Grafici::plot(PlotObj &plotObj, DataSet &dataSet, DisplayBoundaries &customBoundaries)
{
	(&plotObj)->plot(&displayDriver, &dataSet, &customBoundaries, &style);
}

/* use default boundaries and theme */
void Grafici::clear()
{
	clear(boundaries);
}

/* use default theme */
void Grafici::clear(DisplayBoundaries &displayBoundaries)
{
	Vector bl(0.0, 0.0);
	Vector tr(1.0, 1.0);

	displayDriver.fillRectangle(displayBoundaries.project(bl),
								displayBoundaries.project(tr),
								backgroundColor);
}
