#ifndef GRAFICI_GFX_API_H
#define GRAFICI_GFX_API_H

#include "Data.h"
#include "Display.h"

typedef void (*PlotFunction)(DisplayDriver *displayDriver, DataSet *dataset, Boundaries *boundaries, ColorScheme *colorScheme);

class Grafici
{
public:
	void begin(Adafruit_GFX &tft);

	// visitor pattern
	// TODO add default value for boundaries
	void plot(PlotFunction plotFunction, DataSet *dataset, ColorScheme *colorScheme, Boundaries *boundaries = NULL);

Boundaries baseBoundaries(void);

private:
	DisplayDriver _displayDriver;


};

#endif //GRAFICI_GFX_API_H