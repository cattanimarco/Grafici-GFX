#ifndef GRAFICI_COLOR_H
#define GRAFICI_COLOR_H

#include "Arduino.h"
#include "Data.h"
#include "Utils.h"

using ColorCoordinate = unsigned char;
using ColorGFX = uint16_t;

template <typename T>
class ColorCoordinates
{
  public:
	ColorCoordinates(T r, T g, T b)
	    : red{ r }
	    , green{ g }
	    , blue{ b }
	{
	}
	T red;
	T green;
	T blue;
};

template <typename C = ColorCoordinate, typename D = DataNorm>
class ColorMap
{
  public:
	ColorMap(const ColorCoordinates<C> *const colors, int size)
	    : colors(colors)
	    , size(size){};
	ColorGFX colorToGFX(ColorCoordinates<C> color) const;
	ColorGFX project(D val) const;

  private:
	ColorCoordinates<C> valueToColor(D val) const;
	const ColorCoordinates *const colors;
	const int size;
};

#endif /* GRAFICI_COLOR_H */
