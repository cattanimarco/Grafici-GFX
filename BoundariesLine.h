#ifndef ARDU_DATAVIS_BOUNDARIES_LINE_H
#define ARDU_DATAVIS_BOUNDARIES_LINE_H

#include "Boundaries.h"
#include "Geometry.h"

class BoundariesLine : public Boundaries
{
public:
	bool isInside(Point point);
	void accept(Visitor *visitor);

	Line line;
};

#endif //ARDU_DATAVIS_BOUNDARIES_LINE_H
