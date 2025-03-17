/*!
* \file Color.h
* \author Marco Cattani
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

#ifndef GRAFICI_COLOR_H
#define GRAFICI_COLOR_H

#include <cstdint>

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
private:
    uint8_t r, g, b;  // Use 8-bit integers instead of floats

public:
    // Constructors optimized for direct value assignment
    constexpr Color() : r(0), g(0), b(0) {}
    constexpr Color(uint8_t red, uint8_t green, uint8_t blue) 
        : r(red), g(green), b(blue) {}

    // Fast color operations using integer math
    Color operator*(float scalar) const {
        return Color(
            static_cast<uint8_t>(r * scalar),
            static_cast<uint8_t>(g * scalar),
            static_cast<uint8_t>(b * scalar)
        );
    }

    Color operator+(const Color& other) const {
        return Color(
            static_cast<uint8_t>(std::min(255, r + other.r)),
            static_cast<uint8_t>(std::min(255, g + other.g)),
            static_cast<uint8_t>(std::min(255, b + other.b))
        );
    }

    // Optimized 16-bit color conversion for Arduino displays
    uint16_t to_R5G6B5() const {
        // Pre-shift values to avoid multiple operations
        return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
    }

    // Static color constants to avoid runtime initialization
    static constexpr Color Black() { return Color(0, 0, 0); }
    static constexpr Color White() { return Color(255, 255, 255); }
    static constexpr Color Red() { return Color(255, 0, 0); }
    static constexpr Color Green() { return Color(0, 255, 0); }
    static constexpr Color Blue() { return Color(0, 0, 255); }
};

#endif /* GRAFICI_COLOR_H */

/** @}*/