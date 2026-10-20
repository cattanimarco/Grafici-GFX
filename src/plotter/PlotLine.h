#ifndef GRAFICI_GFX_PLOT_LINE_H
#define GRAFICI_GFX_PLOT_LINE_H

#include "PlotOptions.h"

template <typename Scalar>
inline void plot_line(const DisplayDriverT<Scalar> &display,
               const WindowT<Scalar> &window,
               const ColorMap &colorMap,
               const DataSourceNormT<Scalar> &x,
               const DataSourceNormT<Scalar> &y,
               const DataSourceNormT<Scalar> &c,
               const PlotOptionsT<Scalar> opts = {})
{
	/* in case data sources have different sizes, use the smaller one */
	auto source_size = DataSourceNormT<Scalar>::min_data_source_size(x, y, c);

	for (size_t idx = 1; idx < source_size; ++idx)
	{
		const auto x0 = x[idx - 1], y0 = y[idx - 1], c0 = c[idx - 1];
		const auto x1 = x[idx], y1 = y[idx], c1 = c[idx];
		if (!x0.valid() || !y0.valid() || !c0.valid() ||
		    !x1.valid() || !y1.valid() || !c1.valid()) continue;
		display.draw_line({x0.norm(), y0.norm()}, {x1.norm(), y1.norm()},
		                  colorMap.norm_to_color(c0), colorMap.norm_to_color(c1), window, opts.get_segments());
	}
}

#endif //GRAFICI_GFX_PLOT_LINE_H

/** @}*/