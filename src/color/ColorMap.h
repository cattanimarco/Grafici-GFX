/*!
* \file ColorMap.h
* \author Marco Cattani <m.cattani@icloud.com>
* \version 3.0
* \date 26/02/2022
* \brief 
* \remarks None
* 
* 
* 
*/


#ifndef GRAFICI_COLOR_COLORMAP_H
#define GRAFICI_COLOR_COLORMAP_H

/*! Importation of librairies*/
#include "../Range.h"
#include "../data/DataNorm.h"
#include "Color.h"


/**
 * @brief ColorMap interface 
 * 
 */
class ColorMap
{
  public:
	/**
	 * @brief Return an R5G6B5 color according to the Color Map and the given index
	 * 
	 * @param index 
	 * @return R5G6B5 
	 */
	virtual Color index_to_color(size_t index) const = 0;

	/**
	 * @brief Translate a DataNorm object into a R5G6B5 color according to the Color Map
	 * 
	 * @param val 
	 * @return R5G6B5 
	 */
	virtual Color norm_to_color(DataNorm val) const = 0;
};

class ColorMapConstant : public ColorMap
{
  public:
	ColorMapConstant(const Color color)
	    : _color{ color }
	{
	}

	Color index_to_color(size_t /*idx*/) const override
	{
		return _color;
	}

	Color norm_to_color(DataNorm /*val*/) const override
	{
		return _color;
	}

  private:
	const Color _color;
};

/**
 * @brief Color Map Array
 * 
 * @tparam N Size of the Color Map array
 */
template <size_t N>
class ColorMapArray : public ColorMap
{
  public:
	/**
	 * @brief Construct a new Color Map Array object
	 * 
	 * @tparam Color 
	 * @param args 
	 */
	template <typename... T>
	ColorMapArray(T... args)
	    : _colors{ (args)... }
	{
	}

	Color index_to_color(size_t idx) const override
	{
		return _colors[idx % N];
	}

	Color norm_to_color(DataNorm val) const override
	{
		return interpolate_color(val.norm());
	}

  private:
	Color _colors[N];
	Color interpolate_color(float val) const
	{
		size_t idx1;             // |-- Our desired color will be between these two indexes in "color".
		size_t idx2;             // |
		float fract_between = 0; // Fraction between "idx1" and "idx2" where our value is.

		if (val <= 0)
		{
			idx1 = idx2 = 0;
		} // accounts for an input <=0
		else if (val >= 1)
		{
			idx1 = idx2 = N - 1;
		} // accounts for an input >=0
		else
		{
			val = val * (N - 1);
			idx1 = floor(val);
			idx2 = idx1 + 1;
			fract_between = val - float(idx1);
		}

		Range<uint8_t> red_range{ _colors[idx1].red, _colors[idx2].red };
		Range<uint8_t> green_range{ _colors[idx1].green, _colors[idx2].green };
		Range<uint8_t> blue_range{ _colors[idx1].blue, _colors[idx2].blue };

		return Color{ static_cast<uint8_t>(red_range.norm_to_value(fract_between)),
			                static_cast<uint8_t>(green_range.norm_to_value(fract_between)),
			                static_cast<uint8_t>(blue_range.norm_to_value(fract_between)) };
	}
};

#endif /* GRAFICI_COLOR_COLORMAP_H */
