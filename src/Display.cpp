#include "Display.h"

PixelCoordinates Display::project(DisplayCoordinates displayCoordinates) const
{
	return PixelCoordinates{ displayCoordinates.x * tft.width(),
		                     (1 - displayCoordinates.y) * tft.height() };
}

PixelCoordinates Display::project(DisplayCoordinate x, DisplayCoordinate y) const
{
	return project(DisplayCoordinates{ x, y });
}
