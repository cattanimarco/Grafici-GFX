#include "Data.h"

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

PointIterator DataContainer::begin()
{
	PointIterator it(this, 0);
	return it;
}

PointIterator DataContainer::end()
{
	PointIterator it(this, size());
	return it;
}

Point DataContainerFloat::getPoint(int index)
{
	Point p;
	if (index < numElem)
	{
		// normalize data to a 0.0 .. 1.0 value
		p.x = (xData[index] - xMin) / (xMax - xMin);
		if (yData != 0)
		{
			p.y = (yData[index] - yMin) / (yMax - yMin);
		}
		else
		{
			p.y = index / (numElem - 1.0);
		}
	}
	return p;
}

int DataContainerFloat::size(void)
{
	return numElem;
}

void DataContainerFloat::refresh(void)
{
	if (numElem > 0)
	{
		if (yData != 0)
		{
			yMin = yMax = yData[0];
			for (int i = 1; i < numElem; ++i)
			{
				yMin = min(yMin, yData[i]);
				yMax = max(yMax, yData[i]);
			}
		}

		if (xData != 0)
		{
			xMin = xMax = xData[0];
			for (int i = 1; i < numElem; ++i)
			{
				xMin = min(xMin, xData[i]);
				xMax = max(xMax, xData[i]);
			}
		}
	}
}

Point PointIterator::operator*()
{
	return dataContainer->getPoint(dataIndex);
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

// int Data::len()
// {
// 	return dataContainer->size();
// }
