#ifndef GRAFICI_GFX_PLOTTER_SCATTER_H
#define GRAFICI_GFX_PLOTTER_SCATTER_H

#include "../Plotter.h"

namespace Plotter
{

class Scatter : public Base
{
  public:
	void plot(const Display &display, const DataSets::DataSet &data, const Boundary &boundary, const ColorMap &colorMap) const override
	{
		for (auto it = data.begin(); it != data.end(); it++)
		{
			auto dataPoint = *it;
			auto center = boundary.project(dataPoint);
			/* we need a vector with origin 0,0 to be used as a radius */
			auto radius = boundary.projectAbs(dataPoint.opt()/2.0);
			auto color = colorMap.project(dataPoint);
			display.circle(center, radius, color);
		}
	}
};

}
#endif //GRAFICI_GFX_PLOTTER_SCATTER_H
