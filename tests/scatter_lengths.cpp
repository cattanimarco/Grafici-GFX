#include "Adafruit_GFX.h"
#include "Grafici.h"
#include <cassert>
#include <cstdio>

template <typename Real>
class CheckedSource : public DataSourceNormT<Real>
{
public:
    CheckedSource(size_t count, float value) : DataSourceNormT<Real>(count, {0, 1}), value(value) {}
    const DataNormT<Real> operator[](unsigned long index) const override
    {
        assert(index < this->size());
        ++reads;
        return {value, {0, 1}};
    }
    mutable size_t reads = 0;
private:
    float value;
};

template <typename Real>
void check_lengths()
{
    CheckedSource<Real> xy(3, 0.5f), colors(3, 1), radius(1, 0.05f), empty(0, 0);
    Adafruit_GFX target;
    GraficiT<Real> plot(target);
    auto options = PlotOptionsT<Real>{}.scatter_style("o");
    plot.scatter(xy, xy, colors, radius, full_screen_for<Real>(), options);
    assert(target.lines.size() == 45);
    target.lines.clear();
    plot.scatter(xy, xy, colors, empty, full_screen_for<Real>(), options);
    assert(target.lines.empty() && empty.reads == 0);

    target.lines.clear();
    plot.scatter(xy, xy, colors, empty, full_screen_for<Real>(), options.scatter_style("."));
    assert(target.lines.size() == 3 * 45 && empty.reads == 0);
    target.lines.clear();
    plot.scatter(xy, xy, colors, radius, full_screen_for<Real>(), options.scatter_style(".o"));
    assert(target.lines.size() == 4 * 45);

    CheckedSource<Real> short_colors(1, 1);
    target.lines.clear();
    plot.scatter(xy, xy, short_colors, radius, full_screen_for<Real>(), options.scatter_style("."));
    assert(target.lines.size() == 45);
}

int main()
{
    check_lengths<float>();
    check_lengths<grafici::Float16>();
    std::puts("Scatter bounds radius-dependent markers and preserves independent dots.");
}
