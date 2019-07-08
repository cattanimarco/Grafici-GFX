#include "VisitorDrawAxis.h"

void VisitorDrawAxis::visit(DataSet *dataset, Boundaries *boundaries)
{
	//vertical lines
	for (int itX = 0; itX <= 10; itX++)
	{
		DataPoint a(itX / 10.0, 0.0);
		DataPoint b(itX / 10.0, 1.0);
		_driver->drawLine(boundaries->project(a).setColor(_colorScheme->lineColor).fadeColor(0.8, _colorScheme->bkgColor),
						  boundaries->project(b).setColor(_colorScheme->lineColor).fadeColor(0.8, _colorScheme->bkgColor));

		//horrizontal sub line
		for (int itY = 0; itY <= 10; itY++)
		{
			if (itX < 10)
			{
				DataPoint a(itX / 10.0, itY / 10.0);
				DataPoint b((itX + 1.0) / 10.0, itY / 10.0);
				_driver->drawLine(boundaries->project(a).setColor(_colorScheme->lineColor).fadeColor(0.8, _colorScheme->bkgColor),
								  boundaries->project(b).setColor(_colorScheme->lineColor).fadeColor(0.8, _colorScheme->bkgColor));
			}
		}
	}
}
