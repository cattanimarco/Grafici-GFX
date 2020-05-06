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
	Range(T min, T max)
	    : Vector2D<T>{ min, max }
	{
	}

	T &min()
	{
		return Vector2D<T>::_first;
	}

	T &max()
	{
		return Vector2D<T>::_second;
	}

	const T &min() const
	{
		return Vector2D<T>::_first;
	}

	const T &max() const
	{
		return Vector2D<T>::_second;
	}

	T delta() const
	{
		return (max() - min());
	};

	T mid() const
	{
		return (max() + min()) / 2;
	};

	void update(T value)
	{
		min() = graficiMin<T>(min(), value);
		max() = graficiMax<T>(max(), value);
	}

	/* map a value in the range to a double between 0 and 1 */
	double normalize(T value) const
	{
		/* TODO assert value is between min and max */
		return (value - min()) / (1.0 * delta());
	};

	/* map a double value from 0 to 1 to the range's corrsponding value  */
	T map(double value) const
	{
		/* TODO assert value is between 0.0 and 1.0 */
		return static_cast<T>(value * max() + (1.0 - value) * min());
	};

	/* addBorderRelative a given range by a (normalized) factor */
	void addBorderRelative(const Range<double> &shrinkFactor)
	{
		min() += delta() * shrinkFactor.min();
		max() -= delta() * shrinkFactor.max();
	};

	/* addBorderRelative a given range by a (normalized) factor */
	void addBorderAbsolute(const Range<double> &shrinkValue)
	{
		min() += shrinkValue.min();
		max() -= shrinkValue.max();
	};
	
	void flip()
	{
		graficiSwap<T>(min(), max());
	};

	void sort()
	{
		if (max() < min())
		{
			flip();
		}
	}

	bool contains(T value)
	{
		if ((graficiMin<T>(min(), max()) <= value) && (value <= graficiMax<T>(min(), max())))
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
