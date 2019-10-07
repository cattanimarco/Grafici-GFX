#include "Adafruit_GFX.h" // Hardware-specific library
#include <MCUFRIEND_kbv.h>

#include "Grafici.h"
#include "Display.h"

#include "modules/linePlot.h"
#include "modules/barPlot.h"
#include "modules/DataSetFloat.h"
#include "modules/DataSetSpline.h"
#include "modules/DataSetHistogram.h"

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

	// Divide the screen boundaries in 1 row and 2 columns. Select the sub-boundaries with index 0 (column on left). 
	// Add a border of 4% on top, bottom and left. Add a border of 2% on right
	grafici.boundaries.reset().crop(1, 2, 0).addBorder(0.04, 0.04, 0.04, 0.02);
	grafici.plot(linePlot, dataSpline);

	// Divide the screen boundaries in 1 row and 2 columns. Select the sub-boundaries with index 1 (column on right). 
	// Add a border of 4% on top, bottom and right. Add a border of 2% on left
	grafici.boundaries.reset().crop(1, 2, 1).addBorder(0.04, 0.04, 0.02, 0.04);
	grafici.plot(barPlot, dataHist);
		
}

void loop(void)
{
}