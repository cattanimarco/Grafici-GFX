#ifndef ARDU_DATAVIS_VISITOR_DRAW_COUT_H
#define ARDU_DATAVIS_VISITOR_DRAW_COUT_H

#include "../VisitorDraw.h"
#include <iostream>

class VisitorDrawCout : public VisitorDraw
{
public:
    VisitorDrawCout(Driver *driver);

    void visit(Data *data, Line boundaries);
    void visit(Data *data, Rectangle boundaries);
    void visit(Data *data, Circle boundaries);
};

#endif //ARDU_DATAVIS_VISITOR_DRAW_COUT_H
