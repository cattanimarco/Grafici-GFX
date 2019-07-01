#include "VisitorDrawScatter.h"

void VisitorDrawScatter::visit(DataSet *dataset, Boundaries *boundaries)
{
	for (DataPointIterator it = dataset->beginIt(); it != dataset->endIt(); ++it)
	{
		_driver->drawPixel(boundaries->project(*it).setColor((*it).value,_colorScheme->colors,_colorScheme->size));
	}
}

