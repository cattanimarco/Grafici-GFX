#ifndef GRAFICI_GFX_PLOT_SCATTER_H
#define GRAFICI_GFX_PLOT_SCATTER_H

inline void plot_scatter(const DisplayDriver &display,
                  const Window &window,
                  const ColorMap &colorMap,
                  const DataSourceNorm &x,
                  const DataSourceNorm &y,
                  const DataSourceNorm &c,
                  const DataSourceNorm &size,
                  const PlotOptions opts = {})
{
	/* in case data sources have different sizes, use the smaller one */
	auto source_size = DataSourceNorm::min_data_source_size(x, y, c);

	for (size_t idx = 0; idx < source_size; ++idx)
	{
		for (size_t idx_style = 0; idx_style < opts.get_scatter_style().length(); ++idx_style)
		{
			char s = opts.get_scatter_style()[idx_style];
			if (s == '.')
			{
				// dot
				display.draw_circle({ x[idx].norm(), y[idx].norm() }, { 0, 0 }, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == 'o')
			{
				// circle
				display.draw_circle({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == '-' || s == '*' || s == '+')
			{
				// dash or star or plus
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 2, 0, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == '|' || s == '*' || s == '+')
			{
				// vertical bar or star or plus
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 2, 0.25, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == 'x' || s == '*')
			{
				// cross or star
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 2, 0.125, colorMap.norm_to_color(c[idx]), window);
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 2, 0.375, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == 'v')
			{
				// triangle pointing down
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 3, 0.25, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == '^')
			{
				// triangle pointing up
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 3, 0.75, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == '>')
			{
				// triangle pointing right
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 3, 0, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == '<')
			{
				// triangle pointing left
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 3, 0.5, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == 's')
			{
				// square
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 4, 0.125, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == 'd')
			{
				// diamond
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 4, 0, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == 'p')
			{
				// pentagon 1
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 5, 0.75, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == 'P')
			{
				// pentagon 2
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 5, 0.25, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == 'e')
			{
				// exagon 1
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 6, 0.5, colorMap.norm_to_color(c[idx]), window);
			}
			if (s == 'E')
			{
				// exagon 2
				display.draw_polygon({ x[idx].norm(), y[idx].norm() }, { size[idx].norm(), size[idx].norm() }, 6, 0.75, colorMap.norm_to_color(c[idx]), window);
			}
		}
	}
}

#endif //GRAFICI_GFX_PLOT_SCATTER_H

/** @}*/