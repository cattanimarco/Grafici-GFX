#ifndef GRAFICI_DATA_SOURCE_H
#define GRAFICI_DATA_SOURCE_H

#include "Types.h"
#include "Utils.h"

template <typename T>
class DataIterator;

namespace DataSources
{

template <typename T = DataNorm>
class DataSource
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

template <typename T>
class RangeOpt
{
  public:
	Range<T> &limits()
	{
		return range;
	};

	const Range<T> &limits() const
	{
		return range;
	};

  protected:
	Range<T> range{ 0, 0 };
};

} // namespace DataSources

template <typename T>
class DataIterator
{
  public:
	DataIterator(const DataSources::DataSource<T> &source, size_t index)
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

	DataIterator<T> operator+(int other)
	{
		DataIterator<T> temp = *this;
		temp._index += other;
		return temp;
	}

	bool operator!=(DataIterator<T> const &other)
	{
		return ((&(this->_source) != &(other._source)) || ((this->_index) != (other._index)));
	};

  private:
	const DataSources::DataSource<T> &_source;
	size_t _index;
};

#endif //GRAFICI_DATA_SOURCE_H
