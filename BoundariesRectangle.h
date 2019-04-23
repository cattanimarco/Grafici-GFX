#ifndef ARDU_DATAVIS_BOUNDARIES_RECTANGLE_H
#define ARDU_DATAVIS_BOUNDARIES_RECTANGLE_H

#include "Boundaries.h"
#include "Geometry.h"

class BoundariesRectangle : public Boundaries
{
	public:
	bool isInside(Point point);
	void accept(Visitor *visitor);

	Rectangle rectangle;

}
#endif //ARDU_DATAVIS_BOUNDARIES_RECTANGLE_H
