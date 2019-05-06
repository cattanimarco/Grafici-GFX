#ifndef ARDU_DATAVIS_VISITOR_DRAW_COUT_H
#define ARDU_DATAVIS_VISITOR_DRAW_COUT_H

#include <iostream>

#include "../VisitorDraw.h"

class VisitorDrawCout : public VisitorDraw
{
public:
    VisitorDrawCout(Driver *driver);

    void visit(Data *data, Line *const boundaries);
    void visit(Data *data, Rectangle *const boundaries);
    void visit(Data *data, Circle *const boundaries);
};

VisitorDrawCout::VisitorDrawCout(Driver *driver)
{
    this->driver = driver;
}

void VisitorDrawCout::visit(Data *data, Line *const boundaries) 
{
	std::cout << "VisitorDraw::visit(line)" << std::endl;
}

void VisitorDrawCout::visit(Data *data, Rectangle *const boundaries) 
{
	std::cout << "VisitorDraw::visit(rectangle)" << std::endl;
}

void VisitorDrawCout::visit(Data *data, Circle *const boundaries) 
{
	std::cout << "VisitorDraw::visit(circle)" << std::endl;
}

#endif //ARDU_DATAVIS_VISITOR_DRAW_COUT_H

