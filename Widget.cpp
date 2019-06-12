#include "Widget.h"

void Widget::begin(Data &data)
{
	_data = &data;
}

void Widget::begin(Data &data, ColorScheme &colors)
{
	_data = &data;
	_colors = &colors;
}

void Widget::accept(VisitorDraw *visitorDraw, Boundaries boundaries)
{
	// use input parameter boundaries
	visitorDraw->visit(_data, _colors, boundaries);
}