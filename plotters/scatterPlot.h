#ifndef GRAFICI_GFX_PLOT_SCATTER_H
#define GRAFICI_GFX_PLOT_SCATTER_H

#include "../Grafici.h"

void scatterPlot(DisplayDriver *displayDriver, DataSet *dataSet, DisplayBoundaries *boundaries, ColorTheme *theme)
{

	for (DataPointIterator it = dataSet->beginIt(); it != dataSet->endIt(); ++it)
	{
		DataPoint dataPoint = *it;
		displayDriver->drawCircle(boundaries->project(dataPoint),
								  0.0001,
								  theme->project(dataPoint));
	}
}

#endif //GRAFICI_GFX_PLOT_SCATTER_H