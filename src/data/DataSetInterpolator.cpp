#include "DataSetInterpolator.h"

DataSetInterpolator::DataSetInterpolator(DataSet &dataSetX, DataSet &dataSetY, int interpolationSteps)
{
	this->dataSetX = &dataSetX;
	this->dataSetY = &dataSetY;
	setLength(interpolationSteps);
	refresh();
}

DataCoordinates DataSetInterpolator::getDataCoordinate(int index) const
{
	if (index < length())
	{
		int bin = 0;

		DataCoordinate x = (1.0 * index) / (length() - 1);
		// check that we are in the correct bin
		while (x > dataSetX->getDataCoordinate(bin + 1))
		{
			bin++;
			if (bin == dataSetX->length())
			{
				bin--;
				break;
			}
		}
		float fractBetween = (x - dataSetX->getDataCoordinate(bin)) / (dataSetX->getDataCoordinate(bin + 1) - dataSetX->getDataCoordinate(bin));
		DataCoordinate y = dataSetY->getDataCoordinate(bin + 1) * fractBetween + dataSetY->getDataCoordinate(bin) * (1.0 - fractBetween);
		return DataCoordinates{ x, y };
	}
	else
	{
		return DataCoordinates{ 0, 0 };
	}

	return p;
}

void DataSetInterpolator::refresh(void)
{
	dataSetX->refresh();
	dataSetY->refresh();
}

FloatLimits DataSetInterpolator::dataLimitsX()
{
}

FloatLimits DataSetInterpolator::setDataLimitsX(FloatLimits limits)
{
}

FloatLimits DataSetInterpolator::dataLimitsY()
{
}

FloatLimits DataSetInterpolator::setDataLimitsY(FloatLimits limits)
{
}
