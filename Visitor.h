#ifndef ARDU_DATAVIS_VISITOR_H
#define ARDU_DATAVIS_VISITOR_H

#include "BoundariesLine.h"
#include "BoundariesRectangle.h"
#include "BoundariesCircle.h"
#include "Widget.h"

class Visitor
{
public:
	virtual void visit(Widget *const widget) = 0;

	virtual void visit(BoundariesLine *const boundaries) = 0;
	virtual void visit(BoundariesRectangle *const boundaries) = 0;
	virtual void visit(BoundariesCircle *const boundaries) = 0;
};

#endif //ARDU_DATAVIS_VISITOR_H
