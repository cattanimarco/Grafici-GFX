#ifndef GRAFICI_GFX_PLOT_SCATTER_H
#define GRAFICI_GFX_PLOT_SCATTER_H

#include "../Data.h"
#include "../Display.h"

void scatterPlot(DisplayDriver *displayDriver, Dataset *dataset, Boundaries *boundaries, ColorTheme *theme)
{

	for (DatapointIterator it = dataset->beginIt(); it != dataset->endIt(); ++it)
	{
		Datapoint datapoint = *it;
		displayDriver->drawCircle(boundaries->project(datapoint).setColor(theme->colorScheme->getMarkerColor(&datapoint, theme)), theme->markerSize);
	}
}

#endif //GRAFICI_GFX_PLOT_SCATTER_H