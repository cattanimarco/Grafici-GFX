#ifndef ARDU_DATAVIS_DRIVER_H
#define ARDU_DATAVIS_DRIVER_H

#include "Style.h"
#include "Geometry.h"
#include "Adafruit_GFX.h"

class Driver
{
public:
	void begin(Adafruit_GFX *tft);

	void drawPixel(Pixel c);
	void drawLine(Pixel a, Pixel b);
	void drawCircle(Pixel c, int r);
	void drawTriangle(Pixel a, Pixel b, Pixel c);
	void drawRectangle(Pixel bl, int w, int h);
	void drawRectangle(Pixel bl, Pixel tr);
	void drawRoundRectangle(Pixel bl, int w, int h, int r);

	void fillRectangle(Pixel bl, int w, int h);
	void fillCircle(Pixel c, int r);
	void fillTriangle(Pixel a, Pixel b, Pixel c);
	void fillRoundRectangle(Pixel bl, int w, int h, int r);

	void fillScreen(Color c);

	int width(void);
	int height(void);

	Boundaries fullScreen;

private:
	Adafruit_GFX *_tft;
	int colorTo16b(Color color);
};

#endif //ARDU_DATAVIS_DRIVER_H
