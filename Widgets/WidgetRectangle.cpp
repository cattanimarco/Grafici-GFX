#include "WidgetRectangle.h"

WidgetRectangle::WidgetRectangle(Data &data): Widget(&data)
{
		// by default, use all screen
	boundaries.bottomLeft = (Point){0,0};
	boundaries.bottomRight = (Point){0,1};
	boundaries.topLeft = (Point){1,0};
	boundaries.topRight = (Point){1,1};
}

void WidgetRectangle::accept(VisitorDraw *visitorDraw)
{
	// use object boundaries 
	visitorDraw->visit(data, boundaries);
}

// void WidgetRectangle::accept(VisitorDraw *visitorDraw, Rectangle boundaries)
// {
// 	// use input parameter boundaries
// 	visitorDraw->visit(data, boundaries);
// }