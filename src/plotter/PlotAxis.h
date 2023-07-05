/*!
* \file PlotAxis.h
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

#ifndef GRAFICI_GFX_PLOT_AXIS_H
#define GRAFICI_GFX_PLOT_AXIS_H

#include "PlotOptions.h"

inline void plot_axis(const DisplayDriver &display,
               const Window &window,
               const PlotOptions &opts)
{
	if (opts.get_h_axis() > 0 || opts.get_v_axis() > 0)
	{
		display.draw_rect({ 0, 0 }, { 1, 1 }, opts.get_axis_color(), window, opts.get_segments());
	}

	if (opts.get_v_axis() > 1)
	{
		Range<size_t> x_range{ 0, opts.get_v_axis() };
		float tick_length = 1;
		for (size_t x_idx = 1; x_idx < opts.get_v_axis(); ++x_idx)
		{
			display.draw_line({ x_range.value_to_norm(x_idx), 0 }, { x_range.value_to_norm(x_idx), tick_length }, opts.get_axis_color(), opts.get_axis_color(), window, opts.get_segments());
		}
	}

	if (opts.get_h_axis() > 1)
	{
		Range<size_t> y_range{ 0, opts.get_h_axis() };
		float tick_length = 1;
		for (size_t y_idx = 1; y_idx < opts.get_h_axis(); ++y_idx)
		{
			display.draw_line({ 0, y_range.value_to_norm(y_idx) }, { tick_length, y_range.value_to_norm(y_idx) }, opts.get_axis_color(), opts.get_axis_color(), window, opts.get_segments());
		}
	}
}

#endif //GRAFICI_GFX_PLOT_AXIS_H

/** @}*/