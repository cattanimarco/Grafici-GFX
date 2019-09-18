#ifndef GRAFICI_GFX_PLOT_BAR_H
#define GRAFICI_GFX_PLOT_BAR_H

#include "../Grafici.h"

void barPlot(DisplayDriver *displayDriver, DataSet *dataSet, DisplayBoundaries *boundaries, ColorTheme *theme)
{
	for (DataPointIterator it = dataSet->beginIt(); it != dataSet->endIt(); ++it)
	{
		DataPoint baseDataPoint = *it;
		DataPoint topDataPoint = baseDataPoint;

		baseDataPoint.y = 0;
		baseDataPoint.x = (baseDataPoint.x * dataSet->size())/(dataSet->size()+1);
		baseDataPoint.x  += (0.05/(dataSet->size()+1));
		topDataPoint.x  = baseDataPoint.x + (0.90/(dataSet->size()+1));

		displayDriver->fillRectangle(boundaries->project(baseDataPoint),
									 boundaries->project(topDataPoint),
									 theme->project(topDataPoint));
	}
}

#endif //GRAFICI_GFX_PLOT_BAR_H
