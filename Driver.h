#ifndef ARDU_DATAVIS_DRIVER_H
#define ARDU_DATAVIS_DRIVER_H

#include "Style.h"
#include "Geometry.h"

class Driver
{
  public:
	virtual void drawPixel(Point point, int thickness, Color color) =0;
	virtual void drawLine(Line line, int thickness, Color color)=0;
	virtual void drawCircle(Circle circle, int thickness, Color color)=0;
	virtual void drawRectangle(Rectangle rectangle, int thickness, Color color)=0;
	virtual void fillRectangle(Rectangle rectangle, Color color)=0;
	virtual void fillCircle(Circle circle, Color color)=0;

};

#endif //ARDU_DATAVIS_DRIVER_H
