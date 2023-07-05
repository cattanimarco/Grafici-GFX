/*!
* \file PlotBar.h
* \author Marco Cattani <m.cattani@icloud.com>
* \version 3.0
* \date 26/02/2022
* \brief 
* \remarks None
* 
* 
* 
*/

/** \addtogroup Plotter
 *  @{
 */
 
#ifndef GRAFICI_GFX_PLOT_BAR_H
#define GRAFICI_GFX_PLOT_BAR_H

#include "PlotOptions.h"

inline void plot_bar(const DisplayDriver &display,
              const Window &window,
              const ColorMap &colorMap,
              const DataSourceNorm &x,
              const DataSourceNorm &y,
              const DataSourceNorm &c,
              const PlotOptions opts = {})
{
	/* in case data sources have different sizes, use the smaller one */
	auto source_size = DataSourceNorm::min_data_source_size(x, y, c);

	for (size_t idx = 0; idx < source_size; ++idx)
	{
		if (opts.get_thickness() == 0)
		{
			display.draw_line({ x[idx].norm(), 0 }, { x[idx].norm(), y[idx].norm() }, colorMap.norm_to_color(c[idx]), colorMap.norm_to_color(c[idx]), window, opts.get_segments());
		}
		else if (opts.is_bar_filled())
		{
			display.fill_rect({ x[idx].norm() - (opts.get_thickness() / (source_size * 2)), 0 }, { x[idx].norm() + (opts.get_thickness() / (source_size * 2)), y[idx].norm() }, colorMap.norm_to_color(c[idx]), window, opts.get_segments());
		}
		else
		{
			display.draw_rect({ x[idx].norm() - (opts.get_thickness() / (source_size * 2)), 0 }, { x[idx].norm() + (opts.get_thickness() / (source_size * 2)), y[idx].norm() }, colorMap.norm_to_color(c[idx]), window, opts.get_segments());
		}
	}
}

#endif //GRAFICI_GFX_PLOT_BAR_H

/** @}*/