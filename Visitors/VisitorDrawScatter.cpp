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
    Color c = {255, 0, 0};
    Circle circle;

    for (PointIterator it = data->begin(); it != data->end(); it++)
    {
        circle.center = projectPoint(*it, *boundaries);
        circle.outerRadius = 10;
        driver->drawCircle(circle, 10.0, c);
    }
}

void VisitorDrawScatter::visit(Data *data, Circle *const boundaries)
{
}
