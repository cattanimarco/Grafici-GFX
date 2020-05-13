#include "Adafruit_GFX.h" // Hardware-specific library
#include <MCUFRIEND_kbv.h>

#include "Display.h"
#include "Grafici.h"

#include "modules/DataSource::Float.h"
#include "modules/DataSource::Spline.h"
#include "modules/Line.h"
#include "modules/scatterPlot.h"

MCUFRIEND_kbv gfx;

DataSource::Float dataset;
DataSource::Spline dataSpline;

float dataArray[5] = { 1, 0, 2, 1, 2 };

void setup(void)
{
	gfx.begin(0x7575);
	gfx.setRotation(1);

	grafici.begin(gfx);

	dataset.begin(dataArray, 1, 5);  // load array of 5 floats
	dataSpline.begin(dataset, 100);  // interpolate 5 dataPoints to 100 dataPoints
	scatterPlot.markerSize = 0.0002; // this is defined a proportion of the area of the plot

	grafici.clear();
	grafici.boundary.fullScreen().crop(0.04, 0.04, 0.04, 0.04); // add empty border
	grafici.plot(Line, dataSpline);
	// keep the same boundary and plot a second time
	grafici.plot(scatterPlot, dataSpline);
}

void loop(void)
{
}
