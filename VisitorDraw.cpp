#include <iostream>
#include "VisitorDraw.h"

VisitorDraw::VisitorDraw(Driver &driver):driver(&driver)
{
}

void VisitorDraw::visit(DataContainer *data, Boundaries boundaries)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

