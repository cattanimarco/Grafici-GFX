#include "Data.h"
#include <iostream>
Point DataContainerFloat::getPoint(int index)
{
	std::cout << "getpoint" << std::endl;
	Point p;
	if (index < dataSourceDescriptor.size)
	{
		// normalize data to a 0.0 .. 1.0 value
		p.x = (dataSourceDescriptor.xData[index] - dataSourceDescriptor.xMin) / (dataSourceDescriptor.xMax - dataSourceDescriptor.xMin);
		p.y = (dataSourceDescriptor.yData[index] - dataSourceDescriptor.yMin) / (dataSourceDescriptor.yMax - dataSourceDescriptor.yMin);
	}
	return p;
}

int DataContainerFloat::size(void)
{
	std::cout << "size" << std::endl;
	return dataSourceDescriptor.size;
}

Point PointIterator::operator*()
{
	std::cout << "*" << std::endl;
	Point result = dataContainer->getPoint(dataIndex);
	std::cout << "*" << std::endl;
	return result;
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
	return (((this->dataContainer) != (other.dataContainer)) || ((this->dataIndex) != (other.dataIndex)));
}

PointIterator Data::begin()
{
	PointIterator ret(dataContainer, 0);
	return ret;
}

PointIterator Data::end()
{
	PointIterator ret(dataContainer, dataContainer->size());
	return ret;
}
