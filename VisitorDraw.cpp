#include <iostream>
#include "VisitorDraw.h"

void VisitorDraw::begin(DisplayDriver &displayDriver, ColorScheme &colorScheme)
{
	_driver = &displayDriver;
	_colorScheme = &colorScheme;
}


