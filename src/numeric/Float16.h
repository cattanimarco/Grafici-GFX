#ifndef GRAFICI_NUMERIC_FLOAT16_H
#define GRAFICI_NUMERIC_FLOAT16_H

#include <float.h>
#include <stdint.h>
#include <string.h>

namespace grafici {

// IEEE 754 binary16 storage. Arithmetic promotes to float; assignment rounds
// to nearest, ties to even. This is a signed floating-point format, not UNORM.
class Float16
{
    struct RawBits {};
    constexpr Float16(uint16_t bits, RawBits) : _bits(bits) {}

public:
    Float16() = default;
    Float16(float value) : _bits(encode(value)) {}

    operator float() const { return decode(_bits); }

    Float16 &operator+=(float value) { return *this = float(*this) + value; }
    Float16 &operator-=(float value) { return *this = float(*this) - value; }
    Float16 &operator*=(float value) { return *this = float(*this) * value; }
    Float16 &operator/=(float value) { return *this = float(*this) / value; }

    constexpr uint16_t bits() const { return _bits; }

    static constexpr Float16 from_bits(uint16_t bits)
    {
        return Float16(bits, RawBits{});
    }

private:
    static_assert(sizeof(float) == 4 && FLT_RADIX == 2 &&
                  FLT_MANT_DIG == 24 && FLT_MAX_EXP == 128,
                  "Float16 requires IEEE binary32 float");

    static uint32_t round_shift(uint32_t value, unsigned shift)
    {
        const uint32_t result = value >> shift;
        const uint32_t remainder = value & ((uint32_t(1) << shift) - 1);
        const uint32_t halfway = uint32_t(1) << (shift - 1);
        return result + (remainder > halfway ||
                         (remainder == halfway && (result & 1)));
    }

    static uint16_t encode(float value)
    {
        uint32_t bits;
        memcpy(&bits, &value, sizeof(bits));
        const uint16_t sign = (bits >> 16) & 0x8000;
        const unsigned exponent = (bits >> 23) & 0xFF;
        const uint32_t fraction = bits & 0x7FFFFF;
        if (exponent == 0xFF)
        {
            // Preserve NaN sign/payload where possible and quiet all NaNs.
            return sign | 0x7C00 | (fraction ? ((fraction >> 13) | 0x0200) : 0);
        }

        const int half_exponent = int(exponent) - 112;
        if (half_exponent >= 31)
            return sign | 0x7C00;
        if (half_exponent <= 0)
        {
            if (half_exponent < -10)
                return sign;
            return sign | round_shift(fraction | 0x800000, unsigned(14 - half_exponent));
        }

        // A rounded fraction of 0x400 carries into the exponent, including
        // finite overflow at 65520, which rounds to infinity.
        return sign | uint16_t((unsigned(half_exponent) << 10) + round_shift(fraction, 13));
    }

    static float decode(uint16_t bits)
    {
        const uint32_t sign = uint32_t(bits & 0x8000) << 16;
        const unsigned exponent = (bits >> 10) & 0x1F;
        uint32_t fraction = bits & 0x03FF;
        uint32_t result;
        if (exponent == 0)
        {
            if (fraction == 0)
                result = sign;
            else
            {
                unsigned normalized_exponent = 113;
                while (!(fraction & 0x0400))
                {
                    fraction <<= 1;
                    --normalized_exponent;
                }
                result = sign | (uint32_t(normalized_exponent) << 23) |
                         ((fraction & 0x03FF) << 13);
            }
        }
        else
        {
            const unsigned expanded_exponent = exponent == 31 ? 255 : exponent + 112;
            result = sign | (uint32_t(expanded_exponent) << 23) | (fraction << 13);
        }
        float value;
        memcpy(&value, &result, sizeof(value));
        return value;
    }

    uint16_t _bits;
};

static_assert(sizeof(Float16) == 2, "Float16 must occupy two bytes");

} // namespace grafici

#endif
