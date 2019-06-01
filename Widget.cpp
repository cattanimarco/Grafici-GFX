#include "Widget.h"

void Widget::begin(Data &data)
{
	_data = &data;
}

void Widget::begin(Data &data, Style &style)
{
	_data = &data;
	_style = &style;
}

void Widget::accept(VisitorDraw *visitorDraw, Boundaries boundaries)
{
	// use input parameter boundaries
	visitorDraw->visit(_data, _style, boundaries);
}