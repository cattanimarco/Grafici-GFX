#ifndef ARDU_DATAVIS_DISPLAY_H
#define ARDU_DATAVIS_DISPLAY_H

#include "Geometry.h"
#include "Driver.h"
#include "Style.h"

class Display
{
public:
	Display(Driver &driver, Style &style);
	void drawPoint(Point point);
	void drawLine(Line line);
	void drawCircle(Circle circle);
	void drawSquare(Rectangle rectangle);
	void fillCircle(Circle area);
	void fillSquare(Rectangle area);

private:
	Driver *driver;
	Style *style;
};

#endif //ARDU_DATAVIS_DISPLAY_H
