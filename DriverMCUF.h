#ifndef ARDU_DATAVIS_DRIVER_MCUF_H
#define ARDU_DATAVIS_DRIVER_MCUF_H

#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>

class DriverMCUF : public Driver
{
public:
	DriverMCUF();
	void drawPixel(float x, float y, int thickness, Color color);
	void drawLine(float x0, float y0, float x1, float y1, int thickness, Color color);
	void drawCircle(float x0, float y0, float r, int thickness, Color color);
	void drawRect(float x, float y, float w, float h, int thickness, Color color);
	void fillRect(float x, float y, float w, float h, Color color);
	void fillCircle(float x0, float y0, float r, Color color);

private:
	MCUFRIEND_kbv tft;
	ufloat16_t colorTo16b(Color color);
};

#endif //ARDU_DATAVIS_DRIVER_MCUF_H
