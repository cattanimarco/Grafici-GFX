#include "DataSetParametric.h"

DataSetParametric::DataSetParametric(DataSetGenerator dataSetGenerator, int arrayLength)
{
	this->dataSetGenerator = dataSetGenerator;
	setLength(arrayLength);
	refresh();
}

DataCoordinate DataSetParametric::getDataCoordinate(int index) const
{
	if (dataSetGenerator != nullptr)
	{
		return DataCoordinate{ (dataSetGenerator(index) - limits.low) / (limits.high - limits.low) };
	}
	else
	{
		return DataCoordinate{ 0 };
	}
}

void DataSetParametric::refresh()
{
	if (dataSetGenerator != nullptr)
	{
		limits = { dataSetGenerator(0), dataSetGenerator(0) };
		/* provide obvious implementation that iterates */
		for (int idx = 1; idx < length(); ++idx)
		{
			limits.low = graficiMin<float>(limits.low, dataSetGenerator(idx));
			limits.high = graficiMax<float>(limits.high, dataSetGenerator(idx));
		}
	}
	else
	{
		limits = { 0, 0 };
	}
}

/* getters */
FloatLimits DataSetParametric::dataLimits()
{
	return limits;
}

/* setters */
FloatLimits DataSetParametric::setDataLimits(FloatLimits limits)
{
	this->limits = limits;
	return dataLimits();
}
