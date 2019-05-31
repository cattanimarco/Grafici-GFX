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
	return Data->getPoint(dataIndex);
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
	return (((this->Data) != (other.Data)) || ((this->dataIndex) != (other.dataIndex)));
}

