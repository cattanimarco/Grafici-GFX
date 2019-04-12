#ifndef ARDUPLOT_GFX_DISPLAY_INTERFACE_H
#define ARDUPLOT_GFX_DISPLAY_INTERFACE_H


class Display
{

public:

	Display();

	drawPoint(Point point);

	drawLine(Line line);
	drawCircle(CircleArea area);
	drawSquare(RectangleArea area);

	fillCircle(CircleArea area);
	fillSquare(RectangleArea area);


};

#endif //ARDUPLOT_GFX_LAYOUT_INTERFACE_H
