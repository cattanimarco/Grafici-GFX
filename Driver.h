#ifndef ARDUPLOT_GFX_DRIVER_H
#define ARDUPLOT_GFX_DRIVER_H

class Driver
{
  public:
	void drawPixel(int x, int y, Color color);
	void drawLine(int x0, int y0, int x1, int y1, Color color);
	void drawCircle(int x0, int y0, int r, Color color);
	void drawRect(int x, int y, int w, int h, Color color);
	void fillRect(int x, int y, int w, int h, Color color);
	void fillCircle(int x0, int y0, int r, Color color);
	int getWidth();
	int getHeight();
};

#endif //ARDUPLOT_GFX_DRIVER_H
