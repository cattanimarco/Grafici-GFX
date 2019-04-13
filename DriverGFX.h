#ifndef ARDU_DATAVIS_DRIVERGFX_H
#define ARDU_DATAVIS_DRIVERGFX_H

#include "Adafruit_GFX.h"

class DriverGFX : public Driver
{
public:
	void drawPixel(float x, float y, Color color);
	void drawLine(float x0, float y0, float x1, float y1, Color color);
	void drawCircle(float x0, float y0, float r, Color color);
	void drawRect(float x, float y, float w, float h, Color color);
	void fillRect(float x, float y, float w, float h, Color color);
	void fillCircle(float x0, float y0, float r, Color color);


private:
	Adafruit_GFX tft;
	uint16_t colorTo16b(Color color);
};

#endif //ARDU_DATAVIS_DRIVER_H
