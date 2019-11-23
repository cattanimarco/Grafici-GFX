#include "Color.h"

ColorCoordinates ColorSet::project(DataCoordinate val)
{
	int idx1;               // |-- Our desired color will be between these two indexes in "color".
	int idx2;               // |
	float fractBetween = 0; // Fraction between "idx1" and "idx2" where our value is.

	if (val <= 0)
	{
		idx1 = idx2 = 0;
	} // accounts for an input <=0
	else if (val >= 1)
	{
		idx1 = idx2 = size - 1;
	} // accounts for an input >=0
	else
	{
		val = val * (size - 1);
		idx1 = floor(val);
		idx2 = idx1 + 1;
		fractBetween = val - float(idx1);
	}

	return ColorCoordinates{ static_cast<ColorCoordinate>(colors[idx2].red * fractBetween + colors[idx1].red * (1 - fractBetween)),
		                     static_cast<ColorCoordinate>(colors[idx2].green * fractBetween + colors[idx1].green * (1 - fractBetween)),
		                     static_cast<ColorCoordinate>(colors[idx2].blue * fractBetween + colors[idx1].blue * (1 - fractBetween)) };
}

ColorGFX ColorSet::projectGFX(DataCoordinate val)
{
	ColorCoordinates color = project(val);
	ColorGFX r = (color.red / 255.0) * 31;
	ColorGFX g = (color.green / 255.0) * 63;
	ColorGFX b = (color.blue / 255.0) * 31;
	return ColorGFX{
		(r << 11) | (g << 5) | (b)
	};
}
