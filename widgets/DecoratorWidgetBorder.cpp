#include "DecoratorWidgetBorder.h"

void DecoratorWidgetBorder::begin(Widget &widget)
{
	_widget = &widget;
}

void DecoratorWidgetBorder::accept(VisitorDraw *visitorDraw, Boundaries boundaries)
{
	boundaries.bl += Pixel(20, 20);
	boundaries.tr -= Pixel(20, 20);

	_widget->accept(visitorDraw, boundaries);
}