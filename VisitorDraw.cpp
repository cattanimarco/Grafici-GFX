#include <iostream>
#include "VisitorDraw.h"

VisitorDraw::VisitorDraw(Driver &driver):driver(&driver)
{
}

void VisitorDraw::visit(Data *data)
{
	// in case the boundaries are not provided, use full screen
	Boundaries b;
	b.bl.x = 0;
	b.bl.y = 0;
	b.tr.x = driver->width()-1;
	b.tr.y = driver->height()-1;
	visit(data, b);
}

void VisitorDraw::visit(Data *data, Boundaries boundaries)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

