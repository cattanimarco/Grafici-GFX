#ifndef ARDU_DATAVIS_VISITOR_H
#define ARDU_DATAVIS_VISITOR_H

#include "BoundariesLine.h"
#include "BoundariesRectangle.h"
#include "BoundariesCircle.h"
#include "Widget.h"

class Visitor
{
public:
Visitor(void);

	void visit(Widget *const widget);

	void visit(BoundariesLine *const boundaries);
	void visit(BoundariesRectangle *const boundaries);
	void visit(BoundariesCircle *const boundaries);
};

#endif //ARDU_DATAVIS_VISITOR_H
