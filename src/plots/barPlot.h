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

	void plot(DisplayDriver *displayDriver, DataSet *dataSet, Boundaries *boundaries, ColorTheme *theme)
	{
		for (DataCoordinateIterator it = dataSet->begin(); it != dataSet->end(); ++it)
		{
			DataCoordinates baseDataCoordinates = *it;
			DataCoordinates topDataCoordinates = baseDataCoordinates;

			baseDataCoordinates.y = 0;

			if (0.0 == thickness)
			{
				displayDriver->drawLine(boundaries->project(baseDataCoordinates),
				                        boundaries->project(topDataCoordinates),
				                        theme->project(topDataCoordinates));
			}
			else
			{
				baseDataCoordinates.x = (baseDataCoordinates.x * dataSet->size()) / (dataSet->size() + 1);
				baseDataCoordinates.x += (((1.0 - thickness) / 2.0) / (dataSet->size() + 1));
				topDataCoordinates.x = baseDataCoordinates.x + (thickness / (dataSet->size() + 1));

				displayDriver->fillRectangle(boundaries->project(baseDataCoordinates),
				                             boundaries->project(topDataCoordinates),
				                             theme->project(topDataCoordinates));
			}
		}
	};

	float thickness;
};

// Declare default plotter object
BarPlot barPlot;

#endif //GRAFICI_GFX_PLOT_BAR_H
