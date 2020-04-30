#include "Adafruit_GFX.h" // Hardware-specific library
#include <MCUFRIEND_kbv.h>

#include "Grafici.h"
#include "Display.h"

#include "modules/Line.h"
#include "modules/DataSource::Float.h"
#include "modules/DataSource::Spline.h"

MCUFRIEND_kbv gfx;

DataSource::Float dataset;
DataSource::Spline dataSpline;

float dataArray[5] = { 1, 0, 2, 1, 2 };

void setup(void)
{
	gfx.begin(0x7575);
	gfx.setRotation(1);

	grafici.begin(gfx);

	dataset.begin(dataArray, 1, 5); // load array of 5 floats
	dataSpline.begin(dataset, 100); // interpolate 5 dataPoints to 100 dataPoints

	grafici.clear();
	grafici.plot(Line, dataSpline); // plot interpolated dataset using a simple line
}

void loop(void)
{
}