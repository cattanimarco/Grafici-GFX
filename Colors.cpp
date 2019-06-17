#include "Colors.h"

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

Gradient::Gradient(int size, Color * colors) : size(size), colors(colors)
{
}

Color Gradient::getColor(float value)
{
	int idx1;				// |-- Our desired color will be between these two indexes in "color".
	int idx2;				// |
	float fractBetween = 0; // Fraction between "idx1" and "idx2" where our value is.
	Color color;

	value = min(max(value, 0.0), 1.0);

	if (value <= 0)
	{
		idx1 = idx2 = 0;
	} // accounts for an input <=0
	else if (value >= 1)
	{
		idx1 = idx2 = size - 1;
	} // accounts for an input >=0
	else
	{
		value = value * (size - 1);			// Will multiply value by 3.
		idx1 = floor(value);				// Our desired color will be after this index.
		idx2 = idx1 + 1;					// ... and before this index (inclusive).
		fractBetween = value - float(idx1); // Distance between the two indexes (0-1).
	}

	color.red = colors[idx2].red * fractBetween + colors[idx1].red * (1 - fractBetween);
	color.green = colors[idx2].green * fractBetween + colors[idx1].green * (1 - fractBetween);
	color.blue = colors[idx2].blue * fractBetween + colors[idx1].blue * (1 - fractBetween);
}
