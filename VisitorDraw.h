#ifndef ARDU_DATAVIS_VISITOR_DRAW_H
#define ARDU_DATAVIS_VISITOR_DRAW_H

#include "Geometry.h"
#include "Driver.h"
#include "Data.h"

class VisitorDraw
{
public:
	void begin(Driver &driver);
	virtual void visit(Data *data, Style *style, Boundaries boundaries) = 0;

protected:
	Driver *_driver;
};

#endif //ARDU_DATAVIS_VISITOR_DRAW_H
