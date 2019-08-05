#ifndef GRAFICI_GFX_VISITOR_DRAW_LINE_H
#define GRAFICI_GFX_VISITOR_DRAW_LINE_H

#include "../Data.h"
#include "../Display.h"

void linePlot(DisplayDriver *displayDriver, DataSet *dataset, Boundaries *boundaries, ColorScheme *colorScheme)
{

		DataPointIterator it = dataset->beginIt();

	for (DataPoint previous = *(it++); it != dataset->endIt(); previous = *(it++))
	{
		DataPoint actual = *it;
				displayDriver->drawLine(boundaries->project(previous).setColor(colorScheme->getColor(previous.value)),
								boundaries->project(actual).setColor(colorScheme->getColor(actual.value)));
	}

}

#endif //GRAFICI_GFX_VISITOR_DRAW_LINE_H