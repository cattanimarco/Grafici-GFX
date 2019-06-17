#ifndef ARDU_DATAVIS_DATA_FLOAT_H
#define ARDU_DATAVIS_DATA_FLOAT_H

#include "../Data.h"

class DataFloat : public Data
{
public:
	void begin(float *yData, int len);
	void begin(float *xData, float *yData, int len);
	void begin(float *xData, float *yData, float *zData, int len);
	Point getPoint(int index);
	void refresh();
	int size(void);

private:
	float *_xData;
	float *_yData;
	float *_zData;
	
	float _xMin;
	float _yMin;
	float _zMin;
	
	float _xMax;
	float _yMax;
	float _zMax;
	
	int _numElem;
};

#endif //ARDU_DATAVIS_DATA_FLOAT_H
