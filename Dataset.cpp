#include "Dataset.h"

PointIterator Dataset::beginIt()
{
	PointIterator it(this, 0);
	return it;
}

PointIterator Dataset::endIt()
{
	PointIterator it(this, size());
	return it;
}

Point PointIterator::operator*()
{
	return _dataset->getPoint(_dataIndex);
}

PointIterator &PointIterator::operator++()
{
	++_dataIndex;
	return *this;
}

PointIterator PointIterator::operator++(int postfix)
{
	PointIterator result = *this;
	++_dataIndex;
	return result;
}

bool PointIterator::operator!=(PointIterator const &other)
{
	return (((this->_dataset) != (other._dataset)) || ((this->_dataIndex) != (other._dataIndex)));
}
