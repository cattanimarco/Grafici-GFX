#ifndef GRAFICI_GFX_DATA_DECORATOR_INTERPOLATOR_H
#define GRAFICI_GFX_DATA_DECORATOR_INTERPOLATOR_H

#include "../Data.h"

class DataSetInterpolator : public DataSet
{
  public:
	void begin(DataSet &dataSet, int interpolationSteps);
	DataCoordinate getDataCoordinate(int index);
	void refresh();
	int size(void);

  private:
	DataSet *dataSet;
	int numElem;
};

void DataSetInterpolator::begin(DataSet &dataSet, int interpolationSteps)
{
	this->dataSet = &dataSet;
	numElem = interpolationSteps;
}

DataCoordinates DataSetInterpolator::getDataCoordinate(int index)
{
	int bin = 0;
	DataCoordinates p;

	if (index < numElem)
	{
		p.x = (1.0 * index) / (numElem - 1);
		// check that we are in the correct bin
		while (p.x > dataSet->getDataCoordinate(bin + 1).x)
		{
			bin++;
			if (bin == dataSet->size())
			{
				bin--;
				break;
			}
		}
		float fractBetween = (p.x - dataSet->getDataCoordinate(bin).x) / (dataSet->getDataCoordinate(bin + 1).x - dataSet->getDataCoordinate(bin).x);
		p.y = dataSet->getDataCoordinate(bin + 1).y * fractBetween + dataSet->getDataCoordinate(bin).y * (1.0 - fractBetween);
		p.z = dataSet->getDataCoordinate(bin + 1).z * fractBetween + dataSet->getDataCoordinate(bin).z * (1.0 - fractBetween);
	}

	return p;
}

int DataSetInterpolator::size(void)
{
	return numElem;
}

void DataSetInterpolator::refresh(void)
{
	dataSet->refresh();
}

#endif //GRAFICI_GFX_DATA_DECORATOR_INTERPOLATOR_H
