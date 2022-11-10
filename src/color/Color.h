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

#ifndef GRAFICI_color_H
#define GRAFICI_color_H

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
		R5G6B5 r = (red / 255.0) * 31;
		R5G6B5 g = (green / 255.0) * 63;
		R5G6B5 b = (blue / 255.0) * 31;
		return static_cast<R5G6B5>((r << 11) | (g << 5) | (b));
	}

	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

#endif /* GRAFICI_color_H */
