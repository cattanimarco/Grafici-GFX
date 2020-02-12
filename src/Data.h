#ifndef GRAFICI_DATA_H
#define GRAFICI_DATA_H

#include "Arduino.h"
#include "Utils.h"

using DataNorm = float;

template <typename T = DataNorm>
class DataCoordinates
{
	T x;
	T y;
	T z;
	T color;
};

template <typename T>
class DataLimits
{
  public:
	T low;
	T high;
};

template <typename T>
class DataIterator;

template <typename T = DataNorm>
class DataSource
{
  public:
	virtual T getData(int index) const = 0;
	virtual void refresh() = 0;
	int length() const
	{
		return arrayLength;
	};
	void setLength(int arrayLength)
	{
		this->arrayLength = arrayLength;
	};
	DataIterator<T> begin() const
	{
		return DataIterator<T>(this, 0);
	};
	DataIterator<T> end() const
	{
		return DataIterator<T>(this, length());
	};

  protected:
	int arrayLength{ 0 };
};

template <typename T = DataNorm>
class DataSet : public DataSource<DataCoordinates<T>>
{
  public:
	DataSet(DataSource<T> &dataSourceX, DataSource<T> &dataSourceY, DataSource<T> &dataSourceZ, DataSource<T> &dataSourceColor)
	    : dataSourceX{ &dataSourceX }
	    , dataSourceY{ &dataSourceY }
	    , dataSourceZ{ &dataSourceZ }
	    , dataSourceColor{ &dataSourceColor } {};

	DataCoordinates<T> getData(int index) const override;
	void refresh() override
	{
		dataSourceX->refresh();
		dataSourceY->refresh();
		dataSourceZ->refresh();
		dataSourceColor->refresh();
	};

  private:
	DataSource<T> *dataSourceX{ nullptr };
	DataSource<T> *dataSourceY{ nullptr };
	DataSource<T> *dataSourceZ{ nullptr };
	DataSource<T> *dataSourceColor{ nullptr };
};

template <typename T = DataNorm>
class DataIterator
{
  public:
	DataIterator(const DataSource<T> *const dataSource, int dataIndex)
	    : dataSource{ dataSource }
	    , dataIndex{ dataIndex } {};
	T operator*()
	{
		return dataSource->getData(dataIndex);
	};
	DataIterator<T> &operator++()
	{
		++dataIndex;
		return *this;
	};
	bool operator!=(DataIterator<T> const &other)
	{
		return (((this->dataSource) != (other.dataSource)) || ((this->dataIndex) != (other.dataIndex)));
	};

  private:
	const DataSource<T> *const dataSource;
	int dataIndex;
};

#endif //GRAFICI_DATA_H
