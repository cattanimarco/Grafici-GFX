#ifndef ARDU_DATAVIS_STYLE_H
#define ARDU_DATAVIS_STYLE_H

struct Color
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

struct Palette
{
	Color *colors;
	Color lineColor;
	Color pointColor;
	int size;
};

struct DrawSizes
{
	int pointSize;
	int lineTickness;
};

class Style
{
public:
	Style(Palette palette, DrawSizes sizes, bool colorByValue);
	Color getColor(float value);
	// return lineColor if colorByValue == false
	Color getLineColor(float value);
	// return pointColor if colorByValue == false
	Color getPointColor(float value);

private:
	DrawSizes sizes;
	Palette palette;
	bool colorByValue;
}

#endif //ARDU_DATAVIS_STYLE_H
