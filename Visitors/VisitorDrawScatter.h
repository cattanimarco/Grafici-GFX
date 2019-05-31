#ifndef ARDU_DATAVIS_VISITOR_DRAW_SCATTER_H
#define ARDU_DATAVIS_VISITOR_DRAW_SCATTER_H

#include "../VisitorDraw.h"

class VisitorDrawScatter : public VisitorDraw
{
public:
    VisitorDrawScatter(Driver &driver);

	void visit(Data *data, Boundaries boundaries);
};


#endif //ARDU_DATAVIS_VISITOR_DRAW_SCATTER_H
