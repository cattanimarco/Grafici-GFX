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

#include <math.h>

// Compatibility alias; prefer Range<float>::invalid().
#define INVALID_RANGE_FLOAT Range<float>::invalid()

/**
 * @brief Object representing a range between a min and a max limits
 * 
 * @tparam T type of the values of the range
 */
template <typename T>
class Range
{
  public:
	Range() = default;

	/**
	 * @brief Construct a new Range object
	 * 
	 * @param low lower limit of the range
	 * @param high higher limit of the range
	 */
	Range(const T low, const T high): low{low}, high{high}
	{
	}

	static Range invalid() { return {T(1), T(0)}; }

	bool valid() const
	{
		return isfinite(low) && isfinite(high) && low <= high;
	}

	/**
	 * @brief Return the difference between the higher and the lower limits
	 * 
	 * @return float difference between the higher and the lower limits
	 */
	float delta() const
	{
		return valid() ? difference(high, low) : 0.0f;
	}

	/**
	 * @brief Return the middle point between the higher and the lower limits computed as (lower + higher)/2
	 * 
	 * @return T middle point between the higher and the lower limits
	 */
	T mid() const
	{
		return normalized_to_value(0.5f);
	};

	/**
	 * @brief Adjust the range limits to include a given value
	 * 
	 * @param value value to be included in the range limits
	 */
	void update(const T value)
	{
		if (!isfinite(value)) return;
		if (!valid()) { low = high = value; return; }
		if (value < low) low = value;
		if (value > high) high = value;
	}

	/**
	 * @brief Map a given value to a normalized number
	 * 
	 * @param value Value to be mapped. In case this value is outside of the range limits it will be clipped before being mapped.
	 * @return float Normalized mapped value in the range [0,1].
	 */
	float value_to_norm(const T value) const
	{
		if (!valid() || !isfinite(value) || high == low || value <= low) return 0;
		if (value >= high) return 1;
		float span = difference(high, low), offset = difference(value, low);
		if (!isfinite(span))
		{
			span = static_cast<float>(high) * 0.5f - static_cast<float>(low) * 0.5f;
			offset = static_cast<float>(value) * 0.5f - static_cast<float>(low) * 0.5f;
		}
		return offset / span;
	}

	/**
	 * @brief Map a normalized number to a value within the range limits
	 * 
	 * @param value normalized number. In case this value is outside of the [0,1] range, it will be clipped before being mapped.
	 * @return T value within the range limits coreesponding to the given normalized value
	 */
	T normalized_to_value(const float value) const
	{
		if (!valid() || !isfinite(value)) return T{};
		if (value <= 0 || high == low) return low;
		if (value >= 1) return high;
		const float result = static_cast<float>(high) * value + static_cast<float>(low) * (1.0f - value);
		// Check before narrowing, including integer endpoints rounded by FP32.
		if (result <= static_cast<float>(low)) return low;
		if (result >= static_cast<float>(high)) return high;
		return static_cast<T>(result);
	}

	// Compatibility alias; prefer normalized_to_value().
	T norm_to_value(const float value) const { return normalized_to_value(value); }

	/**
	 * @brief Ensure the range limits are in the correcdt order, i.e. lower < higher
	 * 
	 */
	void sort()
	{
		if (high < low)
		{
			T temp = low;
			low = high;
			high = temp;
		}
	}

	/**
	 * @brief Check a given value is inside of the range
	 * 
	 * @param value value to check
	 * @return true, if the given value is inside the range (including the limits)
	 * @return false, if the given value is outside of the range 
	 */
	bool contains(const T value) const
	{
		return valid() && isfinite(value) && low <= value && value <= high;
	}

	/**
	 * @brief Trim a given value to the limits of the range
	 * 
	 * @param value value to be trimmed
	 * @return T value that is guaranteed to be within the range
	 */
	T trim(const T &value) const
	{
		if (!valid() || !isfinite(value)) return T{};
		return value < low ? low : (value > high ? high : value);
	}

	/**
	 * @brief Implement set union for the sum of ranges
	 * 
	 * @param other the other range to unite
	 * @return Range<T> the union of the two ranges
	 */
	Range<T> operator+(const Range<T> &other) const
	{
		if (!valid()) return other;
		if (!other.valid()) return *this;
		Range<T> result(*this);
		result.update(other.low); result.update(other.high);
		return result;
	}

	T low{};
	T high{};

  private:
	static float difference(T upper, T lower)
	{
		// Preserve small integer differences on a large offset, without signed
		// subtraction overflow when endpoints straddle zero.
		if ((upper >= 0 && lower >= 0) || (upper < 0 && lower < 0))
			return static_cast<float>(upper - lower);
		return static_cast<float>(upper) - static_cast<float>(lower);
	}
};

#endif /* GRAFICI_RANGE_H */

/** @}*/