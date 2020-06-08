#ifndef GRAFICI_GFX_PLOTTER_AXIS_H
#define GRAFICI_GFX_PLOTTER_AXIS_H

#include "../Plotter.h"

namespace Plotter
{

class Axis : public Base
{
  public:
	void plot(const Display &display, const DataSet::Base &data, const Boundary &boundary, const ColorMap &colorMap) const override
	{
		bool firstIter = true;
		auto it = data.begin();
		/* note that we plot each segment separatedly to allows the grid to be deformed by the projection */
		for (auto previous = *(it++); it != data.end(); previous = *(it++))
		{
			auto actual = *it;
			auto innerIt = data.begin();
			for (auto previousInner = *(innerIt++); innerIt != data.end(); previousInner = *(innerIt++))
			{
				auto actualInner = *innerIt;

				/* horizzontal lines */
				auto p1 = boundary.project({ previous.x(), actualInner.y() });
				auto p2 = boundary.project({ actual.x(), actualInner.y() });
				auto c2 = colorMap.project(actual);
				display.line(p1, p2, c2);

				/* vertical lines */
				if (firstIter)
				{
					p1 = boundary.project({ previous.x(), previousInner.y() });
					p2 = boundary.project({ previous.x(), actualInner.y() });
					display.line(p1, p2, c2);
				}
				p1 = boundary.project({ actual.x(), previousInner.y() });
				p2 = boundary.project({ actual.x(), actualInner.y() });
				display.line(p1, p2, c2);
			}
			firstIter = false;
		}
	}
};

} // namespace Plotter

#endif //GRAFICI_GFX_PLOTTER_AXIS_H
