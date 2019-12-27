#ifndef GRAFICI_DISPLAY_H
#define GRAFICI_DISPLAY_H

#include "Adafruit_GFX.h"
#include "Color.h"

typedef float DisplayCoordinate;

struct DisplayCoordinates
{
	DisplayCoordinate x;
	DisplayCoordinate y;
};

typedef int PixelCoordinate;

struct PixelCoordinates
{
	PixelCoordinate x;
	PixelCoordinate y;
};

PixelCoordinates operator-(const PixelCoordinates &left, PixelCoordinates &right)
{
	return PixelCoordinates{ left.x - right.x, left.y - right.y };
};

PixelCoordinates operator+(const PixelCoordinates &left, PixelCoordinates &right)
{
	return PixelCoordinates{ left.x + right.x, left.y + right.y };
};

class Display
{
  public:
	void begin(Adafruit_GFX &tft)
	{
		this->tft = &tft;
	}
	Adafruit_GFX &gfx()
	{
		return *tft;
	}
	void clear()
	{
		gfx().fillScreen(colorToGFX(colorBlack));
	}

	PixelCoordinates project(DisplayCoordinates displayCoordinates) const;
	PixelCoordinates project(DisplayCoordinate x, DisplayCoordinate y) const;

  private:
	Adafruit_GFX *tft;
};

extern Display grafici;

#endif /* GRAFICI_DISPLAY_H */
