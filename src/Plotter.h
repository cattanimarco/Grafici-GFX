#ifndef GRAFICI_PLOTTER_H
#define GRAFICI_PLOTTER_H

#include "Display.h"
#include "Data.h"
#include "Boundary.h"
#include "Color.h"

class Plotter
{
  public:
	virtual void plot(const Display &display, const DataSet &data, const Boundary &boundary, const ColorMap &colors) const = 0;
};

#endif /* GRAFICI_PLOTTER_H */
