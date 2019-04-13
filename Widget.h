#ifndef ARDUPLOT_GFX_WIDGET_H
#define ARDUPLOT_GFX_WIDGET_H


class Widget
{
  public:

	draw(Display &display, Data &data, Line boundaries);
	draw(Display &display, Data &data, Square boundaries);
	draw(Display &display, Data &data, Circle boundaries);

};

#endif //ARDUPLOT_GFX_WIDGET_H
