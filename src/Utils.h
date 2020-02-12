#ifndef GRAFICI_UTILS_H
#define GRAFICI_UTILS_H

template <typename T>
void graficiSwap(T &a, T &b)
{
	T swap = a;
	a = b;
	b = swap;
}

template <typename T>
T graficiMin(const T &a, const T &b)
{
	return (a < b ? a : b);
}

template <typename T>
T graficiMax(const T &a, const T &b)
{
	return (a > b ? a : b);
}

#endif /* GRAFICI_UTILS_H */