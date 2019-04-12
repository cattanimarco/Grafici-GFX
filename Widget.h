#ifndef ARDUPLOT_GFX_WIDGET_INTERFACE_H
#define ARDUPLOT_GFX_WIDGET_INTERFACE_H


class Widget
{
  public:

	Widget();

	draw(Display display, Data data, CircularArea area);
	draw(Display display, Data data, SquareArea area);
	draw(Display display, Data data, LinearArea area);

};

#endif //ARDUPLOT_GFX_WIDGETINTERFACE_H
