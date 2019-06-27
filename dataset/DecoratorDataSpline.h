#ifndef ARDU_DATAVIS_DATA_DECORATOR_SPLINE_H
#define ARDU_DATAVIS_DATA_DECORATOR_SPLINE_H

#include "../Dataset.h"

class DecoratorDataSpline : public Dataset
{
public:
	void begin(Dataset *dataset, int interpolationSteps);
	void end(void);
	Point getPoint(int index);
	void refresh();
	int size(void);

private:
	Dataset *_dataset;
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
