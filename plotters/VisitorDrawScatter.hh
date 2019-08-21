#ifndef GRAFICI_GFX_VISITOR_DRAW_SCATTER_H
#define GRAFICI_GFX_VISITOR_DRAW_SCATTER_H

#include "../VisitorDraw.h"

class VisitorDrawScatter : public VisitorDraw
{
public:
	void visit(Dataset *dataset, Boundaries *boundaries);
};


#endif //GRAFICI_GFX_VISITOR_DRAW_SCATTER_H
