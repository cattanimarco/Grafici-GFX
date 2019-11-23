#include "Grafici.h"

Grafici grafici;

void Grafici::begin(Adafruit_GFX &tft)
{
	displayDriver.begin(&tft);
	backgroundColor = colorBlack;
}

/* use default boundaries and theme */
void Grafici::plot(Plotter &plotter, DataSet &dataSet)
{
	plot(plotter, dataSet, boundaries);
}

/* use default theme */
void Grafici::plot(Plotter &plotter, DataSet &dataSet, Boundaries &customBoundaries)
{
	(&plotter)->plot(&displayDriver, &dataSet, &customBoundaries, &style);
}

/* use default boundaries and theme */
void Grafici::clear()
{
	clear(boundaries);
}

/* use default theme */
void Grafici::clear(Boundaries &displayBoundaries)
{
	DataCoordinates bl(0.0, 0.0);
	DataCoordinates tr(1.0, 1.0);

	displayDriver.fillRectangle(displayBoundaries.project(bl),
	                            displayBoundaries.project(tr),
	                            backgroundColor);
}
