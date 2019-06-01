#include "VisitorDrawBar.h"


void VisitorDrawBar::visit(Data *data, Style *style,Boundaries boundaries)
{
	for (PointIterator it = data->begin(); it != data->end(); ++it)
	{
		Point basePoint = *it;
		Point topPoint = basePoint;

		basePoint.y = 0;

		_driver->drawLine(basePoint.projectPoint(boundaries),topPoint.projectPoint(boundaries));
	}
}

