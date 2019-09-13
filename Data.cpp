#include "Data.h"

DataPoint::DataPoint(void) : x(0), y(0), z(1.0) {}

DataPoint::DataPoint(float x, float y) : x(x), y(y), z(1.0) {}

DataPoint::DataPoint(float x, float y, float z) : x(x), y(y), z(z) {}

DataPointIterator Dataset::beginIt()
{
	DataPointIterator it(this, 0);
	return it;
}

DataPointIterator Dataset::endIt()
{
	DataPointIterator it(this, size());
	return it;
}

DataPoint DataPointIterator::operator*()
{
	return _dataset->getDataPoint(_dataIndex);
}

DataPointIterator &DataPointIterator::operator++()
{
	++_dataIndex;
	return *this;
}

DataPointIterator DataPointIterator::operator++(int postfix)
{
	DataPointIterator result = *this;
	++_dataIndex;
	return result;
}

bool DataPointIterator::operator!=(DataPointIterator const &other)
{
	return (((this->_dataset) != (other._dataset)) || ((this->_dataIndex) != (other._dataIndex)));
}
