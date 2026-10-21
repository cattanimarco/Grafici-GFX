#ifndef GRAFICI_DISPLAY_CLIPPING_H
#define GRAFICI_DISPLAY_CLIPPING_H

#include "../Vector.h"
#include <math.h>

namespace grafici_clipping {

inline bool finite_point(const Vector<float> &p)
{
    return isfinite(p.x) && isfinite(p.y);
}

inline bool on_screen(const Vector<float> &p)
{
    return finite_point(p) && p.x >= 0 && p.x <= 1 && p.y >= 0 && p.y <= 1;
}

inline unsigned outcode(const Vector<float> &p)
{
    return (p.x < 0 ? 1u : (p.x > 1 ? 2u : 0u)) |
           (p.y < 0 ? 4u : (p.y > 1 ? 8u : 0u));
}

inline float fraction(float boundary, float a, float b)
{
    const float span = b - a;
    // Opposite finite extremes can overflow their difference in FP32.
    return isfinite(span) ? (boundary - a) / span
        : (boundary * float(0.5) - a * float(0.5)) / (b * float(0.5) - a * float(0.5));
}

inline float blend_coordinate(float a, float b, float weight)
{
    if (weight <= 0) return a;
    if (weight >= 1) return b;
    if ((a >= 0 && b >= 0) || (a < 0 && b < 0))
        return a + (b - a) * weight;
    return a * (float(1) - weight) + b * weight;
}

// Intersect with one screen edge: left, right, bottom, top. The clipping axis
// is set exactly to the boundary, avoiding repeated outcodes from roundoff.
inline Vector<float> edge_intersection(const Vector<float> &a, const Vector<float> &b, unsigned edge)
{
    const float boundary = (edge == 1 || edge == 3) ? float(1) : float(0);
    if (edge < 2)
        return {boundary, blend_coordinate(a.y, b.y, fraction(boundary, a.x, b.x))};
    return {blend_coordinate(a.x, b.x, fraction(boundary, a.y, b.y)), boundary};
}

// Cohen-Sutherland in normalized screen coordinates, before integer conversion.
inline bool clip_line(Vector<float> *a, Vector<float> *b)
{
    if (!finite_point(*a) || !finite_point(*b)) return false;
    for (unsigned iteration = 0; iteration < 8; ++iteration)
    {
        const unsigned ca = outcode(*a), cb = outcode(*b);
        if (!(ca | cb)) return true;
        if (ca & cb) return false;
        const unsigned code = ca ? ca : cb;
        const unsigned edge = (code & 8) ? 3 : ((code & 4) ? 2 : ((code & 2) ? 1 : 0));
        const auto p = edge_intersection(*a, *b, edge);
        if (!finite_point(p)) return false;
        if (ca) *a = p; else *b = p;
    }
    return false;
}

inline bool inside_edge(const Vector<float> &p, unsigned edge)
{
    if (edge == 0) return p.x >= 0;
    if (edge == 1) return p.x <= 1;
    if (edge == 2) return p.y >= 0;
    return p.y <= 1;
}

inline bool same_point(const Vector<float> &a, const Vector<float> &b)
{
    return a.x == b.x && a.y == b.y;
}

inline bool append_vertex(Vector<float> *points, unsigned *count, const Vector<float> &p)
{
    if (!finite_point(p)) return false;
    if (*count && same_point(points[*count - 1], p)) return true;
    if (*count == 7) return same_point(points[0], p); // Closing duplicate only.
    points[(*count)++] = p;
    return true;
}

// Sutherland-Hodgman. A triangle intersected with a rectangle has at most
// seven vertices. The caller supplies seven slots; scratch uses seven more.
inline unsigned clip_triangle(Vector<float> a, Vector<float> b, Vector<float> c, Vector<float> *points)
{
    if (!finite_point(a) || !finite_point(b) || !finite_point(c)) return 0;
    points[0] = a; points[1] = b; points[2] = c;
    Vector<float> scratch[7];
    Vector<float> *input = points, *output = scratch;
    unsigned count = 3;
    for (unsigned edge = 0; edge < 4; ++edge)
    {
        if (count == 0) return 0;
        unsigned emitted = 0;
        auto previous = input[count - 1];
        bool previous_inside = inside_edge(previous, edge);
        for (unsigned i = 0; i < count; ++i)
        {
            const auto current = input[i];
            const bool current_inside = inside_edge(current, edge);
            if (current_inside != previous_inside &&
                !append_vertex(output, &emitted, edge_intersection(previous, current, edge))) return 0;
            if (current_inside && !append_vertex(output, &emitted, current)) return 0;
            previous = current;
            previous_inside = current_inside;
        }
        if (emitted > 1 && same_point(output[0], output[emitted - 1])) --emitted;
        count = emitted;
        auto temp = input; input = output; output = temp;
    }
    // Four edges leave the final output in the caller's array.
    return count;
}

} // namespace grafici_clipping
#endif
