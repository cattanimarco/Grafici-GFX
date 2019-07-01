#ifndef ARDU_DATAVIS_DATA_DECORATOR_SPLINE_H
#define ARDU_DATAVIS_DATA_DECORATOR_SPLINE_H

#include "../Data.h"

class DecoratorDataSetSpline : public DataSet
{
public:
	void begin(DataSet *dataset, int interpolationSteps);
	void end(void);
	DataPoint getDataPoint(int index);
	void refresh();
	int size(void);

private:
	DataSet *_dataset;
	float _xMin;
	float _yMin;
	float _valueMin;
	
	float _xMax;
	float _yMax;
	float _valueMax;
	
	int _numElem;

	//spline support arrays
	float *_bY;
	float *_cY;
	float *_dY;

	float *_bValue;
	float *_cValue;
	float *_dValue;
};

#endif //ARDU_DATAVIS_DATA_DECORATOR_SPLINE_H
