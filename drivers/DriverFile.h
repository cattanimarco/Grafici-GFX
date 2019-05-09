#ifndef ARDU_DATAVIS_DRIVER_FILE_H
#define ARDU_DATAVIS_DRIVER_FILE_H

#include "../Driver.h"
#include "../lib/ezdib.h"

class DriverFile : public Driver
{
public:
	DriverFile();
	void drawPixel(Point point, int thickness, Color color);
	void drawLine(Line line, int thickness, Color color);
	void drawCircle(Circle circle, int thickness, Color color);
	void drawRectangle(Rectangle rectangle, int thickness, Color color);
	void fillRectangle(Rectangle rectangle, Color color);
	void fillCircle(Circle circle, Color color);

private:
};

#endif //ARDU_DATAVIS_DRIVER_FILE_H
