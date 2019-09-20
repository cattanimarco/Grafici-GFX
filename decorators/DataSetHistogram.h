#ifndef GRAFICIGFXDATADECORATORHISTOGRAMH
#define GRAFICIGFXDATADECORATORHISTOGRAMH

#include "../Data.h"

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

class DataSetHistogram : public DataSet
{
public:
	void begin(DataSet *dataSet, int buckets);
	void end(void);
	DataPoint getDataPoint(int index);
	void refresh();
	int size(void);

private:
	DataSet *dataSet;
	int yMax;
	int numElem;
	int *counters;
};


void DataSetHistogram::begin(DataSet *dataSet, int buckets)
{
	this->dataSet = dataSet;
	numElem = buckets;
	counters = (int *)malloc(sizeof(int) * buckets);

	refresh();
}

void DataSetHistogram::end(void)
{
	free(counters);
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
