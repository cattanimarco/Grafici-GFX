#include "DataSourceFloat.h"

DataSourceFloat::DataSourceFloat(float *floatArray, int arrayLength)
{
	this->floatArray = floatArray;
	setLength(arrayLength);
	refresh();
}

DataCoordinate DataSourceFloat::getDataCoordinate(int index) const
{
	if ((floatArray != nullptr) && (index < length()))
	{
		/* normalize DataCoordinate against the limits range */
		return DataCoordinate{ (floatArray[index] - limits.low) / (limits.high - limits.low) };
	}
	else
	{
		return DataCoordinate{ 0 };
	}
}

void DataSourceFloat::refresh()
{
	if ((floatArray != nullptr) && (length() > 0))
	{
		limits.low = limits.high = floatArray[0];
		for (int i = 1; i < length(); ++i)
		{
			limits.low = graficiMin<float>(limits.low, floatArray[i]);
			limits.high = graficiMax<float>(limits.high, floatArray[i]);
		}
	}
	else
	{
		limits = { 0, 0 };
	}
}

/* getters */
FloatLimits DataSourceFloat::dataLimits()
{
	return limits;
}

/* setters */
FloatLimits DataSourceFloat::setDataLimits(FloatLimits limits)
{
	this->limits = limits;
	return dataLimits();
}
