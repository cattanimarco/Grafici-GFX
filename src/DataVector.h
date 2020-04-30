#ifndef GRAFICI_DATA_VECTOR_H
#define GRAFICI_DATA_VECTOR_H

#include "Types.h"

template <typename T = DataNorm>
class DataVector
{
  public:
	DataVector(T x, T y, T c, T opt)
	    : _x{ x }
	    , _y{ y }
	    , _c{ c }
	    , _opt{ opt }

	{
	}
	T &x()
	{
		return _x;
	}
	T &y()
	{
		return _y;
	}
	T &c()
	{
		return _c;
	}
	T &opt()
	{
		return _opt;
	}

	const T &x() const
	{
		return _x;
	}
	const T &y() const
	{
		return _y;
	}
	const T &c() const
	{
		return _c;
	}
	const T &opt() const
	{
		return _opt;
	}

  private:
	T _x;
	T _y;
	T _c;
	T _opt;
};

#endif //GRAFICI_DATA_VECTOR_H
