#ifndef GRAFICI_DISPLAY_H
#define GRAFICI_DISPLAY_H

#include <math.h>

#include "Data.h"
#include "Adafruit_GFX.h"

struct Color
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

class ColorScheme
{
public:
	Color *colors;
	int size;
	Color *lineColor;   //white
	Color *markerColor; //red
	Color *fillColor;   //gray
	Color *bkgColor;	//black
};

struct Pixel
{
public:
	Pixel(void);
	Pixel(unsigned int x, unsigned int y);
	Pixel(unsigned int x, unsigned int y, Color color);

	Pixel &setColor(Color *color);
	Pixel &setColor(float value, Color *colors, int size);
	Pixel &fadeColor(float percentage, Color *otherColor);

	Pixel &operator+=(const Pixel &b);
	Pixel &operator-=(const Pixel &b);

	unsigned int x;
	unsigned int y;
	Color color;
};

struct Line
{
	Pixel begin;
	Pixel end;
};

class DisplayDriver
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

private:
	Adafruit_GFX *_tft;
	int colorTo16b(Color color);
};

class Boundaries
{
public:

	virtual void begin(DisplayDriver &driver);
	// transformation functions	
	virtual void applyBorder(int top, int bottom, int left, int right);
	virtual void reset(void);
	// virtual void horizzontalFraction(int sections, int index);
	// virtual void horizzontalMirror(void);
	// virtual void verticalFraction(int sections, int index);
	// virtual void verticalFlip(void);
	// projection function(s)
	virtual Pixel project(DataPoint point);
	
protected:
	Pixel bottomLeft;
	Pixel topRight;
	DisplayDriver *_driver;
};

class RoundBoundaries : public Boundaries
{
public:

	Pixel project(DataPoint point);
	void begin(DisplayDriver &driver);//link to normal boundaries and make this class a decorator? 
	// TODO how to differentiate functions against outer boundaries and functions againg circle boundaries?

private:
	Pixel center;
	float innerRadius;
	float outerRadius;
	float beginAngle;
	float endAngle;
};

#endif //GRAFICI_DISPLAY_H
