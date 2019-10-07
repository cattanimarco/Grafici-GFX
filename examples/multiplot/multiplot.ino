#include "Adafruit_GFX.h" // Hardware-specific library
#include <MCUFRIEND_kbv.h>

#include "Grafici.h"
#include "Display.h"

#include "modules/linePlot.h"
#include "modules/scatterPlot.h"
#include "modules/DataSetFloat.h"
#include "modules/DataSetSpline.h"

MCUFRIEND_kbv gfx;

DataSetFloat dataset;
DataSetSpline dataSpline;

float dataArray[5] = { 1, 0, 2, 1, 2 };

void setup(void)
{
	gfx.begin(0x7575);
	gfx.setRotation(1);

	grafici.begin(gfx);

	dataset.begin(dataArray, 1, 5); // load array of 5 floats
	dataSpline.begin(dataset, 100); // interpolate 5 dataPoints to 100 dataPoints
	scatterPlot.markerSize = 0.0002; // this is defined a proportion of the area of the plot

		
	grafici.clear();
	grafici.boundaries.reset().addBorder(0.04, 0.04, 0.04, 0.04); // add empty border
	grafici.plot(linePlot, dataSpline);
	// keep the same boundaries and plot a second time
	grafici.plot(scatterPlot, dataSpline);
}

void loop(void)
{
}