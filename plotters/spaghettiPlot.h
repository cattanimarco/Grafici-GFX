#ifndef GRAFICI_GFX_PLOT_SPAGHETTI_H
#define GRAFICI_GFX_PLOT_SPAGHETTI_H

#include "../Data.h"
#include "../Display.h"

void spaghettiPlot(DisplayDriver *displayDriver, Dataset *dataset, Boundaries *boundaries, ColorTheme *theme)
{
	for (DatapointIterator it = dataset->beginIt(); it != dataset->endIt(); ++it)
	{
		Datapoint baseDatapoint = *it;
		Datapoint topDatapoint = baseDatapoint;

		baseDatapoint.y = 0;

		displayDriver->drawLine(boundaries->project(baseDatapoint).setColor(theme->colorScheme->getLineColor(&baseDatapoint, theme)),
								boundaries->project(topDatapoint).setColor(theme->colorScheme->getLineColor(&topDatapoint, theme)));
	}
}

#endif //GRAFICI_GFX_PLOT_SPAGHETTI_H
