#ifndef ARDU_DATAVIS_DATA_FLOAT_H
#define ARDU_DATAVIS_DATA_FLOAT_H

#include "../Data.h"

class DataFloat : public Data
{
public:
	DataFloat(float *xData, int len) : xData(xData), numElem(len) { refresh(); };
	DataFloat(float *xData, float *yData, int len) : xData(xData), yData(yData), numElem(len) { refresh(); };
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
