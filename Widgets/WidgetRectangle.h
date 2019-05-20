#ifndef ARDU_DATAVIS_WIDGET_RECTANGLE_H
#define ARDU_DATAVIS_WIDGET_RECTANGLE_H

#include "../Geometry.h"
#include "../Widget.h"

class WidgetRectangle : public Widget
{
public:
	WidgetRectangle(Data &data);

	// visitor patttern
	void accept(VisitorDraw *visitor);

	Rectangle boundaries;
	Data *data;
};

#endif //ARDU_DATAVIS_WIDGET_RECTANGLE_H