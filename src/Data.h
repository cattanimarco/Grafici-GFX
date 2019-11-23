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
	DataCoordinate z; // third dimension only visualized via color/size/etc..
};

class DataSet
{
  public:
	virtual DataCoordinate getDataCoordinate(int index) = 0;
	virtual void refresh() = 0;

	int length();
	void setLength(int arrayLength);
	DataCoordinateIterator begin();
	DataCoordinateIterator end();

  private:
	int arrayLength{ 0 };
};

class DataCoordinateIterator
{
  public:
	DataCoordinateIterator(DataSet *dataSet, int dataIndex)
	    : dataSet{ dataSet }
	    , dataIndex{ dataIndex } {};
	DataCoordinate operator*();
	DataCoordinateIterator &operator++();
	bool operator!=(DataCoordinateIterator const &other);

  private:
	DataSet *dataSet;
	int dataIndex;
};

#endif //GRAFICI_DATA_H
