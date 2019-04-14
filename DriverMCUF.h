#ifndef ARDU_DATAVIS_DRIVER_MCUF_H
#define ARDU_DATAVIS_DRIVER_MCUF_H

#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>

class DriverMCUF : public Driver
{
public:
	DriverMCUF();
	void drawPixel(int x, int y, Color color);
	void drawLine(int x0, int y0, int x1, int y1, Color color);
	void drawCircle(int x0, int y0, int r, Color color);
	void drawRect(int x, int y, int w, int h, Color color);
	void fillRect(int x, int y, int w, int h, Color color);
	void fillCircle(int x0, int y0, int r, Color color);
	int width();
	int height();

private:
	MCUFRIEND_kbv tft;
	uint16_t colorTo16b(Color color);
};

#endif //ARDU_DATAVIS_DRIVER_MCUF_H
