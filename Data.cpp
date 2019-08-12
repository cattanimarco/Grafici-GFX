#include "Data.h"

Datapoint::Datapoint(void) : x(0), y(0), value(1.0) {}

Datapoint::Datapoint(float x, float y) : x(x), y(y), value(1.0) {}

DatapointIterator Dataset::beginIt()
{
	DatapointIterator it(this, 0);
	return it;
}

DatapointIterator Dataset::endIt()
{
	DatapointIterator it(this, size());
	return it;
}

Datapoint DatapointIterator::operator*()
{
	return _dataset->getDatapoint(_dataIndex);
}

DatapointIterator &DatapointIterator::operator++()
{
	++_dataIndex;
	return *this;
}

DatapointIterator DatapointIterator::operator++(int postfix)
{
	DatapointIterator result = *this;
	++_dataIndex;
	return result;
}

bool DatapointIterator::operator!=(DatapointIterator const &other)
{
	return (((this->_dataset) != (other._dataset)) || ((this->_dataIndex) != (other._dataIndex)));
}
