#ifndef GRAFICI_DISPLAY_H
#define GRAFICI_DISPLAY_H

#include "Adafruit_GFX.h"
#include "Types.h"
#include "Utils.h"
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
		_driver->drawLine(pixel_begin.x(), pixel_begin.y(), pixel_end.x(), pixel_end.y(), color);
	}

	void fillRect(CartesianVector<DisplayNorm> bl, CartesianVector<DisplayNorm> tr, ColorGFX color) const
	{
		CartesianVector<DisplayAbd> pixel_bl = project(bl);
		CartesianVector<DisplayAbd> pixel_tr = project(tr);
		CartesianVector<DisplayAbd> pixel_delta = pixel_tr - pixel_bl;
		/* Use min betwee bl and tr as Adafruit GFX does not handle when top is actually bottom and viceversa */
		/* This can happen when we flip our boundary */
		_driver->fillRect(graficiMin(pixel_bl.x(), pixel_tr.x()), graficiMin(pixel_bl.y(), pixel_tr.y()), abs(pixel_delta.x()), abs(pixel_delta.y()), color);
	}

	void fillRect(CartesianVector<DisplayNorm> bl, CartesianVector<DisplayNorm> br,CartesianVector<DisplayNorm> tl, CartesianVector<DisplayNorm> tr, ColorGFX color) const
	{
		//TODO if this is a simple rectangle call fillRect(bl,tr,color)
		CartesianVector<DisplayAbd> pixel_bl = project(bl);
		CartesianVector<DisplayAbd> pixel_br = project(br);
		CartesianVector<DisplayAbd> pixel_tl = project(tl);
		CartesianVector<DisplayAbd> pixel_tr = project(tr);

		/* Draw rect as two triangles to avoid transformations */
		_driver->fillTriangle(pixel_bl.x(),pixel_bl.y(),pixel_br.x(),pixel_br.y(),pixel_tl.x(),pixel_tl.y(),color);
		_driver->fillTriangle(pixel_tl.x(),pixel_tl.y(),pixel_tr.x(),pixel_tr.y(),pixel_br.x(),pixel_br.y(),color);
	}

	void circle(CartesianVector<DisplayNorm> center, CartesianVector<DisplayNorm> radius, ColorGFX color) const
	{
		CartesianVector<DisplayAbd> circle_center = project(center);

		if ((radius.x() == 0) || (radius.y() == 0))
		{
			_driver->drawPixel(circle_center.x(), circle_center.y(), color);
		}
		else
		{
			CartesianVector<DisplayAbd> circle_radius = project(radius);
			_driver->drawCircle(circle_center.x(), circle_center.y(), graficiMin(circle_radius.x(), circle_radius.y()), color);
		}
	}

	/* TODO provide a deformable circle given a 4-point rectangle */
	void fillCircle(CartesianVector<DisplayNorm> center, CartesianVector<DisplayNorm> radius, ColorGFX color) const
	{
		CartesianVector<DisplayAbd> circle_center = project(center);

		if ((radius.x() == 0) || (radius.y() == 0))
		{
			_driver->drawPixel(circle_center.x(), circle_center.y(), color);
		}
		else
		{
			CartesianVector<DisplayAbd> circle_radius = project(radius);
			_driver->fillCircle(circle_center.x(), circle_center.y(), graficiMin(circle_radius.x(), circle_radius.y()), color);
		}
	}

	void point(CartesianVector<DisplayNorm> center, ColorGFX color) const
	{
		circle(center, { 0, 0 }, color);
	}

	/* from normalized display vector to absolute pixel vector */
	CartesianVector<DisplayAbd> project(CartesianVector<DisplayNorm> vector) const
	{
		return CartesianVector<DisplayAbd>{ static_cast<DisplayAbd>(vector.x() * (_driver->width() - 1)),
			                                static_cast<DisplayAbd>((1 - vector.y()) * (_driver->height() - 1)) };
	};

  private:
	Adafruit_GFX *_driver;
};

#endif /* GRAFICI_DISPLAY_H */
