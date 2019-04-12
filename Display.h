#ifndef ARDUPLOT_GFX_DISPLAY_INTERFACE_H
#define ARDUPLOT_GFX_DISPLAY_INTERFACE_H


class DISPLAY
{
  public:

	Display();

	drawPoint(Point point, Marker marker);
	drawLine(Point startPoint, Point endPoint);
	drawCircle(Point centerPoint, Length radius);
	fillCircle(Point centerPoint, Length radius);
	drawSquare(Point topLeft, Point topRight, Point BottomLeft, Point BottomRight);
	fillSquare(Point topLeft, Point topRight, Point BottomLeft, Point BottomRight);


	ColorPalette colors;
	DrawSizes sizes;
	LinkedList<Pattern> pattern;


};

#endif //ARDUPLOT_GFX_LAYOUT_INTERFACE_H
