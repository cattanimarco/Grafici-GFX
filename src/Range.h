#ifndef GRAFICI_RANGE_H
#define GRAFICI_RANGE_H

#include "Utils.h"
#include "Vector.h"

template <typename T>
void graficiSwap(T &a, T &b);

template <typename T>
T graficiMin(const T &a, const T &b);

template <typename T>
T graficiMax(const T &a, const T &b);

template <typename T>
class Range : public Vector2D<T>
{
  public:
	Range(const T min, const T max)
	    : Vector2D<T>{ min, max }
	{
	}

	T &low()
	{
		return Vector2D<T>::_first;
	}

	T &high()
	{
		return Vector2D<T>::_second;
	}

	const T &low() const
	{
		return Vector2D<T>::_first;
	}

	const T &high() const
	{
		return Vector2D<T>::_second;
	}

	T delta() const
	{
		return (high() - low());
	};

	T mid() const
	{
		return (high() + low()) / 2;
	};

	void update(const T value)
	{
		low() = graficiMin<T>(low(), value);
		high() = graficiMax<T>(high(), value);
	}

	/* map a value in the range to a float between 0 and 1 */
	float normalize(const T value) const
	{
		/* TODO assert value is between min and max */
		return static_cast<float>(value - low()) / static_cast<float>(delta());
	};

	/* map a float value from 0 to 1 to the range's corrsponding value  */
	T map(const float value) const
	{
		/* TODO assert value is between 0.0 and 1.0 */
		return static_cast<T>(value * high() + (1.0 - value) * low());
	};

	/* cropRelative a given range by a (normalized) factor */
	void cropRelative(const Range<float> &shrinkFactor)
	{
		low() += delta() * shrinkFactor.low();
		high() -= delta() * shrinkFactor.high();
	};

	/* cropRelative a given range by a (normalized) factor */
	void cropAbsolute(const Range<float> &shrinkValue)
	{
		low() += shrinkValue.low();
		high() -= shrinkValue.high();
	};

	void flip()
	{
		graficiSwap<T>(low(), high());
	};

	void sort()
	{
		if (high() < low())
		{
			flip();
		}
	}

	bool contains(const T value) const
	{
		if ((graficiMin<T>(low(), high()) <= value) && (value <= graficiMax<T>(low(), high())))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

#endif /* GRAFICI_RANGE_H */
