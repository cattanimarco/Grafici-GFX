#ifndef GRAFICI_DISPLAY_CLIPPING_H
#define GRAFICI_DISPLAY_CLIPPING_H

#include "../Vector.h"
#include "../numeric/Precision.h"

namespace grafici_detail {

template <typename Real>
bool finite_point(const Vector<Real> &p)
{
    return grafici::is_finite(p.x) && grafici::is_finite(p.y);
}

template <typename Real>
bool on_screen(const Vector<Real> &p)
{
    return finite_point(p) && p.x >= 0 && p.x <= 1 && p.y >= 0 && p.y <= 1;
}

template <typename Real>
unsigned outcode(const Vector<Real> &p)
{
    return (p.x < 0 ? 1u : (p.x > 1 ? 2u : 0u)) |
           (p.y < 0 ? 4u : (p.y > 1 ? 8u : 0u));
}

template <typename Real>
Real fraction(Real boundary, Real a, Real b)
{
    const Real span = b - a;
    // Opposite finite extremes can overflow their difference in FP32.
    return grafici::is_finite(span) ? (boundary - a) / span
        : (boundary * Real(0.5) - a * Real(0.5)) / (b * Real(0.5) - a * Real(0.5));
}

template <typename Real>
Real blend_coordinate(Real a, Real b, Real weight)
{
    if (weight <= 0) return a;
    if (weight >= 1) return b;
    if ((a >= 0 && b >= 0) || (a < 0 && b < 0))
        return a + (b - a) * weight;
    return a * (Real(1) - weight) + b * weight;
}

// Intersect with one screen edge: left, right, bottom, top. The clipping axis
// is set exactly to the boundary, avoiding repeated outcodes from roundoff.
template <typename Real>
Vector<Real> edge_intersection(const Vector<Real> &a, const Vector<Real> &b, unsigned edge)
{
    const Real boundary = (edge == 1 || edge == 3) ? Real(1) : Real(0);
    if (edge < 2)
        return {boundary, blend_coordinate(a.y, b.y, fraction(boundary, a.x, b.x))};
    return {blend_coordinate(a.x, b.x, fraction(boundary, a.y, b.y)), boundary};
}

// Cohen-Sutherland in normalized screen coordinates, before integer conversion.
template <typename Real>
bool clip_line(Vector<Real> *a, Vector<Real> *b)
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

template <typename Real>
bool inside_edge(const Vector<Real> &p, unsigned edge)
{
    if (edge == 0) return p.x >= 0;
    if (edge == 1) return p.x <= 1;
    if (edge == 2) return p.y >= 0;
    return p.y <= 1;
}

template <typename Real>
bool same_point(const Vector<Real> &a, const Vector<Real> &b)
{
    return a.x == b.x && a.y == b.y;
}

template <typename Real>
bool append_vertex(Vector<Real> *points, unsigned *count, const Vector<Real> &p)
{
    if (!finite_point(p)) return false;
    if (*count && same_point(points[*count - 1], p)) return true;
    if (*count == 7) return same_point(points[0], p); // Closing duplicate only.
    points[(*count)++] = p;
    return true;
}

// Sutherland-Hodgman. A triangle intersected with a rectangle has at most
// seven vertices. The caller supplies seven slots; scratch uses seven more.
template <typename Real>
unsigned clip_triangle(Vector<Real> a, Vector<Real> b, Vector<Real> c, Vector<Real> *points)
{
    if (!finite_point(a) || !finite_point(b) || !finite_point(c)) return 0;
    points[0] = a; points[1] = b; points[2] = c;
    Vector<Real> scratch[7];
    Vector<Real> *input = points, *output = scratch;
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

} // namespace grafici_detail
#endif
