#ifndef ARDU_DATAVIS_BOUNDARIES_H
#define ARDU_DATAVIS_BOUNDARIES_H

#include "Geometry.h"
#include "Visitor.h"

class Boundaries
{
public:
	bool isInside(Point point);
	// method to draw graph
	void accept(Visitor *visitor);
}
#endif //ARDU_DATAVIS_BOUNDARIES_H

