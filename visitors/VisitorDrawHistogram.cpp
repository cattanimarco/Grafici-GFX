#include "VisitorDrawHistogram.h"

void VisitorDrawHistogram::begin(Driver &driver, int buckets)
{
	VisitorDraw::begin(driver);
	_buckets = buckets;
}

void VisitorDrawHistogram::visit(Data *data, Style *style, Boundaries boundaries)
{
	float counters[_buckets];
	float maxCounter = data->size();

	memset(counters, 0, sizeof(counters));

	for (PointIterator it = data->begin(); it != data->end(); ++it)
	{
		Point p = *it;
		int target = round(p.y * (_buckets - 1));
		counters[target] += 1.0 / maxCounter;

		Point a((float)target / _buckets + (0.1/_buckets),counters[target]);
		Point b((float)(target + 1) / _buckets - (0.1/_buckets),counters[target]);

		_driver->drawLine(a.projectPoint(boundaries), b.projectPoint(boundaries));
	}
}
