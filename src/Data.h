#ifndef GRAFICI_DATA_H
#define GRAFICI_DATA_H

#include "Types.h"
#include "Utils.h"

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

template <typename T>
class DataIterator;

template <typename T = DataNorm>
class DataSource
{
  public:
	virtual T at(size_t index) const = 0;
	virtual void refresh() = 0;
	virtual const size_t &length() const
	{
		return _length;
	};
	virtual size_t &length()
	{
		return _length;
	};
	DataIterator<T> begin() const
	{
		return DataIterator<T>(*this, 0);
	};
	DataIterator<T> end() const
	{
		return DataIterator<T>(*this, length());
	};

  protected:
	size_t _length{ 0 };
};

class DataSet : public DataSource<DataVector<DataNorm>>
{
  public:
	DataSet(DataSource<DataNorm> &x, DataSource<DataNorm> &y, DataSource<DataNorm> &c, DataSource<DataNorm> &opt)
	    : _x{ x }
	    , _y{ y }
	    , _c{ c }
	    , _opt{ opt }
	{
		refresh();
		length();
	};

	DataVector<DataNorm> at(size_t index) const override
	{
		return DataVector<DataNorm>{
			_x.at(index), _y.at(index), _c.at(index), _opt.at(index)
		};
	}

	size_t &length() override
	{
		_length = _x.length();
		_length = graficiMin<size_t>(_length, _y.length());
		_length = graficiMin<size_t>(_length, _c.length());
		_length = graficiMin<size_t>(_length, _opt.length());
		return _length;
	};

	void refresh() override
	{
		_x.refresh();
		_y.refresh();
		_c.refresh();
		_opt.refresh();
	};

  private:
	DataSource<DataNorm> &_x;
	DataSource<DataNorm> &_y;
	DataSource<DataNorm> &_c;
	DataSource<DataNorm> &_opt;
};

template <typename T>
class DataIterator
{
  public:
	DataIterator(const DataSource<T> &source, int index)
	    : _source{ source }
	    , _index{ index } {};
	T operator*()
	{
		return _source.at(_index);
	};

	DataIterator<T> &operator++()
	{
		++_index;
		return *this;
	};

	DataIterator<T> operator++(int)
	{
		DataIterator<T> temp = *this;
		++(*this);
		return temp;
	}

	bool operator!=(DataIterator<T> const &other)
	{
		return ((&(this->_source) != &(other._source)) || ((this->_index) != (other._index)));
	};

  private:
	const DataSource<T> &_source;
	int _index;
};

#endif //GRAFICI_DATA_H
