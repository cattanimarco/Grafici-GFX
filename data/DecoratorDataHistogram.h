#ifndef ARDU_DATAVIS_DATA_DECORATOR_HISTOGRAM_H
#define ARDU_DATAVIS_DATA_DECORATOR_HISTOGRAM_H

#include "../Data.h"

class DecoratorDataHistogram : public Data
{
public:
	void begin(Data *data, int buckets);
	void end(void);
	Point getPoint(int index);
	void refresh();
	int size(void);

private:
	Data *_data;
	int _yMax;
	int _numElem;
	int *_counters;
};

#endif //ARDU_DATAVIS_DATA_DECORATOR_HISTOGRAM_H
