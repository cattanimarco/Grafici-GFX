#include "Widget.h"

void Widget::begin(Dataset &dataset)
{
	_dataset = &dataset;
}

void Widget::accept(VisitorDraw *visitorDraw, Boundaries *boundaries)
{
	// use input parameter boundaries
	visitorDraw->visit(_dataset, boundaries);
}