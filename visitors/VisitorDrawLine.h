#ifndef ARDU_DATAVIS_VISITOR_DRAW_LINE_H
#define ARDU_DATAVIS_VISITOR_DRAW_LINE_H

#include "../VisitorDraw.h"

class VisitorDrawLine : public VisitorDraw
{
public:
	void visit(DataSet *dataset, Boundaries *boundaries);
};


#endif //ARDU_DATAVIS_VISITOR_DRAW_LINE_H
