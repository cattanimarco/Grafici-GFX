#include "VisitorDrawLine.h"

void VisitorDrawLine::visit(Dataset *dataset, Boundaries *boundaries)
{
	PointIterator it = dataset->beginIt();

	for (Point previous = *(it++); it != dataset->endIt(); previous = *(it++))
	{
		Point actual = *it;
		_driver->drawLine(boundaries->project(previous).setColor(previous.value,_colorScheme->colors,_colorScheme->size),
						  boundaries->project(actual).setColor(actual.value,_colorScheme->colors,_colorScheme->size));
	}
}
