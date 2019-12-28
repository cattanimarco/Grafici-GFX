#include "DataSetInterpolator.h"

DataSetInterpolator::DataSetInterpolator(DataSet &dataSetX, DataSet &dataSetY, int interpolationSteps)
    : dataSetX(&dataSetX)
    , dataSetY(&dataSetY)
{
	setLength(interpolationSteps);
	refresh();
}

DataCoordinate DataSetInterpolator::getDataCoordinate(int index) const
{
	if (DatasetSelection::none == selectedDataset)
	{
		return DataCoordinate{ 0 };
	}

	if (index < length())
	{
		int bin = 0;
		DataCoordinate x = (1.0 * index) / (length() - 1);

		if (DatasetSelection::x == selectedDataset)
		{
			return x;
		}

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
		return DataCoordinate{ dataSetY->getDataCoordinate(bin + 1) * fractBetween + dataSetY->getDataCoordinate(bin) * (1.0 - fractBetween) };
	}
	else
	{
		return DataCoordinate{ 0 };
	}
}

void DataSetInterpolator::refresh()
{
	dataSetX->refresh();
	dataSetY->refresh();
}

DataSetInterpolator DataSetInterpolator::interpolatedX() const
{
	/* return a copy */
	DataSetInterpolator result = *this;
	result.selectedDataset = DatasetSelection::x;
	return result;
}

DataSetInterpolator DataSetInterpolator::interpolatedY() const
{
		/* return a copy */
	DataSetInterpolator result = *this;
	result.selectedDataset = DatasetSelection::y;
	return result;
}