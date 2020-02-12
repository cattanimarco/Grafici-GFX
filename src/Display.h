#ifndef GRAFICI_DISPLAY_H
#define GRAFICI_DISPLAY_H

#include "Adafruit_GFX.h"
#include "Color.h"

using DisplayNorm = float;
using DisplayPixel = int;

template <typename T>
class DisplayCoordinates
{
  public:
	T x;
	T y;
};

template <typename T>
DisplayCoordinates<T> operator-(const DisplayCoordinates<T> &left, DisplayCoordinates<T> &right)
{
	return DisplayCoordinates<T>{ left.x - right.x, left.y - right.y };
};

template <typename T>
DisplayCoordinates<T> operator+(const DisplayCoordinates<T> &left, DisplayCoordinates<T> &right)
{
	return DisplayCoordinates<T>{ left.x + right.x, left.y + right.y };
};

class Display
{
  public:
	void begin(Adafruit_GFX &displayDriver)
	{
		this->displayDriver = displayDriver;
	}
	Adafruit_GFX &gfx()
	{
		return displayDriver;
	}
	void clear()
	{
		displayDriver.fillScreen(colorToGFX(colorBlack));
	}

	DisplayCoordinates<DisplayPixel> project(DisplayCoordinates<DisplayNorm> displayCoordinates) const
	{
		return DisplayCoordinates<DisplayPixel>{ displayCoordinates.x * tft->width(),
			                                     (1 - displayCoordinates.y) * tft->height() };
	};

	DisplayCoordinates<DisplayPixel> project(DisplayNorm x, DisplayNorm y) const
	{
		return project(DisplayCoordinates<DisplayNorm>{ x, y });
	};

  private:
	Adafruit_GFX &displayDriver;
};

extern Display grafici;

#endif /* GRAFICI_DISPLAY_H */
