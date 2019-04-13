#ifndef ARDUPLOT_GFX_STYLE_H
#define ARDUPLOT_GFX_STYLE_H

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

#endif //ARDUPLOT_GFX_STYLE_H
