#include "VisitorDrawScatter.h"
#include <iostream>


VisitorDrawScatter::VisitorDrawScatter(Driver *driver)
{
    this->driver = driver;
}

void VisitorDrawScatter::visit(Data *data, Line boundaries)
{
}

void VisitorDrawScatter::visit(Data *data, Rectangle boundaries)
{
    Color c = {255, 0, 0};
    Circle circle;

		std::cout << "Ciao" << std::endl;

PointIterator it = data->begin();
it++;

    // for (PointIterator it = data->begin(); it != data->end(); it++)
    // {
	 	std::cout << (*it).x << " " << (*it).y << std::endl;
    //     // circle.center = projectPoint(*it, *boundaries);
    //     // circle.outerRadius = 10;
    //     // driver->drawCircle(circle, 10.0, c);
    // }
}

void VisitorDrawScatter::visit(Data *data, Circle boundaries)
{
}
