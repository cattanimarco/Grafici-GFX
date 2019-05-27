#include "DecoratorWidgetBorder.h"

DecoratorWidgetBorder::DecoratorWidgetBorder(Widget &widget) : widget(&widget)
{
}

void DecoratorWidgetBorder::accept(VisitorDraw *visitorDraw, Boundaries boundaries)
{
	boundaries.bl += Pixel(20, 20);
	boundaries.tr -= Pixel(10, 10);

	widget->accept(visitorDraw, boundaries);
}