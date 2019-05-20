#include "WidgetRectangle.h"
#include <iostream>

WidgetRectangle::WidgetRectangle(Data &data): data(&data)
{
	boundaries.bottomLeft = {0,0};
	boundaries.bottomRight = {0,1};
	boundaries.topLeft = {1,0};
	boundaries.topRight = {1,1};
}

void WidgetRectangle::accept(VisitorDraw *visitorDraw)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	visitorDraw->visit(data, boundaries);
}
