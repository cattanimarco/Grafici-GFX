#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "Grafici.h"

using Real = grafici::Float16; // Change to float to use the default precision.

Adafruit_ILI9341 gfx(10, 9);
GraficiT<Real> plot(gfx);

// Signed raw samples include values above 1; the explicit range handles units.
Real samples[] = {-2, -1, 0.5f, 1.5f, 2, 1, -0.5f, -1.5f};
DataArrayXY<Real, Real> data(samples, 8, {-3, 3});

void setup()
{
    gfx.begin();
    gfx.setRotation(3);
    plot.clear_screen();

    auto x = data.x();
    auto y = data.y();
    auto options = PlotOptionsT<Real>{}.set_axis(6, 8, gunpowder);
    plot.line(x, y, y, full_screen_for<Real>(), options);
}

void loop() {}
