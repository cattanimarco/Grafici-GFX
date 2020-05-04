#ifndef GRAFICI_GFX_PLOTTER_BAR_H
#define GRAFICI_GFX_PLOTTER_BAR_H

#include "../Plotter.h"

namespace Plotter
{

class Bar : public Base
{
  public:
	void plot(const Display &display, const DataSet::Base &data, const Boundary &boundary, const ColorMap &colorMap) const override
	{

		for (auto it = data.begin(); it != data.end(); ++it)
		{
			auto top = *it;
			auto bottom = top;
			bottom.y() = 0.0;

			/* use optional channel to decide thickness */
			auto thickness = (*it).opt();
			auto color = colorMap.project(*it);

			if (0.0 == thickness)
			{
				auto b = boundary.project(bottom);
				auto t = boundary.project(top);
				display.line(b, t, color);
			}
			else
			{
				bottom.x() -= thickness / (data.length() * 2.0);
				top.x() += thickness / (data.length() * 2.0);
				auto b = boundary.project(bottom);
				auto t = boundary.project(top);
				display.fillRect(b, t, color);
			}
		}
	}
};

} // namespace Plotter

#endif //GRAFICI_GFX_PLOTTER_BAR_H
