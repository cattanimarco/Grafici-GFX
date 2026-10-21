/*!
* \file Vector.h
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

#ifndef GRAFICI_VECTOR_H
#define GRAFICI_VECTOR_H

#include <math.h>

/**
 * @brief Vector with x and y components
 * 
 * @tparam T type of the two components
 */
template <typename T>
class Vector 
{
  public:
	Vector() = default;

	// Construct a vector from invalid components.
	static Vector<T> invalid()
	{
		return { T::invalid(), T::invalid() };
	}

	/**
	 * @brief Construct a new Vector object
	 * 
	 * @param x x component
	 * @param y y component
	 */
	Vector(const T x, const T y): x{x},y{y}
	{
	}

	Vector<T> operator-(const Vector<T> &other) const
	{
		return { x - other.x, y - other.y };
	};

	Vector<T> operator+(const Vector<T> &other) const
	{
		return { x + other.x, y + other.y };
	};

	Vector<T> operator*(const float &other) const
	{
		return { x * other, y * other };
	};

	bool operator<(const Vector<T> &other) const
	{
		return (x < other.x && y < other.y);
	}
	
	T x{};
	T y{};
};

// Floating-point coordinates use NaN to represent invalidity.
template <>
inline Vector<float> Vector<float>::invalid()
{
	return {NAN, NAN};
}

#endif /* GRAFICI_VECTOR_H */

/** @}*/