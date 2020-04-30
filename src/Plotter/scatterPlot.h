#ifndef GRAFICI_GFX_PLOT_SCATTER_H
#define GRAFICI_GFX_PLOT_SCATTER_H

#include "../Grafici.h"

class ScatterPlot : public Plotter
{

  public:
	ScatterPlot()
	{
		markerSize = 0.0001;
	};

	void plot(DisplayDriver *displayDriver, DataSource:: *dataSource, Boundary *boundary, ColorTheme *theme)
	{

		for (DataSource::Iterator it = dataSource->begin(); it != dataSource->end(); ++it)
		{
			DataCoordinates dataPoint = *it;
			displayDriver->drawCircle(boundary->project(dataPoint),
			                          markerSize,
			                          theme->project(dataPoint));
		}
	}

	float markerSize;
};

// Declare default plotter object
ScatterPlot scatterPlot;

#endif //GRAFICI_GFX_PLOT_SCATTER_H