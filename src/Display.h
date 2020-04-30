#ifndef GRAFICI_DISPLAY_H
#define GRAFICI_DISPLAY_H

#include "Types.h"
#include "Adafruit_GFX.h"
#include "Vector.h"

class Display
{
  public:
	void begin(Adafruit_GFX &driver)
	{
		_driver = &driver;
	}

	Adafruit_GFX &driver()
	{
		return *_driver;
	}

	void line(CartesianVector<DisplayNorm> begin, CartesianVector<DisplayNorm> end, ColorGFX color) const
	{
		auto pixel_begin = project(begin);
		auto pixel_end = project(end);
		/* TODO add color blending between two points */
		_driver->writeLine(pixel_begin.x(), pixel_begin.y(), pixel_end.x(), pixel_end.y(), color);
	}

	void fillRect(CartesianVector<DisplayNorm> bl, CartesianVector<DisplayNorm> tr, ColorGFX color) const
	{
		CartesianVector<DisplayAbd> pixel_bl = project(bl);
		CartesianVector<DisplayAbd> pixel_tr = project(tr);
		CartesianVector<DisplayAbd> pixel_delta = pixel_tr - pixel_bl;
		_driver->fillRect(pixel_bl.x(), pixel_bl.y(), pixel_delta.x(), pixel_delta.y(), color);
	}

	/* from normalized display vector to absolute pixel vector */
	CartesianVector<DisplayAbd> project(CartesianVector<DisplayNorm> vector) const
	{
		return CartesianVector<DisplayAbd>{ vector.x() * (_driver->width()-1),
			                                (1 - vector.y()) * (_driver->height()-1) };
	};

  private:
	Adafruit_GFX *_driver;
};

#endif /* GRAFICI_DISPLAY_H */
