#ifndef ARDU_DATAVIS_DRIVERGFX_H
#define ARDU_DATAVIS_DRIVERGFX_H

#include "Adafruit_GFX.h"

class DriverGFX : public Driver
{
public:
	DriverGFX();
	void drawPixel(Point point, int thickness, Color color);
	void drawLine(Line line, int thickness, Color color);
	void drawCircle(Circle circle, int thickness, Color color);
	void drawRect(Rectangle rectangle, int thickness, Color color);
	void fillRect(Rectangle rectangle, Color color);
	void fillCircle(Circle circle, Color color);

private:
	Adafruit_GFX tft;
	ufloat16_t colorTo16b(Color color);
};

#endif //ARDU_DATAVIS_DRIVER_H
