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
	const auto sized_count = DataSourceNorm::min_data_source_size(x, y, c, size);
	const auto &styles = opts.get_scatter_style();

	for (size_t idx = 0; idx < source_size; ++idx)
	{
		const auto vx = x[idx], vy = y[idx], vc = c[idx];
		if (!vx.valid() || !vy.valid() || !vc.valid()) continue;
		for (size_t idx_style = 0; idx_style < styles.length(); ++idx_style)
		{
			char s = styles[idx_style];
			// Dots do not consume a radius. Composite styles keep their dots
			// when a shorter radius source has no corresponding sized marker.
			if (s != '.' && idx >= sized_count)
				continue;
			const DataNorm radius = s == '.' ? DataNorm(0) : size[idx];
			if (!radius.valid()) continue;
			if (s == '.')
			{
				// dot
				display.draw_circle({ vx.norm(), vy.norm() }, { 0, 0 }, colorMap.norm_to_color(vc), window);
			}
			if (s == 'o')
			{
				// circle
				display.draw_circle({ vx.norm(), vy.norm() }, { radius.norm(), radius.norm() }, colorMap.norm_to_color(vc), window);
			}
			if (s == '-' || s == '*' || s == '+')
			{
				// dash or star or plus
				display.draw_polygon({ vx.norm(), vy.norm() }, { radius.norm(), radius.norm() }, 2, 0, colorMap.norm_to_color(vc), window);
			}
			if (s == '|' || s == '*' || s == '+')
			{
				// vertical bar or star or plus
				display.draw_polygon({ vx.norm(), vy.norm() }, { radius.norm(), radius.norm() }, 2, 0.25, colorMap.norm_to_color(vc), window);
			}
			if (s == 'x' || s == '*')
			{
				// cross or star
				display.draw_polygon({ vx.norm(), vy.norm() }, { radius.norm(), radius.norm() }, 2, 0.125, colorMap.norm_to_color(vc), window);
				display.draw_polygon({ vx.norm(), vy.norm() }, { radius.norm(), radius.norm() }, 2, 0.375, colorMap.norm_to_color(vc), window);
			}
			if (s == 'v')
			{
				// triangle pointing down
				display.draw_polygon({ vx.norm(), vy.norm() }, { radius.norm(), radius.norm() }, 3, 0.25, colorMap.norm_to_color(vc), window);
			}
			if (s == '^')
			{
				// triangle pointing up
				display.draw_polygon({ vx.norm(), vy.norm() }, { radius.norm(), radius.norm() }, 3, 0.75, colorMap.norm_to_color(vc), window);
			}
			if (s == '>')
			{
				// triangle pointing right
				display.draw_polygon({ vx.norm(), vy.norm() }, { radius.norm(), radius.norm() }, 3, 0, colorMap.norm_to_color(vc), window);
			}
			if (s == '<')
			{
				// triangle pointing left
				display.draw_polygon({ vx.norm(), vy.norm() }, { radius.norm(), radius.norm() }, 3, 0.5, colorMap.norm_to_color(vc), window);
			}
			if (s == 's')
			{
				// square
				display.draw_polygon({ vx.norm(), vy.norm() }, { radius.norm(), radius.norm() }, 4, 0.125, colorMap.norm_to_color(vc), window);
			}
			if (s == 'd')
			{
				// diamond
				display.draw_polygon({ vx.norm(), vy.norm() }, { radius.norm(), radius.norm() }, 4, 0, colorMap.norm_to_color(vc), window);
			}
			if (s == 'p')
			{
				// pentagon 1
				display.draw_polygon({ vx.norm(), vy.norm() }, { radius.norm(), radius.norm() }, 5, 0.75, colorMap.norm_to_color(vc), window);
			}
			if (s == 'P')
			{
				// pentagon 2
				display.draw_polygon({ vx.norm(), vy.norm() }, { radius.norm(), radius.norm() }, 5, 0.25, colorMap.norm_to_color(vc), window);
			}
			if (s == 'e')
			{
				// exagon 1
				display.draw_polygon({ vx.norm(), vy.norm() }, { radius.norm(), radius.norm() }, 6, 0.5, colorMap.norm_to_color(vc), window);
			}
			if (s == 'E')
			{
				// exagon 2
				display.draw_polygon({ vx.norm(), vy.norm() }, { radius.norm(), radius.norm() }, 6, 0.75, colorMap.norm_to_color(vc), window);
			}
		}
	}
}

#endif //GRAFICI_GFX_PLOT_SCATTER_H

/** @}*/