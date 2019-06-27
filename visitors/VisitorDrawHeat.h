#ifndef ARDU_DATAVIS_VISITOR_DRAW_HEAT_H
#define ARDU_DATAVIS_VISITOR_DRAW_HEAT_H

#include "../VisitorDraw.h"

class VisitorDrawHeat : public VisitorDraw
{
public:
	void visit(Dataset *dataset, Boundaries *boundaries);
};


#endif //ARDU_DATAVIS_VISITOR_DRAW_HEAT_H
