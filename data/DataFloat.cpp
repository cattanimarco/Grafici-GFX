#include "DataFloat.h"

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

Point DataFloat::getPoint(int index)
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

int DataFloat::size(void)
{
	return numElem;
}

void DataFloat::refresh(void)
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


