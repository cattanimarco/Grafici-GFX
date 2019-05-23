#include "VisitorDrawScatter.h"

VisitorDrawScatter::VisitorDrawScatter(Driver &driver):VisitorDraw(driver)
{
}


void VisitorDrawScatter::visit(Data *data, Boundaries boundaries)
{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	for (PointIterator it = data->begin(); it != data->end(); it++)
	{
		driver->drawPixel((*it).projectPoint(boundaries));
	}
}

