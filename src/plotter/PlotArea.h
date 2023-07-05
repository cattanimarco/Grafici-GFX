#ifndef GRAFICI_GFX_PLOT_AREA_H
#define GRAFICI_GFX_PLOT_AREA_H

#include "PlotOptions.h"

inline void plot_area(const DisplayDriver &display,
               const Window &window,
               const ColorMap &colorMap,
               const DataSourceNorm &x,
               const DataSourceNorm &y,
               const DataSourceNorm &c,
               const PlotOptions opts = {})
{
	/* in case data sources have different sizes, use the smaller one */
	auto source_size = DataSourceNorm::min_data_source_size(x, y, c);

	for (size_t idx = 1; idx < source_size; ++idx)
	{
        display.fill_rect({ x[idx - 1].norm(), 0 }, { x[idx].norm(), 0 }, { x[idx - 1].norm(), y[idx - 1].norm() }, { x[idx].norm(), y[idx].norm() }, colorMap.norm_to_color(c[idx - 1]), window, opts.get_segments());
	}
}

#endif //GRAFICI_GFX_PLOT_AREA_H

/** @}*/