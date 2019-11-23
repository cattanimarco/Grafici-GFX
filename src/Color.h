#ifndef GRAFICI_COLOR_H
#define GRAFICI_COLOR_H

#include "Arduino.h"
#include "Data.h"
#include "Utils.h"

typedef unsigned char ColorCoordinate;

typedef uint16_t ColorGFX;

struct ColorCoordinates
{
	ColorCoordinate red;
	ColorCoordinate green;
	ColorCoordinate blue;
};

class ColorSet
{
  public:
	ColorSet(ColorCoordinates *colors, int size)
	    : colors(colors)
	    , size(size){};
	ColorCoordinates project(DataCoordinate val);
	ColorGFX projectGFX(DataCoordinate val);

  private:
	ColorCoordinates *colors;
	int size;
};

#endif /* GRAFICI_COLOR_H */
