#include "VisitorDrawBar.h"

VisitorDrawBar::VisitorDrawBar(Driver *driver)
{
	this->driver = driver;
}

void VisitorDrawBar::visit(Data *data, Line boundaries)
{
}

void VisitorDrawBar::visit(Data *data, Rectangle boundaries)
{
	Color c = {255, 0, 0};

	for (PointIterator it = data->begin(); it != data->end(); it++)
	{
		Line l;
		l.begin = l.end = *it;
		(l.begin).y = 0;
		driver->drawLine(l, 10, c);
	}
}

void VisitorDrawBar::visit(Data *data, Circle boundaries)
{
}
