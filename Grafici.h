#ifndef GRAFICI_GFX_API_H
#define GRAFICI_GFX_API_H

#include "Data.h"
#include "Display.h"

class Grafici
{
public:
	void begin(Adafruit_GFX &tft, ColorTheme &colorTheme);

	/* use default boundaries and theme */
	void plot(PlotObj *plotObj, DataSet &dataSet);
	/* use default theme */
	void plot(PlotObj *plotObj, DataSet &dataSet, DisplayBoundaries &customBoundaries);
	/* use default boundaries */
	void plot(PlotObj *plotObj, DataSet &dataSet, ColorTheme &customTheme);
	/* no default parameters */
	void plot(PlotObj *plotObj, DataSet &dataSet, DisplayBoundaries &customBoundaries, ColorTheme &customTheme);

	/* use default boundaries and theme */
	void clear();
	/* use default theme */
	void clear(DisplayBoundaries &boundaries);
	/* use default boundaries */
	void clear(ColorTheme &customTheme);
	/* no default parameters */
	void clear(DisplayBoundaries &boundaries, ColorTheme &customTheme);

	// TODO declare lamda function to project space and color to a pixel
	// TODO make functor to pass to plot function?
	//Pixel project(DataPoint dataPoint);

private:
	ColorTheme *colorTheme;
	DisplayDriver displayDriver;
};

#endif //GRAFICI_GFX_API_H