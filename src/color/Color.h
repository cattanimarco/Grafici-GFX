/*!
* \file Color.h
* \author Marco Cattani <m.cattani@icloud.com>
* \version 3.0
* \date 26/02/2022
* \brief 
* \remarks None
* 
* 
* 
*/

/** \addtogroup Colors
 *  @{
 */

#ifndef GRAFICI_color_H
#define GRAFICI_color_H

#include <stdint.h>
#include <math.h>

/**
 * @brief 16-bit rgb color. 5-bit red, 6-bit green, 5-bit blue
 * 
 */
using R5G6B5 = uint16_t;

/**
 * @brief 24-bit rgb color. 8-bit red, 8-bit green, 8-bit blue
 * 
 */
class Color
{
  public:
	Color() = default;

	/**
	 * @brief Construct a new Color Vector object
	 * 
	 * @param red 8-bit red value
	 * @param green 8-bit green value
	 * @param blue 8-bit blue value
	 */
	Color(const uint8_t red, const uint8_t green, const uint8_t blue)
	    : red{ red }
	    , green{ green }
	    , blue{ blue }
	{
	}

	// Round linear channel blends to nearest, with half-way cases upward.
	Color midpoint(const Color &other) const
	{
		return {mean(red, other.red), mean(green, other.green), mean(blue, other.blue)};
	}

	Color interpolate(const Color &other, float weight) const
	{
		if (!isfinite(weight)) return {0, 0, 0};
		if (weight <= 0) return *this;
		if (weight >= 1) return other;
		return {blend(red, other.red, weight), blend(green, other.green, weight),
		        blend(blue, other.blue, weight)};
	}

	Color operator-(const Color &other) const
	{
		return { static_cast<uint8_t>(red - other.red), static_cast<uint8_t>(green - other.green), static_cast<uint8_t>(blue - other.blue) };
	};

	Color operator+(const Color &other) const
	{
		return { static_cast<uint8_t>(red + other.red), static_cast<uint8_t>(green + other.green), static_cast<uint8_t>(blue + other.blue) };
	};

	Color operator*(const float &other) const
	{
		return { static_cast<uint8_t>(red * other), static_cast<uint8_t>(green * other), static_cast<uint8_t>(blue * other) };
	};

	/**
	 * @brief Return the R5G6B5 representation of the color
	 * 
	 * @return R5G6B5 Color value
	 */
	R5G6B5 to_R5G6B5() const
	{
		// Preserve the existing floor-scaled bins using widened integer math.
		const R5G6B5 r = (uint16_t(red) * 31u) / 255u;
		const R5G6B5 g = (uint16_t(green) * 63u) / 255u;
		const R5G6B5 b = (uint16_t(blue) * 31u) / 255u;
		return static_cast<R5G6B5>((r << 11) | (g << 5) | (b));
	}

	uint8_t red;
	uint8_t green;
	uint8_t blue;

  private:
	static uint8_t mean(uint8_t a, uint8_t b)
	{
		return static_cast<uint8_t>((uint16_t(a) + uint16_t(b) + 1u) / 2u);
	}
	static uint8_t blend(uint8_t a, uint8_t b, float weight)
	{
		return static_cast<uint8_t>(a * (1.0f - weight) + b * weight + 0.5f);
	}
};

#endif /* GRAFICI_color_H */

/** @}*/