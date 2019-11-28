#include "DataSetInterpolator.h"

DataSetInterpolator::DataSetInterpolator(DataSet &dataSet, int interpolationSteps)
{
	this->dataSet = &dataSet;
	setLength(interpolationSteps);
	refresh();
}

DataCoordinate DataSetInterpolator::getDataCoordinate(int index)
{
	int bin = 0;
	DataCoordinates p;

	if (index < numElem)
	{
		p.x = (1.0 * index) / (numElem - 1);
		// check that we are in the correct bin
		while (p.x > dataSet->getDataCoordinate(bin + 1).x)
		{
			bin++;
			if (bin == dataSet->size())
			{
				bin--;
				break;
			}
		}
		float fractBetween = (p.x - dataSet->getDataCoordinate(bin).x) / (dataSet->getDataCoordinate(bin + 1).x - dataSet->getDataCoordinate(bin).x);
	}

	` return p;
}

int DataSetInterpolator::size(void)
{
	return numElem;
}

void DataSetInterpolator::refresh(void)
{
	dataSet->refresh();
}
