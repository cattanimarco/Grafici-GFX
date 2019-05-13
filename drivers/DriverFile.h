#ifndef ARDU_DATAVIS_DRIVER_FILE_H
#define ARDU_DATAVIS_DRIVER_FILE_H

#include "../Driver.h"
#include "../lib/ezdib.h"

class DriverFile : public Driver
{
public:
	DriverFile(int width, int height, char *filename);
	void drawPixel(Point point, int thickness, Color color);
	void drawLine(Line line, int thickness, Color color);
	void drawCircle(Circle circle, int thickness, Color color);
	void drawRectangle(Rectangle rectangle, int thickness, Color color);
	void fillRectangle(Rectangle rectangle, Color color);
	void fillCircle(Circle circle, Color color);

private:
	int colorTo24b(Color color);

	HEZDIMAGE hDib;
	char *filename;
	int width;
	int height;
};

#endif //ARDU_DATAVIS_DRIVER_FILE_H
