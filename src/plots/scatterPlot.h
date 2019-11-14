#ifndef GRAFICI_GFX_PLOT_SCATTER_H
#define GRAFICI_GFX_PLOT_SCATTER_H

#include "../Grafici.h"

class ScatterPlot : public PlotObj
{

  public:
	ScatterPlot(){markerSize = 0.0001;};

	void plot(DisplayDriver *displayDriver, DataSet *dataSet, DisplayBoundaries *boundaries, ColorTheme *theme)
	{

		for (VectorIterator it = dataSet->beginIt(); it != dataSet->endIt(); ++it)
		{
			Vector dataPoint = *it;
			displayDriver->drawCircle(boundaries->project(dataPoint),
			                          markerSize,
			                          theme->project(dataPoint));
		}
	}

	float markerSize;
};

// Declare default plotter object
ScatterPlot scatterPlot;

#endif //GRAFICI_GFX_PLOT_SCATTER_H