#ifndef GRAFICI_DECORATOR_DatasetInterpolator_H
#define GRAFICI_DECORATOR_DatasetInterpolator_H

#include "../Data.h"

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

class DatasetInterpolator : public Dataset
{
public:
	void begin(Dataset *dataset, int interpolationSteps);
	void end(void);
	Datapoint getDatapoint(int index);
	void refresh();
	int size(void);

private:
	Dataset *_dataset;
	int _numElem;
};

void DatasetInterpolator::begin(Dataset *dataset, int interpolationSteps)
{
	_dataset = dataset;
	_numElem = interpolationSteps;
}

void DatasetInterpolator::end(void)
{
}

Datapoint DatasetInterpolator::getDatapoint(int index)
{
	int bin = 0;
	Datapoint p;

	if (index < _numElem)
	{
		p.x = (1.0 * index) / (_numElem - 1);

		//std::cout << p.x << " - ";

		// check that we are in the correct bin
		while (p.x > _dataset->getDatapoint(bin + 1).x)
		{
			bin++;
			if (bin == _dataset->size())
			{
				bin--;
				break;
			}
		}

		//std::cout << _dataset->getDatapoint(bin).x << " " << p.x << " " << _dataset->getDatapoint(bin + 1).x << std::endl;

		float fractBetween = (p.x - _dataset->getDatapoint(bin).x) / (_dataset->getDatapoint(bin + 1).x - _dataset->getDatapoint(bin).x);
		p.y = _dataset->getDatapoint(bin + 1).y * fractBetween + _dataset->getDatapoint(bin).y * (1.0 - fractBetween);
		p.value = _dataset->getDatapoint(bin + 1).value * fractBetween + _dataset->getDatapoint(bin).value * (1.0 - fractBetween);

		//std::cout << p.x << " " << p.y << " " << p.value << std::endl;
	}

	return p;
}

int DatasetInterpolator::size(void)
{
	return _numElem;
}

void DatasetInterpolator::refresh(void)
{
	_dataset->refresh();
}

#endif //GRAFICI_DECORATOR_DatasetInterpolator_H
