#ifndef ARDU_DATAVIS_DATA_FLOAT_H
#define ARDU_DATAVIS_DATA_FLOAT_H

#include "../Data.h"
#include <iostream>

class DataFloat : public Data
{
public:
	void begin(float *yData, int len);
	void begin(float *xData, float *yData, int len);
	Point getPoint(int index);
	void refresh();
	int size(void);

private:
	float *_xData;
	float *_yData;
	float _xMin;
	float _yMin;
	float _xMax;
	float _yMax;
	int _numElem;
};

#endif //ARDU_DATAVIS_DATA_FLOAT_H
