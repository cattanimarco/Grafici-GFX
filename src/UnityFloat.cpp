#include "UnityFloat.h"

template <class T>
double UnityFloat::operator+(T rhs)
{
	return (value / max) + rhs;
}

template <class T>
double UnityFloat::operator*(T rhs)
{
	return (value / max) * rhs;
}

UnityFloat &UnityFloat::operator=(const double &rhs)
{
	//check that 0 < rhs < 1
	value = static_cast<unsigned short>(max * rhs);
	return *this;
}
