#ifndef GRAFICI_GFX_PLOT_LINE_H
#define GRAFICI_GFX_PLOT_LINE_H

#include "../Grafici.h"

void linePlot(DisplayDriver *displayDriver, DataSet *dataSet, DisplayBoundaries *boundaries, ColorTheme *theme)
{

	DatapointIterator it = dataSet->beginIt();

	for (Datapoint previous = *(it++); it != dataSet->endIt(); previous = *(it++))
	{
		Datapoint actual = *it;
		displayDriver->drawLine(boundaries->project(previous, displayDriver), boundaries->project(actual, displayDriver), theme->project(actual));
	}
}

#endif //GRAFICI_GFX_PLOT_LINE_H