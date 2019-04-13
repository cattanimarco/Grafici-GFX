#ifndef ARDUPLOT_GFX_DISPLAY_H
#define ARDUPLOT_GFX_DISPLAY_H

class Display
{

  public:
	Display(Driver &driver, Style &style);
	drawPoint(Point point);
	drawLine(Line line);
	drawCircle(Circle circle);
	drawSquare(Rectangle rectangle);
	fillCircle(CircleArea area);
	fillSquare(RectangleArea area);

  private:
	Driver driver;
	Style style;
};

#endif //ARDUPLOT_GFX_DISPLAY_H
