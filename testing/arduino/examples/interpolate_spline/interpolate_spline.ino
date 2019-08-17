#include "Adafruit_GFX.h" // Hardware-specific library
#include <MCUFRIEND_kbv.h>

#include "Grafici.h"

#include "drawVisitors/barPlot.h"
#include "drawVisitors/linePlot.h"
#include "dataset/Float.h"
#include "dataset/Spline.h"
#include "colorSchemes/heat.h"

#include "Display.h"

MCUFRIEND_kbv gfx;

float dataArrayValue[11] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2};
float dataArrayY[11] = {0, 2, 2, 2, 2, 6, 5, 10, 10, 10, 9};

Grafici grafici;

DatasetFloat dataset;
DatasetSpline dataSpline;
Boundaries left,right;

void setup(void)
{
	gfx.begin(0x7575);
	gfx.rotate(90);

	grafici.begin(gfx);

	dataset.begin(dataArrayY, dataArrayValue, 11);
	dataSpline.begin(&dataset, 40);

	left = grafici.baseBoundaries();
	left.subBoundaries(1, 2, 0);

	right = grafici.baseBoundaries();
	right.subBoundaries(1, 2, 1);

	grafici.clear(csHeat);

	grafici.plot(barPlot, dataset, csHeat, left);
	grafici.plot(linePlot, dataset, csHeat, left);

	grafici.plot(barPlot, dataSpline, csHeat, right);
	grafici.plot(linePlot, dataSpline, csHeat, right);

}

void loop(void)
{
}