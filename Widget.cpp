#include "Widget.h"

Widget::Widget(Data &data) : data(&data)
{
}

void Widget::accept(VisitorDraw *visitorDraw, Boundaries boundaries)
{
	// use input parameter boundaries
	visitorDraw->visit(data, boundaries);
}