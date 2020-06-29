#ifndef GRAFICI_GFX_PLOTTER_BAR_H
#define GRAFICI_GFX_PLOTTER_BAR_H

#include "../Plotter.h"

namespace Plotter
{

class Bar : public Base
{
  public:
	void plot(const Display &display, const DataSets::DataSet &data, const Boundary &boundary, const ColorMap &colorMap) const override
	{

		for (auto it = data.begin(); it != data.end(); ++it)
		{
			auto tr = *it;
			auto bl = tr;
			bl.y() = 0.0;

			/* use optional channel to decide thickness */
			auto thickness = (*it).opt();
			auto color = colorMap.project(*it);

			if (0.0 == thickness)
			{
				auto b = boundary.project(bl);
				auto t = boundary.project(tr);
				display.line(b, t, color);
			}
			else
			{
				auto br = bl;
				auto tl = tr;
				auto d = thickness / (data.length() * 2.0);
				bl.x() -= d;
				br.x() += d;
				tr.x() += d;
				tl.x() -= d;
				auto b0 = boundary.project(bl);
				auto b1 = boundary.project(br);
				auto t0 = boundary.project(tl);
				auto t1 = boundary.project(tr);
				display.fillRect(b0, b1, t0, t1, color);
			}
		}
	}
};

} // namespace Plotter

#endif //GRAFICI_GFX_PLOTTER_BAR_H
