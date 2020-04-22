#ifndef GRAFICI_GFX_PLOT_BAR_H
#define GRAFICI_GFX_PLOT_BAR_H

#include "../Grafici.h"

class BarPlot : public Plotter
{
  public:
	BarPlot()
	{
		thickness = 0.0;
	};

	void plot(DisplayDriver *displayDriver, DataSource *dataSource, Boundary *boundary, ColorTheme *theme)
	{
		for (DataSourceIterator it = dataSource->begin(); it != dataSource->end(); ++it)
		{
			DataCoordinates baseDataCoordinates = *it;
			DataCoordinates topDataCoordinates = baseDataCoordinates;

			baseDataCoordinates.y = 0;

			if (0.0 == thickness)
			{
				displayDriver->drawLine(boundary->project(baseDataCoordinates),
				                        boundary->project(topDataCoordinates),
				                        theme->project(topDataCoordinates));
			}
			else
			{
				baseDataCoordinates.x = (baseDataCoordinates.x * dataSource->size()) / (dataSource->size() + 1);
				baseDataCoordinates.x += (((1.0 - thickness) / 2.0) / (dataSource->size() + 1));
				topDataCoordinates.x = baseDataCoordinates.x + (thickness / (dataSource->size() + 1));

				displayDriver->fillRectangle(boundary->project(baseDataCoordinates),
				                             boundary->project(topDataCoordinates),
				                             theme->project(topDataCoordinates));
			}
		}
	};

	float thickness;
};

// Declare default plotter object
BarPlot barPlot;

#endif //GRAFICI_GFX_PLOT_BAR_H
