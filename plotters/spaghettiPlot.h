#ifndef GRAFICI_GFX_PLOT_SPAGHETTI_H
#define GRAFICI_GFX_PLOT_SPAGHETTI_H

#include "../Data.h"
#include "../Display.h"

void spaghettiPlot(DisplayDriver *displayDriver, DataSet *dataSet, DisplayBoundaries *boundaries, ColorTheme *theme)
{
	for (DataPointIterator it = dataSet->beginIt(); it != dataSet->endIt(); ++it)
	{
		DataPoint baseDataPoint = *it;
		DataPoint topDataPoint = baseDataPoint;

		baseDataPoint.y = 0;

		displayDriver->drawLine(boundaries->project(baseDataPoint),
								boundaries->project(topDataPoint),
								theme->project(topDataPoint));
	}
}

#endif //GRAFICI_GFX_PLOT_SPAGHETTI_H
