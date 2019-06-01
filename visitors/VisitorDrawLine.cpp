#include "VisitorDrawLine.h"

void VisitorDrawLine::visit(Data *data, Style *style,Boundaries boundaries)
{
	PointIterator it = data->begin();
	
	for (Point previous = *(it++); it != data->end(); previous = *(it++))
	{
		Point actual = *it;
		_driver->drawLine(previous.projectPoint(boundaries),actual.projectPoint(boundaries));
	}
}

