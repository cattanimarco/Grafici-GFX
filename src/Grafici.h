#ifndef GRAFICI_GFX_API_H
#define GRAFICI_GFX_API_H

#include "Arduino.h"
#include "Boundaries.h"
#include "Color.h"
#include "Color_defs.h"
#include "Data.h"
#include "Display.h"
#include "Plotter.h"
#include "Utils.h"

class Grafici
{
  public:
	Grafici(Adafruit_GFX &tft);

	void plot(Plotter &plotter, DataSet &x, DataSet &y, DataSet &z);

	void clear(ColorCoordinates color);

	void useColors(ColorMap &colorSet)
	{
		this->colorSet = &colorSet;
	}

	Boundaries boundaries;

  private:
	Display display;
	ColorMap *colorSet;
};

/* Instance of a Grafici object. Used instead of a singleton patter as it is simpler 
to use this way for arduino users and there can be multiple instances of this object if it is relly needed */
extern Grafici grafici;

#endif //GRAFICI_GFX_API_H