#include "WidgetRectangle.h"

WidgetRectangle::WidgetRectangle(Data &data): data(&data)
{
	// by default, use all screen
	boundaries.bottomLeft = {0,0};
	boundaries.bottomRight = {0,1};
	boundaries.topLeft = {1,0};
	boundaries.topRight = {1,1};
}

void WidgetRectangle::accept(VisitorDraw *visitorDraw)
{
	visitorDraw->visit(data, boundaries);
}
