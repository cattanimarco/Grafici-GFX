#ifndef GRAFICI_GFX_API_H
#define GRAFICI_GFX_API_H

#include "Data.h"
#include "Display.h"
#include "Macros.h"

class Grafici
{
  public:
	void begin(Adafruit_GFX &tft);

	/* use default boundaries and theme */
	void plot(PlotObj &plotObj, DataSet &dataSet);
	/* use default theme */
	void plot(PlotObj &plotObj, DataSet &dataSet, DisplayBoundaries &customBoundaries);

	/* use default boundaries and theme */
	void clear();
	/* use default theme */
	void clear(DisplayBoundaries &boundaries);

	// void setColorPalette(ColorPalette &colorPalette) { colorTheme->colorPalette = &colorPalette;};
	// void setColorSource(const ColorSource &colorSource) {colorTheme->colorSource = colorSource;};

	// TODO declare lamda function to project space and color to a pixel
	// TODO make functor to pass to plot function?
	//Pixel project(DataPoint dataPoint);

	DisplayBoundaries boundaries;
	ColorTheme style;
	Color backgroundColor;

  private:
	DisplayDriver displayDriver;
};

/* Instance of a Grafici object. Used instead of a singleton patter as it is simpler 
to use this way for arduino users and there can be multiple instances of this object if it is relly needed */
extern Grafici grafici;

#endif //GRAFICI_GFX_API_H