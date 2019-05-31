#include "DataFloat.h"
#include <iostream>

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

DataFloat::DataFloat(float *yData, int len) : xData(NULL), yData(yData), numElem(len)
{
	refresh();
};
DataFloat::DataFloat(float *xData, float *yData, int len) : xData(xData), yData(yData), numElem(len)
{
	//TODO make sure x axis is in increasing order
	refresh();
};

Point DataFloat::getPoint(int index)
{
	Point p;
	if (index < numElem)
	{
		// normalize data to a 0.0 .. 1.0 value
		p.y = (yData[index] - yMin) / (yMax - yMin);

		if (xData != NULL)
		{
			p.x = (xData[index] - xMin) / (xMax - xMin);
		}
		else
		{
			p.x = (1.0 * index) / (numElem - 1);
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
		if (yData != NULL)
		{
			yMin = yMax = yData[0];
			for (int i = 1; i < numElem; ++i)
			{
				yMin = min(yMin, yData[i]);
				yMax = max(yMax, yData[i]);
			}
		}

		if (xData != NULL)
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
