#include "VisitorDrawBar.h"

void VisitorDrawBar::visit(Data *data, Boundaries *boundaries)
{
	for (PointIterator it = data->begin(); it != data->end(); ++it)
	{
		Point basePoint = *it;
		Point topPoint = basePoint;

		basePoint.y = 0;

		_driver->drawLine(boundaries->project(basePoint).setColor(topPoint.value,_colorScheme->colors,_colorScheme->size),
						  boundaries->project(topPoint).setColor(topPoint.value,_colorScheme->colors,_colorScheme->size));
	}
}
