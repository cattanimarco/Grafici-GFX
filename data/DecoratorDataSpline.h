#ifndef ARDU_DATAVIS_DATA_DECORATOR_SPLINE_H
#define ARDU_DATAVIS_DATA_DECORATOR_SPLINE_H

#include "../Data.h"

class DecoratorDataSpline : public Data
{
public:
	void begin(Data *data, int interpolationSteps);
	void end(void);
	Point getPoint(int index);
	void refresh();
	int size(void);

private:
	Data *_data;
	float _xMin;
	float _yMin;
	float _xMax;
	float _yMax;
	int _numElem;

	//spline support array
	float *_b;
	float *_c;
	float *_d;
};

#endif //ARDU_DATAVIS_DATA_DECORATOR_SPLINE_H
