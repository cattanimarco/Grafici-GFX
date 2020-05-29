#ifndef GRAFICI_DATA_SOURCE_H
#define GRAFICI_DATA_SOURCE_H

#include "Types.h"
#include "Utils.h"

template <typename T>
class DataIterator;

namespace DataSource
{

template <typename T = DataNorm>
class Base
{
  public:
	virtual T at(size_t index) const = 0;

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
		return DataIterator<T>(*this, _length);
	};

  protected:
	size_t _length{ 0 };
};

} // namespace DataSource

template <typename T>
class DataIterator
{
  public:
	DataIterator(const DataSource::Base<T> &source, size_t index)
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
	const DataSource::Base<T> &_source;
	size_t _index;
};

#endif //GRAFICI_DATA_SOURCE_H
