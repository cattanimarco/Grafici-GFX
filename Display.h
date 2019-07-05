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

	virtual void begin(DisplayDriver &driver) = 0;

	// getter functions
	virtual float getWidth(void) = 0;
	virtual float getHeight(void) = 0;
	virtual Pixel getCenter(void) = 0;

	//transformation function
	virtual void applyBorder(int top, int bottom, int left, int right) = 0;
	virtual void reset(void) = 0;
	virtual void horizzontalFraction(int sections, int index) = 0;
	virtual void verticalFraction(int sections, int index) = 0;
	virtual void horizzontalFlip(void) = 0;
	virtual void verticalFlip(void) = 0;

	// projection function(s)
	virtual Pixel project(DataPoint point) = 0;
};

class RectangularBoundaries : public Boundaries
{
public:
	void begin(DisplayDriver &driver);
	void applyBorder(int top, int bottom, int left, int right);
	void reset(void);
	void horizzontalFraction(int sections, int index);
	void verticalFraction(int sections, int index);
	void horizzontalFlip(void);
	void verticalFlip(void);
	float getWidth(void);
	float getHeight(void);
	Pixel getCenter(void);

	Pixel project(DataPoint point);

protected:
	Pixel bottomLeft;
	Pixel topRight;
	DisplayDriver *_driver;
};

class RoundBoundaries : public Boundaries
{
public:
	void begin(DisplayDriver &driver);
	void applyBorder(int top, int bottom, int left, int right);
	void reset(void);
	void horizzontalFraction(int sections, int index);
	void verticalFraction(int sections, int index);
	void horizzontalFlip(void);
	void verticalFlip(void);
	float getWidth(void);
	float getHeight(void);
	Pixel getCenter(void);
	Pixel project(DataPoint point);

	RectangularBoundaries enclosingBoundaries;

private:
	void update(void);

	Pixel center;
	float innerRadius;
	float outerRadius;
	float beginAngle;
	float endAngle;
};

#endif //GRAFICI_DISPLAY_H
