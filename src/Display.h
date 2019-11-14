#ifndef GRAFICI_DISPLAY_H
#define GRAFICI_DISPLAY_H

#include "Adafruit_GFX.h"
#include "Arduino.h"
#include "Data.h"
#include "Macros.h"

class Color
{
  public:
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

extern Color colorBlack;
extern Color colorDarkGray;
extern Color colorLightGray;
extern Color colorWhite;

class ColorPalette
{
  public:
	ColorPalette(Color *colors, int size)
	    : colors(colors)
	    , size(size){};
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
	ColorTheme(); 

	Color project(Vector &dataPoint);
	Color getColor(float val);
	void setPalette(ColorPalette &colorPalette){this->colorPalette = &colorPalette;};

	ColorPalette *colorPalette;
	ColorSource colorSource;
};

struct Pixel
{
  public:
	Pixel(void);
	Pixel(float x, float y);
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

	virtual DisplayBoundaries &reset(void);
	virtual DisplayBoundaries &set(	Vector bottomLeft, Vector topRight);

	//transformation function
	virtual DisplayBoundaries &addBorder(float top, float bottom, float left, float right);
	virtual DisplayBoundaries &crop(int rows, int columns, int index);
	virtual DisplayBoundaries &horizzontalFlip(void);
	virtual DisplayBoundaries &verticalFlip(void);

	// getter functions
	float width(void);
	float height(void);
	Vector getCenter(void);

	// projection function(s)
	virtual Pixel project(Vector &dataPoint);

  protected:
	Vector bottomLeft;
	Vector topRight;
};

class RoundDisplayBoundaries : public DisplayBoundaries
{
  public:
	RoundDisplayBoundaries();

	DisplayBoundaries &reset(void);
	DisplayBoundaries &set(	Vector bottomLeft, Vector topRight);

	DisplayBoundaries &addBorder(float top, float bottom, float left, float right);
	DisplayBoundaries &addBorderRadial(float top, float bottom, float left, float right);
	DisplayBoundaries &crop(int rows, int columns, int index);
	DisplayBoundaries &cropRadial(int rows, int columns, int index);
	DisplayBoundaries &horizzontalFlip(void);
	DisplayBoundaries &verticalFlip(void);
	DisplayBoundaries &horizzontalFlipRadial(void);
	DisplayBoundaries &verticalFlipRadial(void);
	//void rotateRadial(float value);

	Pixel project(Vector &dataPoint);

  private:

	Vector center;
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
