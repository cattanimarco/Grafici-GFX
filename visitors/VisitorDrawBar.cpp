#include "VisitorDrawBar.h"

void VisitorDrawBar::visit(DataSet *dataset, Boundaries *boundaries)
{
	for (DataPointIterator it = dataset->beginIt(); it != dataset->endIt(); ++it)
	{
		DataPoint baseDataPoint = *it;
		DataPoint topDataPoint = baseDataPoint;

		baseDataPoint.y = 0;

		_driver->drawLine(boundaries->project(baseDataPoint).setColor(topDataPoint.value,_colorScheme->colors,_colorScheme->size),
						  boundaries->project(topDataPoint).setColor(topDataPoint.value,_colorScheme->colors,_colorScheme->size));
	}
}
