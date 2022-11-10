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


#ifndef GRAFICI_GFX_PLOT_BAR_H
#define GRAFICI_GFX_PLOT_BAR_H

/*! Importation of librairies*/
#include "PlotOptions.h"

/**
 * @brief Bar plot options 
 * 
 */
class PlotBarOpts : public PlotOptions
{
  public:
	float thickness{ 0.8 }; //< relative thickness of the bar. A thickness of 1.0 will produce a bar that is 1/length(x) wide. A thickness of 0.0 will produce a bar that is 1-pixel wide 
	bool fill_bars{ false }; //< when false, only draw the bar border. When true, fill the bars with color 
};

/**
 * @brief Plot bars on the given window
 * 
 * @param display reference to the display driver
 * @param window window on which to plot the bars
 * @param colorMap color map to use for drawing the plot bars
 * @param x data source for the x axis
 * @param y data source for the y axis
 * @param c data source for the color of the bars. Note that the final color is a function of colorMap and c
 * @param opts optional bar plot options 
 */
void plot_bar(const DisplayDriver &display,
              const Window &window,
              const ColorMap &colorMap,
              const DataSourceNorm &x,
              const DataSourceNorm &y,
              const DataSourceNorm &c,
              const PlotBarOpts opts = {})
{
	/* in case data sources have different sizes, use the smaller one */
	auto source_size = DataSourceNorm::min_data_source_size(x, y, c);

	for (size_t idx = 0; idx < source_size; ++idx)
	{
		if (opts.thickness == 0)
		{
			display.draw_line({ x[idx].norm(), 0 }, { x[idx].norm(), y[idx].norm() }, colorMap.norm_to_color(c[idx]), colorMap.norm_to_color(c[idx]), window, opts.segments);
		}
		else if (opts.fill_bars)
		{
			display.fill_rect({ x[idx].norm() - (opts.thickness / (source_size * 2)), 0 }, { x[idx].norm() + (opts.thickness / (source_size * 2)), y[idx].norm() }, colorMap.norm_to_color(c[idx]), window, opts.segments);
		}
		else
		{
			display.draw_rect({ x[idx].norm() - (opts.thickness / (source_size * 2)), 0 }, { x[idx].norm() + (opts.thickness / (source_size * 2)), y[idx].norm() }, colorMap.norm_to_color(c[idx]), window, opts.segments);
		}
	}
}

#endif //GRAFICI_GFX_PLOT_BAR_H
