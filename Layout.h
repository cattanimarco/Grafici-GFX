#ifndef ARDUPLOT_GFX_LAYOUT_INTERFACE_H
#define ARDUPLOT_GFX_LAYOUT_INTERFACE_H


class Layout
{
  public:

	draw(Display display, SquareArea area);
	
	addWidget(Widget & widget, position, layer );

private:
	LinkedList<Widget *> widgets;
	LinkedList<Data *> dataSources;

};

#endif //ARDUPLOT_GFX_LAYOUT_INTERFACE_H
