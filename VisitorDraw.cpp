#include "VisitorDraw.h"

void VisitorDraw::visit(BoundariesLine *const boundaries)
{
	if (data != nullptr)
	{
		// only visitors with data associated are allowed
		draw(driver, data, &boundaries->line);
	}
}

void VisitorDraw::visit(BoundariesRectangle *const boundaries)
{
	if (data != nullptr)
	{
		// only visitors with data associated are allowed
		draw(driver, data, &boundaries->rectangle);
	}
}

void VisitorDraw::visit(BoundariesCircle *const boundaries)
{
	if (data != nullptr)
	{
		// only visitors with data associated are allowed
		draw(driver, data, &boundaries->circle);
	}
}

void VisitorDraw::visit(Widget *const widget)
{
	// create a temporary visitor for boundaries enriched with the widget associated data
	VisitorDraw dataEnrichedVisitor(driver, widget->data);

	// visit boundaries with temporary data-enriched visitor
	(widget->boundaries)->accept(&dataEnrichedVisitor);
}