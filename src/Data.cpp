#include "Data.h"

int DataSet::length()
{
	return arrayLength;
};

void DataSet::setLength(int arrayLength)
{
	this->arrayLength = arrayLength;
}

DataCoordinateIterator DataSet::begin()
{
	return DataCoordinateIterator(this, 0);
};
DataCoordinateIterator DataSet::end()
{
	return DataCoordinateIterator(this, length());
};

DataCoordinate DataCoordinateIterator::operator*()
{
	return dataSet->getDataCoordinate(dataIndex);
};

DataCoordinateIterator &DataCoordinateIterator::operator++()
{
	++dataIndex;
	return *this;
};

bool DataCoordinateIterator::operator!=(DataCoordinateIterator const &other)
{
	return (((this->dataSet) != (other.dataSet)) || ((this->dataIndex) != (other.dataIndex)));
};
