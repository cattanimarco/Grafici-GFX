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
		display.fillCircle(boundary.project({ x.mid(), y.mid() }), boundary.projectAbs({ c * x.delta() / 2.0, c * y.delta() / 2.0 }), colorMap.project(c));
	};
};

} // namespace Plotter
#endif //GRAFICI_GFX_PLOTTER_BUBBLEMAP_H
