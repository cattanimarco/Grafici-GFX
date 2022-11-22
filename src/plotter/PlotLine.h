/*!
* \file PlotLine.h
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
 
#ifndef GRAFICI_GFX_PLOT_LINE_H
#define GRAFICI_GFX_PLOT_LINE_H

/*! Importation of librairies*/
#include "PlotOptions.h"

class PlotLineOpts : public PlotOptions
{
};

/**
 * @brief Plot a line on the given window
 * 
 * @param display reference to the display driver
 * @param window window on which to plot the line
 * @param colorMap color map to use for drawing the plot line
 * @param x data source for the x axis
 * @param y data source for the y axis
 * @param c data source for the color of the line segments. Note that the final color is a function of colorMap and c
 * @param opts optional line drawing options. There are no options available at the moment
 */
void plot_line(const DisplayDriver &display,
               const Window &window,
               const ColorMap &colorMap,
               const DataSourceNorm &x,
               const DataSourceNorm &y,
               const DataSourceNorm &c,
               const PlotLineOpts opts = {})
{
	/* in case data sources have different sizes, use the smaller one */
	auto source_size = DataSourceNorm::min_data_source_size(x, y, c);

	for (size_t idx = 1; idx < source_size; ++idx)
	{
		display.draw_line({ x[idx - 1].norm(), y[idx - 1].norm() }, { x[idx].norm(), y[idx].norm() }, colorMap.norm_to_color(c[idx - 1]), colorMap.norm_to_color(c[idx]), window, opts.segments);
	}
}

#endif //GRAFICI_GFX_PLOT_LINE_H

/** @}*/