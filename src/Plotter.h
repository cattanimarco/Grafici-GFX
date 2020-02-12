#ifndef GRAFICI_PLOTTER_H
#define GRAFICI_PLOTTER_H

#include "Arduino.h"
#include "Boundaries.h"
#include "Color.h"
#include "Data.h"
#include "Display.h"

template <typename T = DataNorm>
class Plotter
{
  public:
	virtual void plot(const DataSet<T> &dataSet) const = 0;

	virtual void plot(const DataSource<T> &dataX, const DataSource<T> &dataY, const DataSource<T> &dataZ, const DataSource<T> &dataColor) const
	{
		plot({ dataX, dataY, dataZ, dataColor });
	};

	void plot(const DataSource<T> &dataX, const DataSource<T> &dataY, const DataSource<T> &dataZ)
	{
		plot(dataX, dataY, dataZ, dataZ);
	};

	void clear()
	{
		// auto bl = grafici.project(boundaries.project(0, 0));
		// auto tr = grafici.project(boundaries.project(1, 1));
		// auto delta = tr - bl;
		// grafici.gfx().fillRect(bl.x, bl.y, delta.x, delta.y, colorToGFX(colorBlack));
	}

	Boundaries boundaries;
	ColorMap &colorMap;
};

using DataPlotter = Plotter<DataNorm>;

#endif /* GRAFICI_PLOTTER_H */
