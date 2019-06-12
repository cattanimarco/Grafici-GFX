#ifndef ARDU_DATAVIS_VISITOR_DRAW_AXIS_H
#define ARDU_DATAVIS_VISITOR_DRAW_AXIS_H

#include "../VisitorDraw.h"

class VisitorDrawAxis : public VisitorDraw
{
public:
	void visit(Data *data, ColorScheme *colors,Boundaries boundaries);
};


#endif //ARDU_DATAVIS_VISITOR_DRAW_AXIS_H
