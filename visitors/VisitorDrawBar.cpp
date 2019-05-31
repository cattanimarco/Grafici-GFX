#include "VisitorDrawBar.h"

VisitorDrawBar::VisitorDrawBar(Driver &driver):VisitorDraw(driver)
{
}


void VisitorDrawBar::visit(Data *data, Boundaries boundaries)
{
	for (PointIterator it = data->begin(); it != data->end(); ++it)
	{
		Point basePoint = *it;
		Point topPoint = basePoint;

		basePoint.y = 0;

		driver->drawLine(basePoint.projectPoint(boundaries),topPoint.projectPoint(boundaries));
	}
}

