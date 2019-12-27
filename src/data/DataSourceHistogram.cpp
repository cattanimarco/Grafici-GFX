#include "DataSourceHistogram.h"

DataSourceHistogram::DataSourceHistogram(DataSource &dataSource, int buckets)
{
	this->dataSource = &dataSource;
	this->buckets = (int *)malloc(sizeof(int) * buckets);
	if (this->buckets != nullptr)
	{
		setLength(buckets);
	}
	refresh();
}

DataSourceHistogram::~DataSourceHistogram()
{
	if (buckets != nullptr)
	{
		free(buckets);
	}
}

DataCoordinate DataSourceHistogram::getDataCoordinate(int index) const
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

void DataSourceHistogram::refresh(void)
{
	if (buckets != nullptr)
	{
		memset(buckets, 0, sizeof(int) * length());

		limits = { 0, 0 };

		for (DataSourceIterator it = dataSource->begin(); it != dataSource->end(); ++it)
		{
			DataCoordinate dataCoordinate = *it;
			int target = round(dataCoordinate * (length() - 1));
			buckets[target]++;
			limits.high = graficiMax<int>(buckets[target], limits.high);
		}
	}
}

IntLimits DataSourceHistogram::dataLimits()
{
	return limits;
}

IntLimits DataSourceHistogram::setDataLimits(IntLimits limits)
{
	this->limits = limits;
	return dataLimits();
}
