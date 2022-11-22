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

enum AxisOptsStyle : char
{
	none = 0,
	h_lines = 0x1 << 1,
	v_lines = 0x1 << 2,
};

struct PlotAxisOpts
{
  public:
	PlotAxisOpts(size_t rows = 10, size_t columns = 10, char style = h_lines | v_lines, Color color = white, size_t segments = 1)
	    : rows{ rows }
	    , columns{ columns }
	    , style{ style }
		, color{ color }
	    , segments{ segments }
	{
	}

	size_t rows;
	size_t columns;
	char style;
	Color color;
	size_t segments; /* use ~45 for polar plots */
};

void plot_axis(const DisplayDriver &display,
               const Window &window,
               PlotAxisOpts opts = {})
{

	if (opts.style != none)
	{
		display.draw_rect({ 0, 0 }, { 1, 1 }, opts.color, window, opts.segments);
	}

	if (opts.style & v_lines)
	{
		Range<size_t> x_range{ 0, opts.columns };
		float tick_length = 1;
		for (size_t x_idx = 1; x_idx < opts.columns; ++x_idx)
		{
			display.draw_line({ x_range.value_to_norm(x_idx), 0 }, { x_range.value_to_norm(x_idx), tick_length }, opts.color, opts.color, window, opts.segments);
		}
	}

	if (opts.style & h_lines)
	{
		Range<size_t> y_range{ 0, opts.rows };
		float tick_length = 1;
		for (size_t y_idx = 1; y_idx < opts.rows; ++y_idx)
		{
			display.draw_line({ 0, y_range.value_to_norm(y_idx) }, { tick_length, y_range.value_to_norm(y_idx) }, opts.color, opts.color, window, opts.segments);
		}
	}
}

#endif //GRAFICI_GFX_PLOT_AXIS_H

/** @}*/