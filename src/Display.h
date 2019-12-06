#ifndef GRAFICI_DISPLAY_H
#define GRAFICI_DISPLAY_H

#include "Adafruit_GFX.h"

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

class Display
{
  public:
	Display(const Adafruit_GFX &tft)
	    : tft(tft){};
	PixelCoordinates project(DisplayCoordinates displayCoordinates) const;
	PixelCoordinates project(DisplayCoordinate x, DisplayCoordinate y) const;

  private:
	const Adafruit_GFX &tft;
};

#endif /* GRAFICI_DISPLAY_H */
