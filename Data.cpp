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
	return data->getPoint(dataIndex);
}

PointIterator &PointIterator::operator++()
{
	++dataIndex;
	return *this;
}

PointIterator PointIterator::operator++(int postfix)
{
	PointIterator result = *this;
	++dataIndex;
	return result;
}

bool PointIterator::operator!=(PointIterator const &other)
{
	return (((this->data) != (other.data)) || ((this->dataIndex) != (other.dataIndex)));
}
