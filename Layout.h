#ifndef ARDU_DATAVIS_LAYOUT_H
#define ARDU_DATAVIS_LAYOUT_H

class Layout
{
  public:
	draw(Display display, Square area);
	addWidget(Widget &widget, Data&data, int position);
	clearWidget(int position);
	clearWidget(Widget &widget);

  private:
	struct WidgetAssociation
	{
		Widget *widget;
		Data *data;
		int position;
	};
	LinkedList<WidgetAssociation> registeredWidgets;
};

#endif //ARDU_DATAVIS_LAYOUT_H
