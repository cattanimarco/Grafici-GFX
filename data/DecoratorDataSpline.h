#ifndef ARDU_DATAVIS_DATA_DECORATOR_SPLINE_H
#define ARDU_DATAVIS_DATA_DECORATOR_SPLINE_H

#include "../Data.h"

class DataSpline : public Data
{
public:
	DataSpline(Data *data);
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
};

#endif //ARDU_DATAVIS_DATA_DECORATOR_SPLINE_H
