#ifndef GRAFICI_GFX_VISITOR_DRAW_HEAT_H
#define GRAFICI_GFX_VISITOR_DRAW_HEAT_H

#include "../VisitorDraw.h"

class VisitorDrawHeat : public VisitorDraw
{
public:
	void visit(DataSet *dataset, Boundaries *boundaries);
};


#endif //GRAFICI_GFX_VISITOR_DRAW_HEAT_H
