#include "Adafruit_GFX.h" // Hardware-specific library
#include <MCUFRIEND_kbv.h>

#include "Grafici.h"
#include "Display.h"

#include "utility/linePlot.h"
#include "utility/DataSetFloat.h"
#include "utility/DataSetSpline.h"
#include "utility/DataSetHistogram.h"

MCUFRIEND_kbv gfx;

DataSetFloat dataset;
DataSetSpline dataSpline;
DataSetHistogram dataHist;

float dataArray[5] = { 1, 0, 2, 2, 1 };

void setup(void)
{
	gfx.begin(0x7575);
	gfx.setRotation(1);

	grafici.begin(gfx);

	dataset.begin(dataArray, 1, 5); // load array of 5 floats
	dataSpline.begin(dataset, 100); // interpolate 5 dataPoints to 100 dataPoints
	dataHist.begin(dataSpline, 30); // create a new dataset with a 30-bucket histogram of the interpolated dataset

	grafici.clear();
	grafici.plot(barPlot, dataHist); // plot histogram using a bar plot
}

void loop(void)
{
}