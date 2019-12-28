#ifndef GRAFICI_DATA_H
#define GRAFICI_DATA_H

#include "Arduino.h"
#include "Utils.h"

typedef float DataCoordinate;

class DataCoordinateIterator;

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

struct DataCoordinates
{
	DataCoordinate x;
	DataCoordinate y;
	//	DataCoordinate z; // third dimension only visualized via color/size/etc..
};

class DataSet
{
  public:
	virtual DataCoordinate getDataCoordinate(int index) const = 0;
	virtual void refresh() = 0;

	int length() const;
	void setLength(int arrayLength);
	DataCoordinateIterator begin() const;
	DataCoordinateIterator end() const;

  private:
	int arrayLength{ 0 };
};

class DataCoordinateIterator
{
  public:
	DataCoordinateIterator(const DataSet *const dataSet, int dataIndex)
	    : dataSet{ dataSet }
	    , dataIndex{ dataIndex } {};
	DataCoordinate operator*();
	DataCoordinateIterator &operator++();
	bool operator!=(DataCoordinateIterator const &other);

  private:
	const DataSet *const dataSet;
	int dataIndex;
};

#endif //GRAFICI_DATA_H
