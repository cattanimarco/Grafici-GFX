#ifndef ARDU_DATAVIS_BOUNDARIES_H
#define ARDU_DATAVIS_BOUNDARIES_H

#include "Geometry.h"
#include "Visitor.h"

class Boundaries
{
public:
	virtual bool isInside(Point point) = 0;
	// method to draw graph
	virtual void accept(Visitor *visitor) = 0;
};

#endif //ARDU_DATAVIS_BOUNDARIES_H
