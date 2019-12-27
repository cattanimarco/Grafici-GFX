#ifndef GRAFICI_DATA_H
#define GRAFICI_DATA_H

#include "Arduino.h"
#include "Utils.h"

typedef float DataCoordinate;

class DataSourceIterator;
class DataSetIterator;

struct IntLimits
{
	int low;
	int high;
};

struct FloatLimits
{
	float low;
	float high;
};

struct DataCoordinateLimits
{
	DataCoordinate low;
	DataCoordinate high;
};
struct DataCoordinates
{
	DataCoordinate x;
	DataCoordinate y;
	DataCoordinate z;
	DataCoordinate color;
};

class DataSource
{
  public:
	virtual DataCoordinate getDataCoordinate(int index) const = 0;
	virtual void refresh() = 0;

	int length() const;
	void setLength(int arrayLength);
	DataSourceIterator begin() const;
	DataSourceIterator end() const;

  private:
	int arrayLength{ 0 };
};

class DataSet : public DataSource
{
  public:

	DataSource DataSourceX() const{};
	DataSource DataSourceY() const{};
	DataSource DataSourceZ() const;
	DataSource DataSourceColor() const;
	
	DataCoordinate getDataCoordinate(int index) const override;
	void refresh() override;

	int length() const;
	void setLength(int arrayLength);
	DataSourceIterator begin() const;
	DataSourceIterator end() const;
	
  protected:
	enum class SelectedDataSource
	{
		none,
		x,
		y,
		z,
		color
	};

	SelectedDataSource selectedDataSource{ SelectedDataSource::none };
	DataSource *dataSourceX{ nullptr };
	DataSource *dataSourceY{ nullptr };
	DataSource *dataSourceZ{ nullptr };
	DataSource *dataSourceColor{ nullptr };
};

class DataSourceIterator
{
  public:
	DataSourceIterator(const DataSource *const dataSource, int dataIndex)
	    : dataSource{ dataSource }
	    , dataIndex{ dataIndex } {};
	DataCoordinate operator*();
	DataSourceIterator &operator++();
	bool operator!=(DataSourceIterator const &other);

  private:
	const DataSource *const dataSource;
	int dataIndex;
};

// class DataCoordinatesIterator
// {
//   public:
// 	DataSourceIterator(const DataSourceIterator &const aataCoordinateIterator, int dataIndex)
// 	    : dataSource{ dataSource }
// 	    , dataIndex{ dataIndex } {};
// 	DataCoordinate operator*();
// 	DataSourceIterator &operator++();
// 	bool operator!=(DataSourceIterator const &other);

//   private:
// 	const DataSource *const dataSource;
// 	int dataIndex;
// };

#endif //GRAFICI_DATA_H
