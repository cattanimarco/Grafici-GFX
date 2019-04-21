#ifndef ARDU_DATAVIS_VISITOR_DRAW_H
#define ARDU_DATAVIS_VISITOR_DRAW_H


#include "Visitor.h"

class VisitorDraw : public Visitor
{
public:
	//VisitorDraw(Driver,Data);
	//VisitorDraw(Driver);
	void visit(Boundaries * const boundaries);
	//void visit(Boundaries * const boundaries, data);

private:
	// virtual void draw(Driver &driver, Data &data, Line boundaries);
	// virtual void draw(Driver &driver, Data &data, Rectangle boundaries);
	// virtual void draw(Driver &driver, Data &data, Circle boundaries);
	//static driver;
};

#endif //ARDU_DATAVIS_VISITOR_DRAW_H

void VisitorDraw::visit(Boundaries * const boundaries)
{
draw(Driver &driver, Data &data, boundaries);
}