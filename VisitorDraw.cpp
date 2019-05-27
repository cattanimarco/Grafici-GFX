#include <iostream>
#include "VisitorDraw.h"

VisitorDraw::VisitorDraw(Driver &driver):driver(&driver)
{
}

void VisitorDraw::visit(Data *data, Boundaries boundaries)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

