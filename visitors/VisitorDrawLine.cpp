#include "VisitorDrawLine.h"

void VisitorDrawLine::visit(Data *data, ColorScheme *colors, Boundaries boundaries)
{
	PointIterator it = data->begin();

	for (Point previous = *(it++); it != data->end(); previous = *(it++))
	{
		Point actual = *it;
		_driver->drawLine(previous.projectPoint(boundaries).setColor(lineColor),
						  actual.projectPoint(boundaries).setColor(lineColor));
	}
}
