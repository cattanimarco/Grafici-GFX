#include "Adafruit_GFX.h" // Hardware-specific library
#include <MCUFRIEND_kbv.h>

#include "Grafici.h"

#include "plotters/spaghettiPlot.h"
#include "plotters/linePlot.h"
#include "datasets/DatasetFloat.h"
#include "decorators/DatasetInterpolator.h"
#include "decorators/DatasetSpline.h"
#include "color_schemes/heat.h"

#include "Display.h"

MCUFRIEND_kbv gfx;

float dataArrayValue[11] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2};
float dataArrayY[11] = {0, 2, 2, 2, 2, 6, 5, 10, 10, 10, 9};

Grafici grafici;

DatasetFloat dataset;
DatasetSpline dataSpline;
DatasetInterpolator dataInterpolator;
Boundaries left, mid, right;

void setup(void)
{
	gfx.begin(0x7575);
	gfx.setRotation(1);

	grafici.begin(gfx);

	dataset.begin(dataArrayY, dataArrayValue, 11);
	dataInterpolator.begin(&dataset, 50);
	dataSpline.begin(&dataset, 50);

	left = grafici.baseBoundaries();
	left.subBoundaries(1, 3, 0);
	left.applyBorder(10, 10, 10, 5);

	mid = grafici.baseBoundaries();
	mid.subBoundaries(1, 3, 1);
	mid.applyBorder(10, 10, 5, 5);

	right = grafici.baseBoundaries();
	right.subBoundaries(1, 3, 2);
	right.applyBorder(10, 10, 5, 10);

	grafici.clear(csHeat);

	grafici.plot(spaghettiPlot, dataset, csHeat, left);

	grafici.plot(spaghettiPlot, dataInterpolator, csHeat, mid);

	grafici.plot(spaghettiPlot, dataSpline, csHeat, right);
}

void loop(void)
{
}