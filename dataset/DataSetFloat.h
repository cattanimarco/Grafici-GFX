#ifndef ARDU_DATAVIS_DATA_FLOAT_H
#define ARDU_DATAVIS_DATA_FLOAT_H

#include "../Data.h"

#define ZVALUE_FROM_X (-2.0)
#define ZVALUE_FROM_Y (2.0)

class DataSetFloat : public DataSet
{
public:

	void begin(float *yDataPoint, float zValue, int len);
	void begin(float *yDataPoint, float *zDataPoint, int len);
	void begin(float *xDataPoint, float *yDataPoint, float zDataPoint, int len);
	void begin(float *xDataPoint, float *yDataPoint, float *zDataPoint, int len);
	
	DataPoint getDataPoint(int index);
	void refresh();
	int size(void);

private:
	float *_xDataPoint;
	float *_yDataPoint;
	float *_zDataPoint;
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
