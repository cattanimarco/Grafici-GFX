#include "Widget.h"

void Widget::begin(Data &data)
{
	_data = &data;
}

void Widget::accept(VisitorDraw *visitorDraw, Boundaries *boundaries)
{
	// use input parameter boundaries
	visitorDraw->visit(_data, boundaries);
}