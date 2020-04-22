#ifndef GRAFICI_VECTOR_H
#define GRAFICI_VECTOR_H

template <typename T>
class Vector2D
{
  public:
	Vector2D(T first, T second)
	    : _first{ first }
	    , _second{ second }
	{
	}

Vector2D<T> operator-(const Vector2D<T> &other)
{
	return Vector2D<T>{ static_cast<T>(this->_first - other._first), static_cast<T>(this->_second - other._second) };
};

Vector2D<T> operator+(const Vector2D<T> &other)
{
	return Vector2D<T>{ static_cast<T>(this->_first + other._first), static_cast<T>(this->_second + other._second) };
};

  protected:
	T _first;
	T _second;
};

template <typename T>
class CartesianVector : public Vector2D<T>
{
  public:
	CartesianVector(const T &x, const T &y)
	    : Vector2D<T>{ x, y }
	{
	}
	CartesianVector(Vector2D<T> vector)
	    : Vector2D<T>{ vector }
	{
	}
	T &x()
	{
		return Vector2D<T>::_first;
	}
	T &y()
	{
		return Vector2D<T>::_second;
	}

	const T &x() const
	{
		return Vector2D<T>::_first;
	}
	const T &y() const
	{
		return Vector2D<T>::_second;
	}
};

template <typename T>
class PolarVector : public Vector2D<T>
{
  public:
	PolarVector(const T &a, const T &r)
	    : Vector2D<T>{ a, r }
	{
	}
	T &a()
	{
		return Vector2D<T>::_first;
	}
	T &r()
	{
		return Vector2D<T>::_second;
	}
};

#endif /* GRAFICI_VECTOR_H */