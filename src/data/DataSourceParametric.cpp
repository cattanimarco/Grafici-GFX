#include "DataSourceParametric.h"

DataSourceParametric::DataSourceParametric(DataSourceGenerator dataSourceGenerator, int arrayLength)
{
	this->dataSourceGenerator = dataSourceGenerator;
	setLength(arrayLength);
	refresh();
}

DataCoordinate DataSourceParametric::at(int index) const
{
	if (dataSourceGenerator != nullptr)
	{
		return DataCoordinate{ (dataSourceGenerator(index) - limits.low) / (limits.high - limits.low) };
	}
	else
	{
		return DataCoordinate{ 0 };
	}
}

void DataSourceParametric::refresh()
{
	if (dataSourceGenerator != nullptr)
	{
		limits = { dataSourceGenerator(0), dataSourceGenerator(0) };
		/* provide obvious implementation that iterates */
		for (int idx = 1; idx < length(); ++idx)
		{
			limits.low = graficiMin<DataCoordinate>(limits.low, dataSourceGenerator(idx));
			limits.high = graficiMax<DataCoordinate>(limits.high, dataSourceGenerator(idx));
		}
	}
	else
	{
		limits = { 0, 0 };
	}
}

/* getters */
FloatLimits DataSourceParametric::dataLimits()
{
	return limits;
}

/* setters */
FloatLimits DataSourceParametric::setDataLimits(FloatLimits limits)
{
	this->limits = limits;
	return dataLimits();
}
