#ifndef ARDU_DATAVIS_VISITOR_DRAW_H
#define ARDU_DATAVIS_VISITOR_DRAW_H

#include "Geometry.h"
#include "Driver.h"
#include "Data.h"

class VisitorDraw
{
public:
	void begin(Driver &driver, ColorScheme &colorScheme);
	virtual void visit(Data *data, Boundaries *boundaries) = 0;

protected:
	Driver *_driver;
	ColorScheme *_colorScheme;
};

#endif //ARDU_DATAVIS_VISITOR_DRAW_H
