#include "Widget.h"


Widget::Widget(Data &data): data(&data)
{

}

void Widget::accept(VisitorDraw *visitorDraw)
{
				std::cout << __PRETTY_FUNCTION__ << std::endl;

	// use input parameter boundaries
	visitorDraw->visit(data);
}

void Widget::accept(VisitorDraw *visitorDraw, Boundaries boundaries)
{
				std::cout << __PRETTY_FUNCTION__ << std::endl;

	// use input parameter boundaries
	visitorDraw->visit(data, boundaries);
}