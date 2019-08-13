#ifndef GRAFICI_GFX_VISITOR_DRAW_BAR_H
#define GRAFICI_GFX_VISITOR_DRAW_BAR_H

#include "../Data.h"
#include "../Display.h"

void barPlot(DisplayDriver *displayDriver, Dataset *dataset, Boundaries *boundaries, ColorScheme *colorScheme)
{
	for (DatapointIterator it = dataset->beginIt(); it != dataset->endIt(); ++it)
	{
		Datapoint baseDatapoint = *it;
		Datapoint topDatapoint = baseDatapoint;

		baseDatapoint.y = 0;

		displayDriver->drawLine(boundaries->project(baseDatapoint).setColor(colorScheme->getColor(topDatapoint.value)),
								boundaries->project(topDatapoint).setColor(colorScheme->getColor(topDatapoint.value)));
	}
}

#endif //GRAFICI_GFX_VISITOR_DRAW_BAR_H
