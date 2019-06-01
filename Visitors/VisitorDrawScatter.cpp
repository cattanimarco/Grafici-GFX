#include "VisitorDrawScatter.h"

void VisitorDrawScatter::visit(Data *data, Style *style,Boundaries boundaries)
{
	for (PointIterator it = data->begin(); it != data->end(); ++it)
	{
		_driver->drawPixel((*it).projectPoint(boundaries));
	}
}

