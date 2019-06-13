#ifndef ARDU_DATAVIS_WIDGET_H
#define ARDU_DATAVIS_WIDGET_H

#include "Data.h"
#include "VisitorDraw.h"
#include "Colors.h"

class Widget
{
public:
	void begin(Data &data);

	// visitor patttern
	void accept(VisitorDraw *visitor, Boundaries *boundaries);

protected:
	Data *_data;
};

#endif //ARDU_DATAVIS_WIDGET_H