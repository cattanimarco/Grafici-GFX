#ifndef ARDU_DATAVIS_VISITOR_DRAW_SCATTER_H
#define ARDU_DATAVIS_VISITOR_DRAW_SCATTER_H

#include "../VisitorDraw.h"

class VisitorDrawScatter : public VisitorDraw
{
public:
	void visit(Dataset *dataset, Boundaries *boundaries);
};


#endif //ARDU_DATAVIS_VISITOR_DRAW_SCATTER_H
