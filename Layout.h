#ifndef ARDU_DATAVIS_LAYOUT_H
#define ARDU_DATAVIS_LAYOUT_H

#include "Geometry.h"
#include "Boundaries.h"

class Layout
{
public:
	virtual void draw(Driver driver, Boundaries boundaries);
	void setWidget(Widget &widget, Data &data, Point position);

private:
	struct WidgetAssociation
	{
		Widget *widget;
		Data *data;
		Boundaries boundaries;
	};
	LinkedList<WidgetAssociation> registeredWidgets;
};

#endif //ARDU_DATAVIS_LAYOUT_H
