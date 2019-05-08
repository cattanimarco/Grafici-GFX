#include "WidgetRectangle.h"
#include <iostream>

void WidgetRectangle::accept(VisitorDraw *visitorDraw)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	visitorDraw->visit(data, boundaries);
}
