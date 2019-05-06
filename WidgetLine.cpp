#include "WidgetLine.h"

void WidgetLine::accept(VisitorDraw *visitorDraw)
{
	 visitorDraw->visit(data, lineBoundaries); 
}
