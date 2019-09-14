#ifndef GRAFICI_GFX_DATA_DECORATOR_INTERPOLATOR_H
#define GRAFICI_GFX_DATA_DECORATOR_INTERPOLATOR_H

#include "../Data.h"

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

class DataSetInterpolator : public DataSet
{
public:
	void begin(DataSet *dataSet, int interpolationSteps);
	void end(void);
	Datapoint getDatapoint(int index);
	void refresh();
	int size(void);

private:
	DataSet *dataSet;
	int numElem;
};

void DataSetInterpolator::begin(DataSet *dataSet, int interpolationSteps)
{
	this->dataSet = dataSet;
	numElem = interpolationSteps;
}

void DataSetInterpolator::end(void)
{
}

Datapoint DataSetInterpolator::getDatapoint(int index)
{
	int bin = 0;
	Datapoint p;

	if (index < numElem)
	{
		p.x = (1.0 * index) / (numElem - 1);
		// check that we are in the correct bin
		while (p.x > dataSet->getDatapoint(bin + 1).x)
		{
			bin++;
			if (bin == dataSet->size())
			{
				bin--;
				break;
			}
		}
		float fractBetween = (p.x - dataSet->getDatapoint(bin).x) / (dataSet->getDatapoint(bin + 1).x - dataSet->getDatapoint(bin).x);
		p.y = dataSet->getDatapoint(bin + 1).y * fractBetween + dataSet->getDatapoint(bin).y * (1.0 - fractBetween);
		p.value = dataSet->getDatapoint(bin + 1).value * fractBetween + dataSet->getDatapoint(bin).value * (1.0 - fractBetween);
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
