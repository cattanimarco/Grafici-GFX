#ifndef ARDU_DATAVIS_WIDGET_H
#define ARDU_DATAVIS_WIDGET_H

#include "Data.h"
#include "VisitorDraw.h"

class Widget
{
public:
	// visitor patttern
	virtual void accept(VisitorDraw *visitor) = 0;

	Data *data;
};

#endif //ARDU_DATAVIS_WIDGET_H