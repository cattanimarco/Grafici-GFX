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

	const float thickness = opts.get_thickness();
	if (!isfinite(thickness) || thickness < 0 || source_size == 0) return;
	const float half_width = thickness / (static_cast<float>(source_size) * 2.0f);

	for (size_t idx = 0; idx < source_size; ++idx)
	{
		const auto vx = x[idx], vy = y[idx], vc = c[idx];
		if (!vx.valid() || !vy.valid() || !vc.valid()) continue;
		if (opts.get_thickness() == 0)
		{
			display.draw_line({ vx.norm(), 0 }, { vx.norm(), vy.norm() }, colorMap.norm_to_color(vc), colorMap.norm_to_color(vc), window, opts.get_segments());
		}
		else if (opts.is_bar_filled())
		{
			display.fill_rect({ vx.norm() - half_width, 0 }, { vx.norm() + half_width, vy.norm() }, colorMap.norm_to_color(vc), window, opts.get_segments());
		}
		else
		{
			display.draw_rect({ vx.norm() - half_width, 0 }, { vx.norm() + half_width, vy.norm() }, colorMap.norm_to_color(vc), window, opts.get_segments());
		}
	}
}

#endif //GRAFICI_GFX_PLOT_BAR_H

/** @}*/