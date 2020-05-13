#ifndef GRAFICI_GFX_PLOTTER_SCATTER_H
#define GRAFICI_GFX_PLOTTER_SCATTER_H

#include "../Plotter.h"

namespace Plotter
{

class Scatter : public Base
{
  public:
	void plot(const Display &display, const DataSet::Base &data, const Boundary &boundary, const ColorMap &colorMap) const override
	{
		for (auto it = data.begin(); it != data.end(); it++)
		{
			auto dataPoint = *it;
			auto center = boundary.project(dataPoint);
			/* we remove the origin from the projection in order to have a vector with origin 0,0 that can be used as a radius */
			auto radius = boundary.project(dataPoint.opt())-boundary.origin();
			auto color = colorMap.project(dataPoint);
			display.circle(center, radius, color);
		}
	}
};

}
#endif //GRAFICI_GFX_PLOTTER_SCATTER_H
