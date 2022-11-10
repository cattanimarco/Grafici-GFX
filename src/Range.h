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

#ifndef GRAFICI_RANGE_H
#define GRAFICI_RANGE_H

/*!
* \def INVALID_RANGE_FLOAT
* Value for an invalid range object
*/
#define INVALID_RANGE_FLOAT \
	{                       \
		0.0, 0.0            \
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

	/**
	 * @brief Return the difference between the higher and the lower limits
	 * 
	 * @return T difference between the higher and the lower limits
	 */
	T delta() const
	{
		return (high - low);
	}

	/**
	 * @brief Return the middle point between the higher and the lower limits computed as (lower + higher)/2
	 * 
	 * @return T middle point between the higher and the lower limits
	 */
	T mid() const
	{
		return (high + low) / 2.0;
	};

	/**
	 * @brief Adjust the range limits to include a given value
	 * 
	 * @param value value to be included in the range limits
	 */
	void update(const T value)
	{
		low = low < value ? low : value;
		high = high > value ? high : value;
	}

	/**
	 * @brief Map a given value to a normalized number
	 * 
	 * @param value Value to be mapped. In case this value is outside of the range limits it will be clipped before being mapped.
	 * @return float Normalized mapped value in the range [0,1].
	 */
	float value_to_norm(const T value) const
	{
		if (value <= low)
		{
			return 0.0;
		}
		else if (value >= high)
		{
			return 1.0;
		}
		else
		{
			return static_cast<float>(value - low) / static_cast<float>(delta());
		}
	}

	/**
	 * @brief Map a normalized number to a value within the range limits
	 * 
	 * @param value normalized number. In case this value is outside of the [0,1] range, it will be clipped before being mapped.
	 * @return T value within the range limits coreesponding to the given normalized value
	 */
	T norm_to_value(const float value) const
	{
		if (value <= 0.0)
		{
			return low;
		}
		else if (value >= 1.0)
		{
			return high;
		}
		else
		{
			return static_cast<T>(high * value + low * (1.0 - value));
		}
	}

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
		Range<T> tmp_range(*this);
		tmp_range.sort();
		if (tmp_range.low <= value && tmp_range.high >= value)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/**
	 * @brief Trim a given value to the limits of the range
	 * 
	 * @param value value to be trimmed
	 * @return T value that is guaranteed to be within the range
	 */
	T trim(const T &value) const
	{
		if (contains(value))
		{
			return value;
		}
		else
		{
			Range<T> tmp_range(*this);
			tmp_range.sort();
			if (value > tmp_range.high)
				return tmp_range.high;
			else if (value < tmp_range.low)
				return tmp_range.low;
			else
				return value;
		}
	}

	/**
	 * @brief Implement set union for the sum of ranges
	 * 
	 * @param other the other range to unite
	 * @return Range<T> the union of the two ranges
	 */
	Range<T> operator+(const Range<T> &other)
	{
		Range<T> result{ other.low, other.high };
		result.sort();
		result.update(low);
		result.update(high);
		return result;
	}

	T low{};
	T high{};
};

#endif /* GRAFICI_RANGE_H */
