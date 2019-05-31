#ifndef ARDU_DATAVIS_DECORATOR_WIDGET_BORDER_H
#define ARDU_DATAVIS_DECORATOR_WIDGET_BORDER_H

#include "../Data.h"
#include "../VisitorDraw.h"
#include "../Widget.h"

class DecoratorWidgetBorder : public Widget
{
public:
	DecoratorWidgetBorder(Widget &widget);
	// visitor pattern
	void accept(VisitorDraw *visitor, Boundaries boundaries);

private:
	Widget *widget;
};

#endif //ARDU_DATAVIS_DECORATOR_WIDGET_BORDER_H