#ifndef ARDU_DATAVIS_BOUNDARIES_CIRCLE_H
#define ARDU_DATAVIS_BOUNDARIES_CIRCLE_H

#include "Boundaries.h"
#include "Geometry.h"

class BoundariesCircle : public Boundaries
{
public:
	bool isInside(Point point);
	void accept(Visitor *visitor);

	Circle circle;
}
#endif //ARDU_DATAVIS_BOUNDARIES_CIRCLE_H
