#ifndef GRAFICI_PLOTTER_BASE_H
#define GRAFICI_PLOTTER_BASE_H

#include "Display.h"
#include "DataSet.h"
#include "Boundary.h"
#include "Color.h"

namespace Plotter
{

class Base
{
  public:
	virtual void plot(const Display &display, const DataSets::DataSet &data, const Boundary &boundary, const ColorMap &colors) const = 0;
};

}

#endif /* GRAFICI_PLOTTER_BASE_H */
