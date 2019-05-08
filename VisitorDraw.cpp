#include <iostream>

#include "VisitorDraw.h"

VisitorDraw::VisitorDraw()
{
}

void VisitorDraw::visit(Data *data, Line boundaries)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void VisitorDraw::visit(Data *data, Rectangle boundaries)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void VisitorDraw::visit(Data *data, Circle boundaries)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}
