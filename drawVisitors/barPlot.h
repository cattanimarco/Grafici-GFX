#ifndef GRAFICI_GFX_VISITOR_DRAW_BAR_H
#define GRAFICI_GFX_VISITOR_DRAW_BAR_H

#include "../Data.h"
#include "../Display.h"

void barPlot(DisplayDriver *displayDriver, DataSet *dataset, Boundaries *boundaries, ColorScheme *colorScheme)
{
	for (DataPointIterator it = dataset->beginIt(); it != dataset->endIt(); ++it)
	{
		DataPoint baseDataPoint = *it;
		DataPoint topDataPoint = baseDataPoint;

		baseDataPoint.y = 0;

		displayDriver->drawLine(boundaries->project(baseDataPoint).setColor(colorScheme->getColor(topDataPoint.value)),
								boundaries->project(topDataPoint).setColor(colorScheme->getColor(topDataPoint.value)));
	}
}

#endif //GRAFICI_GFX_VISITOR_DRAW_BAR_H
