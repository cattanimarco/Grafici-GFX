#include "DataSetInterpolator.h"

DataSetInterpolator::DataSetInterpolator(DataSet &dataSetX, DataSet &dataSetY, int interpolationSteps)
    : dataSetInX(&dataSetX)
    , dataSetInY(&dataSetY)
// , dataSetX(generatorX, interpolationSteps)
// , dataSetY(generatorY, interpolationSteps)
{
	dataSetX = new DataSetParametric(&generatorX, interpolationSteps);
	setLength(interpolationSteps);
	refresh();
}

DataCoordinate DataSetInterpolator::getDataCoordinate(int index) const
{
	return generatorY(index);
}

void DataSetInterpolator::refresh(void)
{
	dataSetInX->refresh();
	dataSetInY->refresh();
}

DataCoordinate DataSetInterpolator::generatorX(int index)
{
	if (index < length())
	{
		return DataCoordinate{ (1.0 * index) / (length() - 1) };
	}
	else
	{
		return DataCoordinate{ 0 };
	}
}

DataCoordinate DataSetInterpolator::generatorY(int index)
{
	if (index < length())
	{
		int bin = 0;
		DataCoordinate x = generatorX(index);

		// check that we are in the correct bin
		while (x > dataSetInX->getDataCoordinate(bin + 1))
		{
			bin++;
			if (bin == dataSetInX->length())
			{
				bin--;
				break;
			}
		}

		float fractBetween = (x - dataSetInX->getDataCoordinate(bin)) / (dataSetInX->getDataCoordinate(bin + 1) - dataSetX->getDataCoordinate(bin));
		return DataCoordinate{ dataSetInY->getDataCoordinate(bin + 1) * fractBetween + dataSetInY->getDataCoordinate(bin) * (1.0 - fractBetween) };
	}
	else
	{
		return DataCoordinate{ 0 };
	}
}