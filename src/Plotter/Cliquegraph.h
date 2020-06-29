#ifndef GRAFICI_GFX_PLOTTER_CLIQUEGRAPH_H
#define GRAFICI_GFX_PLOTTER_CLIQUEGRAPH_H

#include "../Plotter.h"

namespace Plotter
{

class Cliquegraph : public Base
{
  public:
	void plot(const Display &display, const DataSets::DataSet &data, const Boundary &boundary, const ColorMap &colorMap) const override
	{
		for (auto it1 = data.begin(); it1+1 != data.end(); it1++)
		{
			for (auto it2 = it1+1; it2 != data.end(); it2++)
			{
				auto data1 = *it1;
				auto data2 = *it2;
				auto p1 = boundary.project(data1);
				auto p2 = boundary.project(data2);
				auto c2 = colorMap.project(data2);
				display.line(p1, p2, c2);
			}
		}
	}
};

} // namespace Plotter
#endif //GRAFICI_GFX_PLOTTER_CLIQUEGRAPH_H
