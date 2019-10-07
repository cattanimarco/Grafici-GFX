#ifndef GRAFICIGFXDATADECORATORHISTOGRAMH
#define GRAFICIGFXDATADECORATORHISTOGRAMH

#include "../Data.h"

class DataSetHistogram : public DataSet
{
  public:
	DataSetHistogram(){};
	~DataSetHistogram();
	void begin(DataSet &dataSet, int buckets);
	DataPoint getDataPoint(int index);
	void refresh();
	int size(void);

  private:
	DataSet *dataSet;
	int yMax;
	int numElem;
	int *counters;
};

DataSetHistogram::~DataSetHistogram()
{
	// if (counters != nullptr)
	// 	free(counters);
}

void DataSetHistogram::begin(DataSet &dataSet, int buckets)
{
	this->dataSet = &dataSet;
	numElem = buckets;
	counters = (int *)malloc(sizeof(int) * buckets);
	memset(counters, 0, sizeof(int) * buckets);
	refresh();
}

DataPoint DataSetHistogram::getDataPoint(int index)
{
	DataPoint p;
	if (index < numElem)
	{
		p.x = (1.0 * index) / (numElem - 1);
		p.y = (1.0 * counters[index]) / yMax;
	}

	return p;
}

int DataSetHistogram::size(void)
{
	return numElem;
}

void DataSetHistogram::refresh(void)
{
	yMax = 0;

	for (DataPointIterator it = dataSet->beginIt(); it != dataSet->endIt(); ++it)
	{
		DataPoint p = *it;
		int target = round(p.y * (numElem - 1));
		counters[target]++;
		yMax = max(counters[target], yMax);
	}
}

#endif //GRAFICIGFXDATADECORATORHISTOGRAMH
