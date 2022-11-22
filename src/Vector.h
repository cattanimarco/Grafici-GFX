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

#endif /* GRAFICI_VECTOR_H */

/** @}*/