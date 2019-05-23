#ifndef ARDU_DATAVIS_LAYOUT_H
#define ARDU_DATAVIS_LAYOUT_H

#include "Geometry.h"
#include "Widget.h"

class Layout
{
public:
	virtual void draw(Boundaries boundaries);
	void setWidget(Widget *widget, Point position);


};

#endif //ARDU_DATAVIS_LAYOUT_H
