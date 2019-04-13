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
	Color * colors;
	int size;
};

#endif //ARDUPLOT_GFX_STYLE_H
