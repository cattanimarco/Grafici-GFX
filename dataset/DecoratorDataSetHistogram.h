#ifndef GRAFICI_GFX_DATA_DECORATOR_HISTOGRAM_H
#define GRAFICI_GFX_DATA_DECORATOR_HISTOGRAM_H

#include "../Data.h"

class DecoratorDataSetHistogram : public DataSet
{
public:
	void begin(DataSet *dataset, int buckets);
	void end(void);
	DataPoint getDataPoint(int index);
	void refresh();
	int size(void);

private:
	DataSet *_dataset;
	int _yMax;
	int _numElem;
	int *_counters;
};

#endif //GRAFICI_GFX_DATA_DECORATOR_HISTOGRAM_H
