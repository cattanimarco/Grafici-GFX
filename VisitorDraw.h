#ifndef ARDU_DATAVIS_VISITOR_DRAW_H
#define ARDU_DATAVIS_VISITOR_DRAW_H

#include "Geometry.h"
#include "Driver.h"
#include "Data.h"

class VisitorDraw
{
public:
	VisitorDraw();
	VisitorDraw(Driver *driver);

	virtual void visit(Data *data, Line *boundaries);
	virtual void visit(Data *data, Rectangle *boundaries);
	virtual void visit(Data *data, Circle *boundaries);

	Driver *driver;
};

#endif //ARDU_DATAVIS_VISITOR_DRAW_H
