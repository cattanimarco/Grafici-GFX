#ifndef ARDU_DATAVIS_DATA_DECORATOR_SPLINE_H
#define ARDU_DATAVIS_DATA_DECORATOR_SPLINE_H

#include "../Data.h"

class DecoratorDataSpline : public Data
{
public:
	DecoratorDataSpline(Data *data, int interpolationSteps);
	Point getPoint(int index);
	void refresh();
	int size(void);

private:
	Data *data;
	float xMin;
	float yMin;
	float xMax;
	float yMax;
	int numElem;

	//spline support array
	float *b;
	float *c;
	float *d;
};

#endif //ARDU_DATAVIS_DATA_DECORATOR_SPLINE_H
