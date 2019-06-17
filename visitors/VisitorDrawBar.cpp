#include "VisitorDrawBar.h"
#include "../colorMaps/EthColorMap.h"

void VisitorDrawBar::visit(Data *data, Boundaries *boundaries)
{
	for (PointIterator it = data->begin(); it != data->end(); ++it)
	{
		Point basePoint = *it;
		Point topPoint = basePoint;

		basePoint.y = 0;

		_driver->drawLine(boundaries->project(basePoint).setColor(ethGradient.getColor(topPoint.y)),
						  boundaries->project(topPoint).setColor(ethGradient.getColor(topPoint.y)));
	}
}
