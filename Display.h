#ifndef GRAFICI_DISPLAY_H
#define GRAFICI_DISPLAY_H

#include "Arduino.h"
#include "Data.h"
#include "Adafruit_GFX.h"

typedef void (*PlotFunction)(DisplayDriver *displayDriver, DataSource *dataSource, DisplayBoundaries *displayBoundaries, ColorTheme *colorTheme);

class Color
{
public:
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

Color colorBlack = (Color){0, 0, 0};
Color colorRed = (Color){255, 0, 0};
Color colorGreen = (Color){0, 255, 0};
Color colorBlue = (Color){0, 0, 255};

class ColorPalette
{
public:
	ColorPalette(Color *colors, int size) : colors(colors), size(size){};
	Color getColor(float val);

private:
	Color *colors;
	int size;
};

class ColorTheme
{
public:

	enum class ColorSource
	{
		predefined,
		computeFromX,
		computeFromY,
		computeFromZ,
	};

	ColorTheme(ColorPalette *colorPalette, ColorSource colorSource) : colorPalette(colorPalette), colorSource(colorSource){};

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
	Pixel(int x, int y);

	Pixel &operator+=(const Pixel &b);
	Pixel &operator-=(const Pixel &b);

	int x;
	int y;
};

class DisplayDriver
{
public:
	void begin(Adafruit_GFX *tft);

	void drawPixel(Pixel c, Color color);
	void drawLine(Pixel a, Pixel b, Color color);
	void drawCircle(Pixel c, int r, Color color);
	void drawTriangle(Pixel a, Pixel b, Pixel c, Color color);
	void drawRectangle(Pixel bl, int w, int h, Color color);
	void drawRectangle(Pixel bl, Pixel tr, Color color);
	void drawRoundRectangle(Pixel bl, int w, int h, int r, Color color);

	void fillRectangle(Pixel bl, int w, int h, Color color);
	void fillRectangle(Pixel bl, Pixel tr, Color color);

	void fillCircle(Pixel c, int r, Color color);
	void fillTriangle(Pixel a, Pixel b, Pixel c, Color color);
	void fillRoundRectangle(Pixel bl, int w, int h, int r, Color color);

	void fillScreen(Color color);

	int width(void);
	int height(void);

private:
	Adafruit_GFX *_tft;
	int colorTo16b(Color color);
};

class DisplayBoundaries
{
public:
	virtual void begin();

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
	virtual Pixel project(DataPoint &dataPoint,DisplayDriver &displayDriver);

protected:
	DataPoint bottomLeft;
	DataPoint topRight;
};

class RoundDisplayBoundaries : public DisplayBoundaries
{
public:
	void begin();

	void applyBorder(float top, float bottom, float left, float right);
	void reset(void);
	void subBoundaries(int rows, int columns, int index);
	void subBoundariesRadial(int rows, int columns, int index);
	void horizzontalFlip(void);
	void verticalFlip(void);
	void horizzontalFlipRadial(void);
	void verticalFlipRadial(void);
	//void rotateRadial(float value);

	Pixel project(DataPoint dataPoint,DisplayDriver &displayDriver);

private:
	void update(void);

	DataPoint center;
	float innerRadius;
	float outerRadius;
	float beginAngle;
	float endAngle;
};

#endif //GRAFICI_DISPLAY_H
