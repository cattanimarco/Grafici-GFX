#ifndef GRAFICI_GFX_PLOTTER_LINE_H
#define GRAFICI_GFX_PLOTTER_LINE_H

#include "../Plotter.h"

namespace Plotter
{

class Line : public Base
{
  public:
	void plot(const Display &display, const DataSet::Base &data, const Boundary &boundary, const ColorMap &colorMap) const override
	{
		auto it = data.begin();
		for (auto previous = *(it++); it != data.end(); previous = *(it++))
		{
			auto actual = *it;
			auto p1 = boundary.project(previous);
			auto p2 = boundary.project(actual);
			auto c2 = colorMap.project(actual);
			display.line(p1, p2, c2);
		}
	}
};

}
#endif //GRAFICI_GFX_PLOTTER_LINE_H