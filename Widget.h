#ifndef ARDU_DATAVIS_WIDGET_H
#define ARDU_DATAVIS_WIDGET_H

#include "Data.h"
#include "VisitorDraw.h"
#include "Colors.h"

class Widget
{
public:
	void begin(Data &data);
	void begin(Data &data, ColorScheme &colors);

	// visitor patttern
	void accept(VisitorDraw *visitor, Boundaries boundaries);

protected:
	Data *_data;
	ColorScheme *_colors;
};

#endif //ARDU_DATAVIS_WIDGET_H