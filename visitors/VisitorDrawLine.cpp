#include "VisitorDrawLine.h"

void VisitorDrawLine::visit(Data *data, Boundaries *boundaries)
{
	PointIterator it = data->begin();

	for (Point previous = *(it++); it != data->end(); previous = *(it++))
	{
		Point actual = *it;
		_driver->drawLine(boundaries->project(previous).setColor(previous.value,_colorScheme->colors,_colorScheme->size),
						  boundaries->project(actual).setColor(actual.value,_colorScheme->colors,_colorScheme->size));
	}
}
