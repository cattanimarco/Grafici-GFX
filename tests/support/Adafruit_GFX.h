#ifndef GRAFICI_TEST_GFX_H
#define GRAFICI_TEST_GFX_H

// Host drawing-call recorder; this does not emulate display rasterization.
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <string>
#include <vector>

class String
{
public:
    String(const char *text = "") : value(text) {}
    size_t length() const { return value.length(); }
    char operator[](size_t i) const { return value[i]; }
private:
    std::string value;
};

inline void randomSeed(unsigned long seed) { std::srand(seed); }
inline long random(long low, long high) { return low + std::rand() % (high - low); }
inline long random(long high) { return high > 0 ? random(0, high) : 0; }

class Adafruit_GFX
{
public:
    struct Line { int16_t x0, y0, x1, y1; uint16_t color; };
    struct Triangle { int16_t x0, y0, x1, y1, x2, y2; uint16_t color; };
    struct Pixel { int16_t x, y; uint16_t color; };
    explicit Adafruit_GFX(int16_t w = 128, int16_t h = 64) : w(w), h(h) {}
    std::vector<Line> lines;
    std::vector<Triangle> triangle_log;
    std::vector<Pixel> pixel_log;
    size_t triangles = 0, pixels = 0, screens = 0;
    int16_t width() const { return w; }
    int16_t height() const { return h; }
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
    {
        lines.push_back({x0, y0, x1, y1, color});
    }
    void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
    {
        ++triangles;
        triangle_log.push_back({x0, y0, x1, y1, x2, y2, color});
    }
    void drawPixel(int16_t x, int16_t y, uint16_t color)
    {
        ++pixels;
        pixel_log.push_back({x, y, color});
    }
    void fillScreen(uint16_t) { ++screens; }
private:
    int16_t w, h;
};

#endif
