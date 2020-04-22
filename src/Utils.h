#ifndef GRAFICI_COMMON_H
#define GRAFICI_COMMON_H

#include "Range.h"

template <typename T> class Range;

template <typename T>
void graficiSwap(T &a, T &b)
{
	T swap = a;
	a = b;
	b = swap;
};

template <typename T>
T graficiMin(const T &a, const T &b)
{
	return (a < b ? a : b);
};

template <typename T>
T graficiMax(const T &a, const T &b)
{
	return (a > b ? a : b);
};

template <typename T>
T graficiTrim(const T &value, Range<T> range)
{
	range.sort();
	if (range.contains(value))
	{
		return graficiMax<T>(range.min(), graficiMin<T>(range.max(), value));
	}
	else
	{
		return value;
	}
};

#endif /* GRAFICI_COMMON_H */