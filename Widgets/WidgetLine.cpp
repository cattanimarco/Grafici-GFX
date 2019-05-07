#include "WidgetLine.h"
#include <iostream>

void WidgetLine::accept(VisitorDraw *visitorDraw)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	visitorDraw->visit(data, lineBoundaries);
}
