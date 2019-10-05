#include "Adafruit_GFX.h" // Hardware-specific library
#include <MCUFRIEND_kbv.h>

#include "Grafici.h"
#include "Display.h"

#include "utility/linePlot.h"
#include "utility/DataSetFloat.h"

MCUFRIEND_kbv gfx;

DataSetFloat dataset;
DataSetSpline dataSpline;

float dataArray[5] = { 1, 0, 2, 1, 2 };

void setup(void)
{
	gfx.begin(0x7575);
	gfx.setRotation(1);

	grafici.begin(gfx);

	dataset.begin(dataArray, 1, 5);
	dataSpline.begin(dataset, 100);


	grafici.clear();
	grafici.plot(linePlot, dataSpline);
}

void loop(void)
{
}