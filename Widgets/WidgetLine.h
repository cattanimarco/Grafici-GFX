#ifndef ARDU_DATAVIS_WIDGET_LINE_H
#define ARDU_DATAVIS_WIDGET_LINE_H

#include "../Geometry.h"
#include "../Widget.h"

class WidgetLine : public Widget
{
public:
		// visitor patttern
	void accept(VisitorDraw *visitor);

	Line lineBoundaries;
};

#endif //ARDU_DATAVIS_WIDGET_LINE_H