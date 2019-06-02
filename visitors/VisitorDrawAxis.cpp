#include "VisitorDrawAxis.h"

void VisitorDrawAxis::visit(Data *data, Style *style, Boundaries boundaries)
{
	//vertical lines
	for (int i = 0; i <= 10; i++)
	{
		Point a(i / 10.0, 0.0);
		Point b(i / 10.0, 1.0);
		_driver->drawLine(a.projectPoint(boundaries), b.projectPoint(boundaries));
	}

	//horizzontal lines
	for (int i = 0; i <= 10; i++)
	{
		Point a(0.0, i / 10.0);
		Point b(1.0, i / 10.0);
		_driver->drawLine(a.projectPoint(boundaries), b.projectPoint(boundaries));
	}
}
