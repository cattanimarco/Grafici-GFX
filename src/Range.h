/*!
* \file Range.h
* \author Marco Cattani <m.cattani@icloud.com>
* \version 3.0
* \date 26/02/2022
* \brief 
* \remarks None
* 
* 
* 
*/

/** \addtogroup Main
 *  @{
 */

#ifndef GRAFICI_RANGE_H
#define GRAFICI_RANGE_H

#include "numeric/Precision.h"

/*!
* \def INVALID_RANGE_FLOAT
* Value for an invalid range object
*/
#define INVALID_RANGE_FLOAT \
	{                       \
		1.0, 0.0            \
	}

/**
 * @brief Object representing a range between a min and a max limits
 * 
 * @tparam T type of the values of the range
 */
template <typename T>
class Range
{
  public:
    using Compute = typename grafici::ComputationType<T>::type;
    Range() = default;
    Range(T low, T high) : low{low}, high{high} {}
    template <typename Other>
    Range(const Range<Other> &other) : low{static_cast<T>(other.low)}, high{static_cast<T>(other.high)} {}

    static Range invalid() { return {T(1), T(0)}; }
    bool valid() const
    {
        return grafici::is_finite(low) && grafici::is_finite(high) && low <= high;
    }
    Compute delta() const { return valid() ? difference(high, low) : Compute(0); }
    T mid() const { return norm_to_value(Compute(0.5)); }

    // An invalid range is also an empty accumulator; ignore non-finite values.
    void update(T value)
    {
        if (!grafici::is_finite(value)) return;
        if (!valid()) { low = high = value; return; }
        if (value < low) low = value;
        if (value > high) high = value;
    }

    // Constant ranges normalize to zero. Invalid mapping inputs return zero;
    // callers use valid() to distinguish that fallback from a valid constant.
    Compute value_to_norm(T value) const
    {
        if (!valid() || !grafici::is_finite(value) || high == low || value <= low) return 0;
        if (value >= high) return 1;
        Compute span = difference(high, low), offset = difference(value, low);
        if (!grafici::is_finite(span))
        {
            span = static_cast<Compute>(high) * Compute(0.5) - static_cast<Compute>(low) * Compute(0.5);
            offset = static_cast<Compute>(value) * Compute(0.5) - static_cast<Compute>(low) * Compute(0.5);
        }
        return offset / span;
    }
    T norm_to_value(Compute value) const
    {
        if (!valid() || !grafici::is_finite(value)) return T{};
        if (value <= 0 || high == low) return low;
        if (value >= 1) return high;
        const Compute result = static_cast<Compute>(high) * value + static_cast<Compute>(low) * (Compute(1) - value);
        // Check before narrowing, including integer endpoints rounded by FP32.
        if (result <= static_cast<Compute>(low)) return low;
        if (result >= static_cast<Compute>(high)) return high;
        return static_cast<T>(result);
    }
    void sort()
    {
        if (high < low) { T temp = low; low = high; high = temp; }
    }
    bool contains(T value) const
    {
        return valid() && grafici::is_finite(value) && low <= value && value <= high;
    }
    T trim(const T &value) const
    {
        if (!valid() || !grafici::is_finite(value)) return T{};
        return value < low ? low : (value > high ? high : value);
    }
    Range operator+(const Range &other) const
    {
        if (!valid()) return other;
        if (!other.valid()) return *this;
        Range result(*this);
        result.update(other.low); result.update(other.high);
        return result;
    }

    T low{};
    T high{};

  private:
    static Compute difference(T upper, T lower)
    {
        // Preserve small integer differences on a large offset, without signed
        // subtraction overflow when endpoints straddle zero.
        if ((upper >= 0 && lower >= 0) || (upper < 0 && lower < 0))
            return static_cast<Compute>(upper - lower);
        return static_cast<Compute>(upper) - static_cast<Compute>(lower);
    }
};

#endif /* GRAFICI_RANGE_H */

/** @}*/