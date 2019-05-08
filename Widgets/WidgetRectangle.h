#ifndef ARDU_DATAVIS_WIDGET_RECTANGLE_H
#define ARDU_DATAVIS_WIDGET_RECTANGLE_H

#include "../Geometry.h"
#include "../Widget.h"

class WidgetRectangle : public Widget
{
public:
		// visitor patttern
	void accept(VisitorDraw *visitor);

	Rectangle boundaries;
};

#endif //ARDU_DATAVIS_WIDGET_RECTANGLE_H