#include "VisitorDrawScatter.h"

VisitorDrawScatter::VisitorDrawScatter(Driver *driver)
{
	this->driver = driver;
}

void VisitorDrawScatter::visit(Data *data, Line boundaries)
{
}

void VisitorDrawScatter::visit(Data *data, Rectangle boundaries)
{
	Color c = {255, 0, 0};

	for (PointIterator it = data->begin(); it != data->end(); it++)
	{
		driver->drawPixel(*it, 10, c);
	}
}

void VisitorDrawScatter::visit(Data *data, Circle boundaries)
{
}
