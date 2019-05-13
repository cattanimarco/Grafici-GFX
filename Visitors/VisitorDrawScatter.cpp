#include "VisitorDrawScatter.h"



VisitorDrawScatter::VisitorDrawScatter(Driver *driver)
{
    this->driver = driver;
}

void VisitorDrawScatter::visit(Data *data, Line *const boundaries)
{
}

void VisitorDrawScatter::visit(Data *data, Rectangle *const boundaries)
{
}

void VisitorDrawScatter::visit(Data *data, Circle *const boundaries)
{
}

