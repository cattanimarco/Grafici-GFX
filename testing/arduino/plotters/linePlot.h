#ifndef GRAFICI_GFX_VISITOR_DRAW_LINE_H
#define GRAFICI_GFX_VISITOR_DRAW_LINE_H

#include "../Data.h"
#include "../Display.h"

void linePlot(DisplayDriver *displayDriver, Dataset *dataset, Boundaries *boundaries, ColorPalette *colorScheme)
{

		DatapointIterator it = dataset->beginIt();

	for (Datapoint previous = *(it++); it != dataset->endIt(); previous = *(it++))
	{
		Datapoint actual = *it;
				displayDriver->drawLine(boundaries->project(previous).setColor(colorScheme->getColor(previous.z)),
								boundaries->project(actual).setColor(colorScheme->getColor(actual.z)));
	}

}

#endif //GRAFICI_GFX_VISITOR_DRAW_LINE_H