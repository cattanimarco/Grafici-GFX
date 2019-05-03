#ifndef ARDU_DATAVIS_WIDGET_H
#define ARDU_DATAVIS_WIDGET_H

#include "Boundaries.h"
#include "Data.h"
#include "Visitor.h"

class Widget
{
public:
	Widget(Data *data, Boundaries *boundaries, Visitor *defaultVisitor) : data(data), boundaries(boundaries), defaultVisitor(defaultVisitor){};
	
	// visitor patttern
	void accept(Visitor *visitor) { visitor->visit(this); };

	Data *data;
	Boundaries *boundaries;
	Visitor *defaultVisitor;
};

#endif //ARDU_DATAVIS_WIDGET_H