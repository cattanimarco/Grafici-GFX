#include "DecoratorWidgetBorder.h"


DecoratorWidgetBorder::DecoratorWidgetBorder(Widget &widget): widget(&widget)
{

}

void DecoratorWidgetBorder::accept(VisitorDraw *visitorDraw)
{
				std::cout << __PRETTY_FUNCTION__ << std::endl;

	// use input parameter boundaries
	widget->accept(visitorDraw);
}

void DecoratorWidgetBorder::accept(VisitorDraw *visitorDraw, Boundaries boundaries)
{
			std::cout << __PRETTY_FUNCTION__ << std::endl;

//std::cout << 
	//boundaries.bl += Pixel(10,10);
	//boundaries.tr -= Pixel(10,10);
	Boundaries b;
	b.bl.x = boundaries.bl.x + 10;
	b.bl.y = boundaries.bl.y + 10;
	b.tr.x = boundaries.tr.x - 10;
	b.tr.y = boundaries.tr.y - 10;
	
	// use input parameter boundaries
	widget->accept(visitorDraw, b);
}