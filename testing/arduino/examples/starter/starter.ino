#include "Adafruit_GFX.h" // Hardware-specific library
#include <MCUFRIEND_kbv.h>

#include "Grafici.h"

#include "drawVisitors/barPlot.h"
#include "drawVisitors/linePlot.h"
#include "dataset/Float.h"
#include "colorSchemes/heat.h"

#include "Display.h"

MCUFRIEND_kbv gfx;

float dataArrayValue[11] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2};
float dataArrayY[11] = {0, 2, 2, 2, 2, 6, 5, 10, 10, 10, 9};

Grafici grafici;

DatasetFloat dataset;

void setup(void)
{
	gfx.begin(0x7575);

	grafici.begin(gfx);

	// dataset
	dataset.begin(dataArrayY, dataArrayValue, 11);

grafici.clear(&csHeat);
	grafici.plot(barPlot, &dataset, &csHeat);
	grafici.plot(linePlot, &dataset, &csHeat);
}

void loop(void)
{
}