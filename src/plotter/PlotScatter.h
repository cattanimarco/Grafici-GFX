/*!
* \file PlotScatter.h
* \author Marco Cattani <m.cattani@icloud.com>
* \version 3.0
* \date 26/02/2022
* \brief 
* \remarks None
* 
* 
* 
*/


#ifndef GRAFICI_GFX_PLOT_SCATTER_H
#define GRAFICI_GFX_PLOT_SCATTER_H

struct PlotScatterOpts
{
  public:
	PlotScatterOpts(String style = "o")
	    : style{ style }
	{
	}
	/* use String for compatibility with the arduino library */
	String style; 
	bool draw_background{true};
    Color background_color{black}; 
};

void plot_scatter(const DisplayDriver &display,
                  const Window &window,
                  const ColorMap &colorMap,
                  const DataSourceNorm &x,
                  const DataSourceNorm &y,
                  const DataSourceNorm &c,
                  const DataSourceNorm &size,
                  const PlotScatterOpts opts = {})
{
	/* in case data sources have different sizes, use the smaller one */
	auto source_size = DataSourceNorm::min_data_source_size(x, y, c);

	for (size_t idx = 0; idx < source_size; ++idx)
	{
		for (size_t idx_style = 0; idx_style < opts.style.length(); ++idx_style)
		{
			char s = opts.style[idx_style];
			if (s == '.')
			{
				display.draw_circle({ x[idx].norm(), y[idx].norm() }, { 0, 0 }, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == 'o')
			{
				display.draw_circle({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == '-' || s == '*' || s == '+')
			{
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 2, 0, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == '|' || s == '*' || s == '+')
			{
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 2, 0.25, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == 'x' || s == '*')
			{
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 2, 0.125, colorMap.norm_to_color(c[idx]), window);
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 2, 0.375, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == 'v')
			{
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 3, 0.25, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == '^')
			{
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 3, 0.75, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == '>')
			{
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 3, 0, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == '<')
			{
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 3, 0.5, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == 's')
			{
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 4, 0.125, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == 'd')
			{
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 4, 0, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == 'p')
			{
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 5, 0.75, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == 'P')
			{
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 5, 0.25, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == 'e')
			{
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 6, 0.5, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == 'E')
			{
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 6, 0.75, colorMap.norm_to_color(c[idx]), window);
			}
		}
	}
}

#endif //GRAFICI_GFX_PLOT_SCATTER_H
