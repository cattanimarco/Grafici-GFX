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
		display.draw_line({ x[idx - 1].norm(), y[idx - 1].norm() }, { x[idx].norm(), y[idx].norm() }, colorMap.norm_to_color(c[idx - 1]), colorMap.norm_to_color(c[idx]), window, opts.get_segments());
	}
}

#endif //GRAFICI_GFX_PLOT_LINE_H

/** @}*/