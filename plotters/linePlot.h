#ifndef GRAFICI_GFX_PLOT_LINE_H
#define GRAFICI_GFX_PLOT_LINE_H

#include "../Data.h"
#include "../Display.h"

void linePlot(DisplayDriver *displayDriver, Dataset *dataset, Boundaries *boundaries, ColorTheme *theme)
{

		DatapointIterator it = dataset->beginIt();

	for (Datapoint previous = *(it++); it != dataset->endIt(); previous = *(it++))
	{
		Datapoint actual = *it;
				displayDriver->drawLine(boundaries->project(previous).setColor(theme->colorScheme->getMarkerColor(&previous, theme)),
								boundaries->project(actual).setColor(theme->colorScheme->getMarkerColor(&actual, theme)));
	}

}

#endif //GRAFICI_GFX_PLOT_LINE_H