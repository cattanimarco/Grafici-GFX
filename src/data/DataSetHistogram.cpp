#include "DataSetHistogram.h"

DataSetHistogram::DataSetHistogram(DataSet &dataSet, int buckets)
{
	this->dataSet = &dataSet;
	this->buckets = (int *)malloc(sizeof(int) * buckets);
	if (this->buckets != nullptr)
	{
		setLength(buckets);
	}
	refresh();
}

DataSetHistogram::~DataSetHistogram()
{
	if (buckets != nullptr)
	{
		free(buckets);
	}
}

DataCoordinate DataSetHistogram::getDataCoordinate(int index)
{
	if (index < length())
	{
		return DataCoordinate{ (1.0 * buckets[index]) / limits.high };
	}
	else
	{
		return DataCoordinate{ 0 };
	}
}

void DataSetHistogram::refresh(void)
{
	if (buckets != nullptr)
	{
		memset(buckets, 0, sizeof(int) * length());

		limits = { 0, 0 };

		for (DataCoordinateIterator it = dataSet->begin(); it != dataSet->end(); ++it)
		{
			DataCoordinate dataCoordinate = *it;
			int target = round(dataCoordinate * (length() - 1));
			buckets[target]++;
			limits.high = max(buckets[target], limits.high);
		}
	}
}

IntLimits dataLimits()
{
}

IntLimits dataLimits(IntLimits limits)
{
}
