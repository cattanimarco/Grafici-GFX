#ifndef GRAFICI_PLOTTER_H
#define GRAFICI_PLOTTER_H

#include "Arduino.h"
#include "Boundaries.h"
#include "Color.h"
#include "Data.h"
#include "Display.h"

class Plotter
{
  public:
	virtual void plot(const DataSource &dataX, const DataSource &dataY, const DataSource &dataZ, const DataSource &dataColor) const = 0;

	void plot(const DataSource &dataX, const DataSource &dataY, const DataSource &dataZ)
	{
		plot(dataX, dataY, dataZ, dataZ);
	};

	void clear()
	{
		auto bl = grafici.project(boundaries.project(0, 0));
		auto tr = grafici.project(boundaries.project(1, 1));
		auto delta = tr - bl;
		grafici.gfx().fillRect(bl.x, bl.y, delta.x, delta.y, colorToGFX(colorBlack));
	}

	Boundaries boundaries;
	ColorMap &colorMap;
};

#endif /* GRAFICI_PLOTTER_H */
