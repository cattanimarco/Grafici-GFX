#include "VisitorDrawScatter.h"

void VisitorDrawScatter::visit(Data *data, Boundaries *boundaries)
{
	for (PointIterator it = data->begin(); it != data->end(); ++it)
	{
		_driver->drawPixel(boundaries->project(*it).setColor((*it).value,_colorScheme->colors,_colorScheme->size));
	}
}

