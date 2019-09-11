#ifndef GRAFICI_GFX_API_H
#define GRAFICI_GFX_API_H

#include "Data.h"
#include "Display.h"

class Grafici
{
public:
	void begin(Adafruit_GFX &tft, ColorPalette &colorScheme);

	/* use default boundaries and theme */
	void plot(PlotFunction plotFunction, Dataset &dataset);
	/* use default theme */
	void plot(PlotFunction plotFunction, Dataset &dataset, Boundaries &customBoundaries);
	/* use default boundaries */
	void plot(PlotFunction plotFunction, Dataset &dataset, ColorTheme &customSettings);
	/* no default parameters */
	void plot(PlotFunction plotFunction, Dataset &dataset, Boundaries &customBoundaries, ColorTheme &customSettings);

	/* use default boundaries and theme */
	void clear();
	/* use default theme */
	void clear(Boundaries &boundaries);
	/* use default boundaries */
	void clear(ColorTheme &customSettings);
	/* no default parameters */
	void clear(Boundaries &boundaries, ColorTheme &customSettings);

	// TODO select type of boundaries via theme
	Boundaries baseBoundaries(void);

private:
	ColorTheme _theme;
	DisplayDriver _displayDriver;
};

#endif //GRAFICI_GFX_API_H