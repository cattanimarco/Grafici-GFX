#include "DataSourceInterpolator.h"

DataSourceInterpolator::DataSourceInterpolator(DataSource &dataSourceX, DataSource &dataSourceY, int interpolationSteps)
{
	this->dataSourceX = &dataSourceX;
	this->dataSourceY = &dataSourceY;
	setLength(interpolationSteps);
	refresh();
}

DataCoordinate DataSourceInterpolator::getDataCoordinate(int index) const
{
	if (SelectedDataSource::none == selectedDataSource)
	{
		return DataCoordinate{ 0 };
	}

	if (index < length())
	{
		int bin = 0;
		DataCoordinate x = (1.0 * index) / (length() - 1);

		if (SelectedDataSource::x == selectedDataSource)
		{
			return x;
		}

		// check that we are in the correct bin
		while (x > dataSourceX->getDataCoordinate(bin + 1))
		{
			bin++;
			if (bin == dataSourceX->length())
			{
				bin--;
				break;
			}
		}

		float fractBetween = (x - dataSourceX->getDataCoordinate(bin)) / (dataSourceX->getDataCoordinate(bin + 1) - dataSourceX->getDataCoordinate(bin));
		return DataCoordinate{ dataSourceY->getDataCoordinate(bin + 1) * fractBetween + dataSourceY->getDataCoordinate(bin) * (1.0 - fractBetween) };
	}
	else
	{
		return DataCoordinate{ 0 };
	}
}

void DataSourceInterpolator::refresh()
{
	dataSourceX->refresh();
	dataSourceY->refresh();
}