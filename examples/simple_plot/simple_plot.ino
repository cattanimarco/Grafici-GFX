#include "Adafruit_GFX.h" // Hardware-specific library
#include <MCUFRIEND_kbv.h>

#include "Grafici.h"

#include "Display.h"

MCUFRIEND_kbv gfx;

DataSource::Float dataset;
float dataArray[5] = { 1, 0, 2, 1, 2 };

void setup(void)
{
	gfx.begin(0x7575);
	gfx.setRotation(1);

	grafici.begin(gfx);

	dataset.begin(dataArray, 1, 5); // load array of 5 floats

	grafici.clear();
	grafici.plot(Line, dataset); // plot dataSource using a simple line
}

void loop(void)
{
}