#ifndef GRAFICI_GFX_DATA_DECORATOR_HISTOGRAM_H
#define GRAFICI_GFX_DATA_DECORATOR_HISTOGRAM_H

#include "Data.h"

class DatasetHistogram : public Dataset
{
public:
	void begin(Dataset *dataset, int buckets);
	void end(void);
	Datapoint getDatapoint(int index);
	void refresh();
	int size(void);

private:
	Dataset *_dataset;
	int _yMax;
	int _numElem;
	int *_counters;
};

#endif //GRAFICI_GFX_DATA_DECORATOR_HISTOGRAM_H
