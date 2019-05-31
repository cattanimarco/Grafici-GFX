#ifndef ARDU_DATAVIS_DATA_FLOAT_H
#define ARDU_DATAVIS_DATA_FLOAT_H

#include "../Data.h"
#include <iostream>

class DataFloat : public Data
{
public:
	DataFloat(float *yData, int len);
	DataFloat(float *xData, float *yData, int len);
	Point getPoint(int index);
	void refresh();
	int size(void);

private:
	float *xData;
	float *yData;
	float xMin;
	float yMin;
	float xMax;
	float yMax;
	int numElem;
};

#endif //ARDU_DATAVIS_DATA_FLOAT_H
