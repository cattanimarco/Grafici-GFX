#include "Data.h"

DataPoint::DataPoint(void) : x(0), y(0), z(1.0) {}

DataPoint::DataPoint(float x, float y) : x(x), y(y), z(1.0) {}

DataPoint::DataPoint(float x, float y, float z) : x(x), y(y), z(z) {}

DataPointIterator DataSet::beginIt()
{
	DataPointIterator it(this, 0);
	return it;
}

DataPointIterator DataSet::endIt()
{
	DataPointIterator it(this, size());
	return it;
}

DataPoint DataPointIterator::operator*()
{
	return dataSet->getDataPoint(dataIndex);
}

DataPointIterator &DataPointIterator::operator++()
{
	++dataIndex;
	return *this;
}

DataPointIterator DataPointIterator::operator++(int postfix)
{
<<<<<<< HEAD
	//unused variable
	(void)postfix;
	
=======
	(void)postfix;
>>>>>>> e6ad5960686b287db08262bc784a64540820d380
	DataPointIterator result = *this;
	++dataIndex;
	return result;
}

bool DataPointIterator::operator!=(DataPointIterator const &other)
{
	return (((this->dataSet) != (other.dataSet)) || ((this->dataIndex) != (other.dataIndex)));
}
