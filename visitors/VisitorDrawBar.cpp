#include "VisitorDrawBar.h"

void VisitorDrawBar::visit(Data *data, ColorScheme *colors, Boundaries boundaries)
{
	for (PointIterator it = data->begin(); it != data->end(); ++it)
	{
		Point basePoint = *it;
		Point topPoint = basePoint;

		basePoint.y = 0;

		_driver->drawLine(basePoint.projectPoint(boundaries).setColor(lineColor),
						  topPoint.projectPoint(boundaries).setColor(lineColor));
	}
}
