#include "VisitorDrawLine.h"

void VisitorDrawLine::visit(Data *data, Boundaries *boundaries)
{
	PointIterator it = data->begin();

	for (Point previous = *(it++); it != data->end(); previous = *(it++))
	{
		Point actual = *it;
		_driver->drawLine(boundaries->project(previous).setColor(lineColor),
						  boundaries->project(actual).setColor(lineColor));
	}
}
