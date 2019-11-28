#include "DataSetFloat.h"

DataSetFloat::DataSetFloat(float *floatArray, int arrayLength)
{
	this->floatArray = floatArray;
	setLength(arrayLength);
	refresh();
}

DataCoordinate DataSetFloat::getDataCoordinate(int index)
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

void DataSetFloat::refresh()
{
	if (floatArray != nullptr)
	{
		if (length() > 0)
		{
			limits.low = limits.high = floatArray[0];
			for (int i = 1; i < length(); ++i)
			{
				limits.low = min(limits.low, floatArray[i]);
				limits.high = max(limits.high, floatArray[i]);
			}
		}
	}
	else
	{
		limits = { 0, 0 };
	}
}

/* getters */
FloatLimits DataSetFloat::dataLimits()
{
	return limits;
}

/* setters */
FloatLimits DataSetFloat::setDataLimits(FloatLimits limits)
{
	this->limits = limits;
	return dataLimits();
}
