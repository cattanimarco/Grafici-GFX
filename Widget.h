#ifndef ARDU_DATAVIS_WIDGET_H
#define ARDU_DATAVIS_WIDGET_H

#include "Data.h"
#include "VisitorDraw.h"

class Widget
{
public:
	Widget(void){};
	Widget(Data &data);
	// visitor patttern
	void accept(VisitorDraw *visitor, Boundaries boundaries);

protected:
	Data *data;
};

#endif //ARDU_DATAVIS_WIDGET_H