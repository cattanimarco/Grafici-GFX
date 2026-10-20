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

template <typename Scalar>
inline void plot_bar(const DisplayDriverT<Scalar> &display,
              const WindowT<Scalar> &window,
              const ColorMap &colorMap,
              const DataSourceNormT<Scalar> &x,
              const DataSourceNormT<Scalar> &y,
              const DataSourceNormT<Scalar> &c,
              const PlotOptionsT<Scalar> opts = {})
{
	/* in case data sources have different sizes, use the smaller one */
	auto source_size = DataSourceNormT<Scalar>::min_data_source_size(x, y, c);
	using Compute = typename grafici::ComputationType<Scalar>::type;
	const Compute thickness = opts.get_thickness();
	if (!grafici::is_finite(thickness) || thickness < 0 || source_size == 0) return;
	const Compute half_width = thickness / (static_cast<Compute>(source_size) * Compute(2));

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