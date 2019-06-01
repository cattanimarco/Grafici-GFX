#ifndef ARDU_DATAVIS_WIDGET_H
#define ARDU_DATAVIS_WIDGET_H

#include "Data.h"
#include "VisitorDraw.h"
#include "Style.h"

class Widget
{
public:
	void begin(Data &data);
	void begin(Data &data, Style &style);

	// visitor patttern
	void accept(VisitorDraw *visitor, Boundaries boundaries);

protected:
	Data *_data;
	Style *_style;
};

#endif //ARDU_DATAVIS_WIDGET_H