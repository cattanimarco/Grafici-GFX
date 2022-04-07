#ifndef GRAFICI_GFX_PLOTTER_BUBBLEMAP_H
#define GRAFICI_GFX_PLOTTER_BUBBLEMAP_H

#include "Heatmap.h"

namespace Plotter
{

class Bubblemap : public Heatmap
{
  protected:
	void draw_block(const Display &display,
	                const Boundary &boundary,
	                const ColorMap &colorMap,
	                Range<DataNorm> x,
	                Range<DataNorm> y,
	                DataNorm c) const override
	{
		DataNorm u = c * x.delta() / 2.0;
		DataNorm v = c * y.delta() / 2.0;

		display.fillCircle(boundary.project({ x.mid(), y.mid() }), boundary.projectAbs({ u, v }), colorMap.project(c));
	};
};

} // namespace Plotter
#endif //GRAFICI_GFX_PLOTTER_BUBBLEMAP_H
