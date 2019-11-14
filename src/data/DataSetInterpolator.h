#ifndef GRAFICI_GFX_DATA_DECORATOR_INTERPOLATOR_H
#define GRAFICI_GFX_DATA_DECORATOR_INTERPOLATOR_H

#include "../Data.h"

class DataSetInterpolator : public DataSet
{
  public:
	void begin(DataSet &dataSet, int interpolationSteps);
	Vector getVector(int index);
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

Vector DataSetInterpolator::getVector(int index)
{
	int bin = 0;
	Vector p;

	if (index < numElem)
	{
		p.x = (1.0 * index) / (numElem - 1);
		// check that we are in the correct bin
		while (p.x > dataSet->getVector(bin + 1).x)
		{
			bin++;
			if (bin == dataSet->size())
			{
				bin--;
				break;
			}
		}
		float fractBetween = (p.x - dataSet->getVector(bin).x) / (dataSet->getVector(bin + 1).x - dataSet->getVector(bin).x);
		p.y = dataSet->getVector(bin + 1).y * fractBetween + dataSet->getVector(bin).y * (1.0 - fractBetween);
		p.z = dataSet->getVector(bin + 1).z * fractBetween + dataSet->getVector(bin).z * (1.0 - fractBetween);
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
