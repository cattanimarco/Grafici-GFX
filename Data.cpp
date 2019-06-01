#include "Data.h"

PointIterator Data::begin()
{
	PointIterator it(this, 0);
	return it;
}

PointIterator Data::end()
{
	PointIterator it(this, size());
	return it;
}

Point PointIterator::operator*()
{
	return _data->getPoint(_dataIndex);
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
	return (((this->_data) != (other._data)) || ((this->_dataIndex) != (other._dataIndex)));
}
