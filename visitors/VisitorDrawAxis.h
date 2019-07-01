#ifndef ARDU_DATAVIS_VISITOR_DRAW_AXIS_H
#define ARDU_DATAVIS_VISITOR_DRAW_AXIS_H

#include "../VisitorDraw.h"

class VisitorDrawAxis : public VisitorDraw
{
public:
	void visit(DataSet *dataset, Boundaries *boundaries);
};


#endif //ARDU_DATAVIS_VISITOR_DRAW_AXIS_H
