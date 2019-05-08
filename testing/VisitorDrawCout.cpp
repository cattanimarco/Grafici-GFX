

#include <iostream>
#include "VisitorDrawCout.h"

VisitorDrawCout::VisitorDrawCout(Driver *driver)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	this->driver = driver;
}

void VisitorDrawCout::visit(Data *data, Line boundaries)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	Color c = {0, 127, 255};
	driver->drawLine(boundaries, 1, c);
}

void VisitorDrawCout::visit(Data *data, Rectangle boundaries)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	Color c = {0, 127, 255};
	driver->drawRectangle(boundaries, 1, c);
}

void VisitorDrawCout::visit(Data *data, Circle boundaries)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}
