#ifndef ARDU_DATAVIS_DRIVER_COUT_H
#define ARDU_DATAVIS_DRIVER_COUT_H

#include "../Driver.h"

class DriverCout : public Driver
{
public:
	DriverCout();
	void drawPixel(Point point, int thickness, Color color);
	void drawLine(Line line, int thickness, Color color);
	void drawCircle(Circle circle, int thickness, Color color);
	void drawRect(Rectangle rectangle, int thickness, Color color);
	void fillRect(Rectangle rectangle, Color color);
	void fillCircle(Circle circle, Color color);

private:
};

#endif //ARDU_DATAVIS_DRIVER_COUT_H
