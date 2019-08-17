#ifndef GRAFICI_GFX_API_H
#define GRAFICI_GFX_API_H

#include "Data.h"
#include "Display.h"

typedef void (*PlotFunction)(DisplayDriver *displayDriver, Dataset *dataset, Boundaries *boundaries, ColorScheme *colorScheme);

class Grafici
{
public:
	void begin(Adafruit_GFX &tft);

	// visitor pattern
	// TODO add default value for boundaries
	void plot(PlotFunction plotFunction, Dataset &dataset, ColorScheme &colorScheme);
	void plot(PlotFunction plotFunction, Dataset &dataset, ColorScheme &colorScheme, Boundaries &boundaries);

	void clear(ColorScheme &colorScheme);
	void clear(ColorScheme &colorScheme, Boundaries &boundaries);

Boundaries baseBoundaries(void);

private:
	DisplayDriver _displayDriver;


};

#endif //GRAFICI_GFX_API_H