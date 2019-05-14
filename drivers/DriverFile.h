#ifndef ARDU_DATAVIS_DRIVER_FILE_H
#define ARDU_DATAVIS_DRIVER_FILE_H

#include "../Driver.h"
#include "../lib/ezdib.h"

class DriverFile : public Driver
{
public:
	DriverFile(int width, int height, char *filename);

protected:
	void drawPixel(int x, int y, Color color);
	void drawLine(int x1, int y1, int x2, int y2, Color color);
	void drawCircle(int x, int y, int radius, Color color);
	void fillCircle(int x, int y, int radius, Color color);
	void drawRectangle(int xTopLeft, int yTopLeft, int xBottomRight, int yBottomRight, Color color);
	void fillRectangle(int xTopLeft, int yTopLeft, int xBottomRight, int yBottomRight, Color color);
	
	int width(void);
	int height(void);

private:
	int colorTo24b(Color color);

	HEZDIMAGE _hDib;
	char *_filename;
	int _width;
	int _height;
};

#endif //ARDU_DATAVIS_DRIVER_FILE_H
