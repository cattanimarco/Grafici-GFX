#ifndef ARDU_DATAVIS_WIDGET_H
#define ARDU_DATAVIS_WIDGET_H

#include "Display.h"
#include "Data.h"
#include "Geometry.h"

class Widget
{
  public:

	void draw(Display &display, Data &data, Line boundaries);
	void draw(Display &display, Data &data, Rectangle boundaries);
	void draw(Display &display, Data &data, Circle boundaries);

};

#endif //ARDU_DATAVIS_WIDGET_H
