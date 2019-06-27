#ifndef ARDU_DATAVIS_DATA_DECORATOR_HISTOGRAM_H
#define ARDU_DATAVIS_DATA_DECORATOR_HISTOGRAM_H

#include "../Dataset.h"

class DecoratorDataHistogram : public Dataset
{
public:
	void begin(Dataset *dataset, int buckets);
	void end(void);
	Point getPoint(int index);
	void refresh();
	int size(void);

private:
	Dataset *_dataset;
	int _yMax;
	int _numElem;
	int *_counters;
};

#endif //ARDU_DATAVIS_DATA_DECORATOR_HISTOGRAM_H
