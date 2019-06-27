#include "VisitorDrawBar.h"

void VisitorDrawBar::visit(Dataset *dataset, Boundaries *boundaries)
{
	for (PointIterator it = dataset->beginIt(); it != dataset->endIt(); ++it)
	{
		Point basePoint = *it;
		Point topPoint = basePoint;

		basePoint.y = 0;

		_driver->drawLine(boundaries->project(basePoint).setColor(topPoint.value,_colorScheme->colors,_colorScheme->size),
						  boundaries->project(topPoint).setColor(topPoint.value,_colorScheme->colors,_colorScheme->size));
	}
}
