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

class ColorMap
{
  public:
	ColorMap(const ColorCoordinates * const colors, int size)
	    : colors(colors)
	    , size(size){};
	ColorCoordinates project(DataCoordinate val) const;
	ColorGFX projectGFX(DataCoordinate val) const;

  private:
	const ColorCoordinates * const colors;
	const int size;
};

#endif /* GRAFICI_COLOR_H */
