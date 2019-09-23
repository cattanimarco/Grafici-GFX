#ifndef GRAFICI_DISPLAY_H
#define GRAFICI_DISPLAY_H

#include "Arduino.h"
#include "Data.h"
#include "Adafruit_GFX.h"

class Color
{
public:
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

class ColorPalette
{
public:
	ColorPalette(Color *colors, int size) : colors(colors), size(size){};
	Color getColor(float val);

private:
	Color *colors;
	int size;
};
	
	enum ColorSource
	{
		predefined,
		computeFromX,
		computeFromY,
		computeFromZ,
	};

class ColorTheme
{
public:

	ColorTheme(ColorPalette &colorPalette, ColorSource colorSource) : colorPalette(&colorPalette), colorSource(colorSource){};

	Color project(DataPoint &dataPoint);
	Color getColor(float val);

private:
	ColorPalette *colorPalette;
	ColorSource colorSource;
};

struct Pixel
{
public:
	Pixel(void);
	Pixel(float x, float y);

	Pixel &operator+=(const Pixel &b);
	Pixel &operator-=(const Pixel &b);

	float x;
	float y;
};

class DisplayDriver
{
public:
	void begin(Adafruit_GFX *tft);

	void drawPixel(Pixel c, Color color);
	void drawLine(Pixel a, Pixel b, Color color);
	void drawCircle(Pixel c, float area, Color color);
	
	void drawTriangle(Pixel a, Pixel b, Pixel c, Color color);
	void drawRectangle(Pixel bl, float w, float h, Color color);
	void drawRectangle(Pixel bl, Pixel tr, Color color);
	void drawRoundRectangle(Pixel bl, float w, float h, float r, Color color);

	void fillRectangle(Pixel bl, float w, float h, Color color);
	void fillRectangle(Pixel bl, Pixel tr, Color color);

	void fillCircle(Pixel c, float r, Color color);
	void fillTriangle(Pixel a, Pixel b, Pixel c, Color color);
	void fillRoundRectangle(Pixel bl, float w, float h, float r, Color color);

	void fillScreen(Color color);

private:
	Adafruit_GFX *tft;
	int colorTo16b(Color color);
	//int displayWidth(void);
	//int displayHeight(void);
};

class DisplayBoundaries
{
public:
	DisplayBoundaries();

	//transformation function
	virtual void applyBorder(float top, float bottom, float left, float right);
	virtual void reset(void);
	virtual void subBoundaries(int rows, int columns, int index);
	virtual void horizzontalFlip(void);
	virtual void verticalFlip(void);

	// getter functions
	float width(void);
	float height(void);
	DataPoint getCenter(void);

	// projection function(s)
	virtual Pixel project(DataPoint &dataPoint);

protected:
	DataPoint bottomLeft;
	DataPoint topRight;
};

class RoundDisplayBoundaries : public DisplayBoundaries
{
public:
	RoundDisplayBoundaries();

	void applyBorder(float top, float bottom, float left, float right);
	void reset(void);
	void subBoundaries(int rows, int columns, int index);
	void subBoundariesRadial(int rows, int columns, int index);
	void horizzontalFlip(void);
	void verticalFlip(void);
	void horizzontalFlipRadial(void);
	void verticalFlipRadial(void);
	//void rotateRadial(float value);

	Pixel project(DataPoint &dataPoint);

private:
	void update(void);

	DataPoint center;
	float innerRadius;
	float outerRadius;
	float beginAngle;
	float endAngle;
};

class PlotObj
{
public:
PlotObj();

	virtual void plot(DisplayDriver *displayDriver, DataSet *dataSet, DisplayBoundaries *boundaries, ColorTheme *theme);	
};

#endif //GRAFICI_DISPLAY_H
