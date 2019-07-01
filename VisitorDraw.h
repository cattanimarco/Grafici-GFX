#ifndef ARDU_DATAVIS_VISITOR_DRAW_H
#define ARDU_DATAVIS_VISITOR_DRAW_H

#include "Display.h"
#include "Display.h"
#include "Data.h"

class VisitorDraw
{
public:
	void begin(DisplayDriver &displayDriver, ColorScheme &colorScheme);
	virtual void visit(DataSet *dataset, Boundaries *boundaries) = 0;

protected:
	DisplayDriver *_driver;
	ColorScheme *_colorScheme;
};

#endif //ARDU_DATAVIS_VISITOR_DRAW_H
