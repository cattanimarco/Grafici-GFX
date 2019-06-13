#ifndef ARDU_DATAVIS_VISITOR_DRAW_BAR_H
#define ARDU_DATAVIS_VISITOR_DRAW_BAR_H

#include "../VisitorDraw.h"

class VisitorDrawBar : public VisitorDraw
{
public:

	void visit(Data *data, Boundaries *boundaries);
};


#endif //ARDU_DATAVIS_VISITOR_DRAW_BAR_H
