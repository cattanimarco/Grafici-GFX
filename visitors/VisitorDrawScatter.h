#ifndef ARDU_DATAVIS_VISITOR_DRAW_SCATTER_H
#define ARDU_DATAVIS_VISITOR_DRAW_SCATTER_H

#include "../VisitorDraw.h"

class VisitorDrawScatter : public VisitorDraw
{
public:
    VisitorDrawScatter(Driver *driver);

    void visit(Data *data, Line *const boundaries);
    void visit(Data *data, Rectangle *const boundaries);
    void visit(Data *data, Circle *const boundaries);
};


#endif //ARDU_DATAVIS_VISITOR_DRAW_SCATTER_H
