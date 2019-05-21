#ifndef ARDU_DATAVIS_DRIVER_H
#define ARDU_DATAVIS_DRIVER_H

#include "Style.h"
#include "Geometry.h"

class Driver
{
  public:
  	// implemented high level api
	void drawPixel(Point point, int thickness, Color color);
	void drawLine(Line line, int thickness, Color color);
	void drawCircle(Circle circle, int thickness, Color color);
	void drawRectangle(Rectangle rectangle, int thickness, Color color);
	void fillRectangle(Rectangle rectangle, int thickness, Color color);
	void fillCircle(Circle circle, int thickness, Color color);
	
protected:
	// low level api interface 
	virtual void drawPixel(int x, int y, Color color) =0;
	virtual void drawLine(int x1, int y1, int x2, int y2, Color color)=0;
	virtual void drawCircle(int x, int y, int radius, Color color)=0;
	virtual void drawRectangle(int xTopLeft, int yTopLeft, int xBottomRight, int yBottomRight, Color color)=0;
	virtual void fillRectangle(int xTopLeft, int yTopLeft, int xBottomRight, int yBottomRight, Color color)=0;
	virtual	void fillCircle(int x, int y, int radius, Color color) = 0;

	virtual int width(void) = 0;
	virtual int height(void) = 0;

	// implemented low level api
	void fillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color color);
private:



};

#endif //ARDU_DATAVIS_DRIVER_H
