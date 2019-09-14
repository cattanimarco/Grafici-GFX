#ifndef GRAFICI_GFX_PLOT_SCATTER_H
#define GRAFICI_GFX_PLOT_SCATTER_H

#include "../Grafici.h"

void scatterPlot(DisplayDriver *displayDriver, DataSet *dataSet, DisplayBoundaries *boundaries, ColorTheme *theme)
{

	for (DatapointIterator it = dataSet->beginIt(); it != dataSet->endIt(); ++it)
	{
		Datapoint dataPoint = *it;
		displayDriver->drawCircle(boundaries->project(dataPoint), theme->markerSize, theme->project(dataPoint));
	}
}

#endif //GRAFICI_GFX_PLOT_SCATTER_H