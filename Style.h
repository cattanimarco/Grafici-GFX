#ifndef ARDU_DATAVIS_STYLE_H
#define ARDU_DATAVIS_STYLE_H

struct Color
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
}

struct Palette
{
	Color *colors;
	int size;
}

struct DrawSizes
{
	float pointSize;
	float lineTickness;
}

class Style
{
public:
	Style(Palette palette, PlotSizes sizes);
	Color getColor(float value);

private:
	DrawSizes sizes;
	Palette palette;
}

#endif //ARDU_DATAVIS_STYLE_H
