#include "VisitorDrawLine.h"

VisitorDrawLine::VisitorDrawLine(Driver &driver):VisitorDraw(driver)
{
}


void VisitorDrawLine::visit(Data *data, Boundaries boundaries)
{
	PointIterator it = data->begin();
	
	for (Point previous = *(it++); it != data->end(); previous = *(it++))
	{
		Point actual = *it;
		driver->drawLine(previous.projectPoint(boundaries),actual.projectPoint(boundaries));
	}
}

