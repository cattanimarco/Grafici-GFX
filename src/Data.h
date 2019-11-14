#ifndef GRAFICI_DATA_H
#define GRAFICI_DATA_H

#include "Arduino.h"
#include "Macros.h"

class VectorIterator;
class FloatIterator;

class Vector
{
  public:
	Vector(float x = 0.0, float y = 0.0, float z = 1.0)
	    : x{ x }
	    , y{ y }
	    , z{ z } {};
	float x;
	float y;
	float z; // third dimension only visualized via color/size/etc..
};

class DataSet
{
  public:
	virtual Vector getVector(int index) = 0;
	virtual int size(void) = 0;
	virtual void refresh() = 0;

	VectorIterator begin();
	VectorIterator end();
	FloatIterator beginX();
	FloatIterator endX();
	FloatIterator beginY();
	FloatIterator endY();
	FloatIterator beginZ();
	FloatIterator endZ();
};

class VectorIterator
{
  public:
	VectorIterator(DataSet *dataSet, int dataIndex)
	    : dataSet{ dataSet }
	    , dataIndex{ dataIndex } {};
	Vector operator*();
	VectorIterator &operator++();
	bool operator!=(VectorIterator const &other);

  private:
	DataSet *dataSet;
	int dataIndex;
};

class FloatIterator
{
  public:
	enum class FloatSource
	{
		X,
		Y,
		Z,
	};

	FloatIterator(DataSet *dataSet, int dataIndex, FloatSource floatSource)
	    : floatSource{ floatSource }
	    , vectorIterator{ dataSet, dataIndex } {};
	float operator*();
	FloatIterator &operator++();
	bool operator!=(FloatIterator const &other);

  private:
	FloatSource floatSource;
	VectorIterator vectorIterator;
};

#endif //GRAFICI_DATA_H
