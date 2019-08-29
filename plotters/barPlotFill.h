#ifndef GRAFICI_GFX_PLOT_BAR_FILL_H
#define GRAFICI_GFX_PLOT_BAR_FILL_H

#include "../Data.h"
#include "../Display.h"

void barPlotFill(DisplayDriver *displayDriver, Dataset *dataset, Boundaries *boundaries, ColorScheme *colorScheme)
{
	for (DatapointIterator it = dataset->beginIt(); it != dataset->endIt(); ++it)
	{
		Datapoint baseDatapoint = *it;
		Datapoint topDatapoint = baseDatapoint;

		baseDatapoint.y = 0;
		baseDatapoint.x = (baseDatapoint.x * dataset->size())/(dataset->size()+1);
		baseDatapoint.x  += (0.05/(dataset->size()+1));
		topDatapoint.x  = baseDatapoint.x + (0.90/(dataset->size()+1));

		displayDriver->fillRectangle(boundaries->project(baseDatapoint).setColor(colorScheme->getColor(topDatapoint.value)),
									 boundaries->project(topDatapoint).setColor(colorScheme->getColor(topDatapoint.value)));
	}
}

#endif //GRAFICI_GFX_PLOT_BAR_FILL_H
