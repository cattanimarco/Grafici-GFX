#ifndef GRAFICI_PLOTTER_H
#define GRAFICI_PLOTTER_H

// #include "Adafruit_GFX.h"
// #include "Arduino.h"
// #include "Data.h"
// #include "Utils.h"

class Plotter
{
  public:
	virtual void plot(const Adafruit_GFX &displayDriver, const DataSet &dataSet, const Boundaries &boundaries, const ColorSet &palette, const ColorSource colorSource) = 0;
};

#endif /* GRAFICI_PLOTTER_H */
