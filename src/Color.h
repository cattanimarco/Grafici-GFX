#ifndef GRAFICI_COLOR_H
#define GRAFICI_COLOR_H

#include "Data.h"
#include "Range.h"
#include "Types.h"
#include "Utils.h"
#include "Vector.h"

class ColorVector
{
  public:
	ColorVector() = default;
	ColorVector(ColorUint8 red, ColorUint8 green, ColorUint8 blue)
	    : _red{ red }
	    , _green{ green }
	    , _blue{ blue }
	{
	}

	const ColorUint8 &red() const
	{
		return _red;
	}
	const ColorUint8 &green() const
	{
		return _green;
	}
	const ColorUint8 &blue() const
	{
		return _blue;
	}
	ColorUint8 &red()
	{
		return _red;
	}
	ColorUint8 &green()
	{
		return _green;
	}
	ColorUint8 &blue()
	{
		return _blue;
	}

	friend ColorVector operator+(const ColorVector &left, const ColorVector &right)
	{
		ColorVector result;
		result.red() = graficiTrim(int(left.red()) + int(right.red()), left._trimRange);
		result.green() = graficiTrim(int(left.green()) + int(right.green()), left._trimRange);
		result.blue() = graficiTrim(int(left.blue()) + int(right.blue()), left._trimRange);
		return result;
	}

	friend ColorVector operator*(const ColorVector &left, const double right)
	{
		ColorVector result;
		result.red() = graficiTrim(int(left.red() * right), left._trimRange);
		result.green() = graficiTrim(int(left.green() * right), left._trimRange);
		result.blue() = graficiTrim(int(left.blue() * right), left._trimRange);
		return result;
	}

	ColorGFX toColorGFX() const
	{
		ColorGFX r = (red() / 255.0) * 31;
		ColorGFX g = (green() / 255.0) * 63;
		ColorGFX b = (blue() / 255.0) * 31;
		return static_cast<ColorGFX>((r << 11) | (g << 5) | (b));
	}

  private:
	ColorUint8 _red;
	ColorUint8 _green;
	ColorUint8 _blue;
	Range<int> _trimRange{ 0, 255 };
};

class ColorMap
{
  public:

	ColorMap() = default;

	ColorMap(const ColorVector *const colors, size_t size)
	    : colors{ colors }
	    , size{ size } {};

	/* from normalized data value to color in Adafruit GFX format (according to the map) */
	ColorGFX project(DataVector<DataNorm> val) const
	{
		return valueToColor(val.c()).toColorGFX();
	}

  private:
	ColorVector valueToColor(DataNorm val) const
	{
		int idx1;               // |-- Our desired color will be between these two indexes in "color".
		int idx2;               // |
		float fractBetween = 0; // Fraction between "idx1" and "idx2" where our value is.

		if (val <= 0)
		{
			idx1 = idx2 = 0;
		} // accounts for an input <=0
		else if (val >= 1)
		{
			idx1 = idx2 = size - 1;
		} // accounts for an input >=0
		else
		{
			val = val * (size - 1);
			idx1 = floor(val);
			idx2 = idx1 + 1;
			fractBetween = val - float(idx1);
		}

		return ColorVector{ static_cast<ColorUint8>( colors[idx2].red() * fractBetween + colors[idx1].red() * (1 - fractBetween)     ),
			                static_cast<ColorUint8>( colors[idx2].green() * fractBetween + colors[idx1].green() * (1 - fractBetween) ),
			                static_cast<ColorUint8>( colors[idx2].blue() * fractBetween + colors[idx1].blue() * (1 - fractBetween)   ) };
	}
	const ColorVector *const colors;
	const size_t size;
};

#endif /* GRAFICI_COLOR_H */
