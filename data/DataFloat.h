#ifndef ARDU_DATAVIS_DATA_FLOAT_H
#define ARDU_DATAVIS_DATA_FLOAT_H

#include "../Data.h"

#define ZVALUE_FROM_X (-2.0)
#define ZVALUE_FROM_Y (2.0)

class DataFloat : public Data
{
public:
	void begin(float *yData, float zValue, int len);
	void begin(float *xData, float *yData, float zValue, int len);
	void begin(float *xData, float *yData, float *zData, int len);
	Point getPoint(int index);
	void refresh();
	int size(void);

private:
	float *_xData;
	float *_yData;
	float *_zData;
	float _zValue;

	float _xMin;
	float _yMin;
	float _zMin;
	
	float _xMax;
	float _yMax;
	float _zMax;
	
	int _numElem;
};

#endif //ARDU_DATAVIS_DATA_FLOAT_H
