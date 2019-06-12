#include "VisitorDrawScatter.h"

void VisitorDrawScatter::visit(Data *data, ColorScheme *colors,Boundaries boundaries)
{
	for (PointIterator it = data->begin(); it != data->end(); ++it)
	{
		_driver->drawPixel((*it).projectPoint(boundaries).setColor(markerColor));
	}
}

