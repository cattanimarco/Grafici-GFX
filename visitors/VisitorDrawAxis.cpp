#include "VisitorDrawAxis.h"

void VisitorDrawAxis::visit(Data *data, Boundaries *boundaries)
{
	//vertical lines
	for (int i = 0; i <= 10; i++)
	{
		Point a(i / 10.0, 0.0);
		Point b(i / 10.0, 1.0);
		_driver->drawLine(boundaries->project(a).setColor(lineColor).darkerColor(0.8),
						  boundaries->project(b).setColor(lineColor).darkerColor(0.8));
	}

	//horizzontal lines
	for (int i = 0; i <= 10; i++)
	{
		Point a(0.0, i / 10.0);
		Point b(1.0, i / 10.0);
		_driver->drawLine(boundaries->project(a).setColor(lineColor).darkerColor(0.8),
						  boundaries->project(b).setColor(lineColor).darkerColor(0.8));
	}
}
