#include "VisitorDrawLine.h"

void VisitorDrawLine::visit(DataSet *dataset, Boundaries *boundaries)
{
	DataPointIterator it = dataset->beginIt();

	for (DataPoint previous = *(it++); it != dataset->endIt(); previous = *(it++))
	{
		DataPoint actual = *it;
		_driver->drawLine(boundaries->project(previous).setColor(previous.value,_colorScheme->colors,_colorScheme->size),
						  boundaries->project(actual).setColor(actual.value,_colorScheme->colors,_colorScheme->size));
	}
}
