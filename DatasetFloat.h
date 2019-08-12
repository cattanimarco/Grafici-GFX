#ifndef GRAFICI_GFX_DATA_FLOAT_H
#define GRAFICI_GFX_DATA_FLOAT_H

#include "Data.h"

#define ZVALUE_FROM_X (-2.0)
#define ZVALUE_FROM_Y (2.0)

class DatasetFloat : public Dataset
{
public:

	void begin(float *yDatapoint, float zValue, int len);
	void begin(float *yDatapoint, float *zDatapoint, int len);
	void begin(float *xDatapoint, float *yDatapoint, float zDatapoint, int len);
	void begin(float *xDatapoint, float *yDatapoint, float *zDatapoint, int len);
	
	Datapoint getDatapoint(int index);
	void refresh();
	int size(void);

private:
	float *_xDatapoint;
	float *_yDatapoint;
	float *_zDatapoint;
	float _zValue;

	float _xMin;
	float _yMin;
	float _zMin;
	
	float _xMax;
	float _yMax;
	float _zMax;
	
	int _numElem;
};

#endif //GRAFICI_GFX_DATA_FLOAT_H
