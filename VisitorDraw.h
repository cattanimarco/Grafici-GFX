#ifndef ARDU_DATAVIS_VISITOR_DRAW_H
#define ARDU_DATAVIS_VISITOR_DRAW_H

#include "Visitor.h"
#include "BoundariesLine.h"
#include "BoundariesRectangle.h"
#include "BoundariesCircle.h"
#include "Widget.h"
#include "Driver.h"

class VisitorDraw : public Visitor
{
public:
	VisitorDraw(Driver &driver);
	VisitorDraw(Driver *driver, Data *data);

	void visit(BoundariesLine *const boundaries);
	void visit(BoundariesRectangle *const boundaries);
	void visit(BoundariesCircle *const boundaries);
	void visit(Widget *const widget);

protected:
	// draw functions should be overridden
	void draw(Driver *driver, Data *data, Line *boundaries){};
	void draw(Driver *driver, Data *data, Rectangle *boundaries){};
	void draw(Driver *driver, Data *data, Circle *boundaries){};

	Driver *driver = nullptr;
	Data *data = nullptr;
};

#endif //ARDU_DATAVIS_VISITOR_DRAW_H
