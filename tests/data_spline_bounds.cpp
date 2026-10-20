#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace {

const size_t guard_size = 16;
const unsigned char guard_value = 0xA5;

struct Allocation
{
    unsigned char *base;
    size_t bytes;
};

Allocation allocations[5] = {};
size_t attempts = 0;
size_t failure_at = 5;

void reset_allocator(size_t fail_at = 5)
{
    for (const auto &allocation : allocations)
        assert(allocation.base == nullptr);
    attempts = 0;
    failure_at = fail_at;
}

void *guarded_malloc(size_t bytes)
{
    assert(attempts < 5);
    Allocation &allocation = allocations[attempts++];
    allocation.bytes = bytes;
    if (attempts - 1 == failure_at)
        return nullptr;

    allocation.base = static_cast<unsigned char *>(std::malloc(bytes + 2 * guard_size));
    assert(allocation.base != nullptr);
    std::memset(allocation.base, guard_value, bytes + 2 * guard_size);
    return allocation.base + guard_size;
}

void guarded_free(void *pointer)
{
    if (pointer == nullptr)
        return;
    for (auto &allocation : allocations)
    {
        if (allocation.base == nullptr || allocation.base + guard_size != pointer)
            continue;
        for (size_t i = 0; i < guard_size; ++i)
        {
            assert(allocation.base[i] == guard_value);
            assert(allocation.base[guard_size + allocation.bytes + i] == guard_value);
        }
        std::free(allocation.base);
        allocation.base = nullptr;
        return;
    }
    assert(false && "Unknown or already freed spline allocation");
}

void check_workspace(size_t points)
{
    assert(attempts == 5);
    for (size_t i = 0; i < 5; ++i)
    {
        assert(allocations[i].base == nullptr);
        assert(allocations[i].bytes == sizeof(float) * (i < 2 ? points - 1 : points));
    }
}

} // namespace

// Pad only the spline's requests so even a one-byte undersize is observable,
// without relying on the host allocator's alignment or minimum block size.
#define malloc guarded_malloc
#define free guarded_free
#include "data/DataSpline.h"
#undef malloc
#undef free

namespace {

class CheckedSource : public DataSourceNorm
{
public:
    CheckedSource(const float *values, size_t count, Range<float> range)
        : DataSourceNorm(count, range), values(values)
    {
    }

    const DataNorm operator[](unsigned long index) const override
    {
        assert(index < size());
        ++reads;
        return {values[index], range()};
    }

    mutable size_t reads = 0;

private:
    const float *values;
};

void check_invalid(const DataVector &value)
{
    assert(value.x.raw() == 0 && value.y.raw() == 0);
    assert(!value.x.valid() && !value.y.valid());
}

template <size_t N>
void check_linear(size_t points)
{
    reset_allocator();
    const float xs[] = {0, 0.25f, 0.5f, 0.75f, 1};
    const float ys[] = {1, 1.5f, 2, 2.5f, 3};
    CheckedSource x(xs, points, {0, xs[points - 1]});
    CheckedSource y(ys, points, {1, ys[points - 1]});
    DataSpline<N> spline(x, y);
    check_workspace(points);
    assert(spline.size() == N);
    for (size_t i = 0; i < N; ++i)
    {
        const auto value = spline[i];
        const float expected_x = N == 1 ? 0 : xs[points - 1] * (float(i) / (N - 1));
        assert(std::fabs(value.x.raw() - expected_x) < 1e-5f);
        assert(std::fabs(value.y.raw() - (1 + 2 * expected_x)) < 1e-5f);
    }
    check_invalid(spline[N]);
}

void check_curved()
{
    reset_allocator();
    const float xs[] = {0, 0.5f, 1};
    const float ys[] = {0, 1, 0};
    const float expected[] = {0, 23.0f / 27, 23.0f / 27, 0};
    CheckedSource x(xs, 3, {0, 1});
    CheckedSource y(ys, 3, {0, 1});
    DataSpline<4, false> spline(x, y);
    check_workspace(3);
    for (size_t i = 0; i < 4; ++i)
        assert(std::fabs(spline[i].y.raw() - expected[i]) < 1e-5f);
}

template <size_t N>
void check_rejected(size_t x_points, size_t y_points)
{
    reset_allocator();
    const float values[] = {0, 0.25f, 0.5f, 0.75f, 1};
    CheckedSource x(values, x_points, {0, 1});
    CheckedSource y(values, y_points, {0, 1});
    DataSpline<N> spline(x, y);
    assert(spline.size() == 0);
    check_invalid(spline[0]);
    assert(spline.x().size() == 0 && spline.y().size() == 0);
    assert(attempts == 0 && x.reads == 0 && y.reads == 0);
}

void check_allocation_failures()
{
    const float xs[] = {0, 0.5f, 1};
    const float ys[] = {0, 1, 0};
    for (size_t failed = 0; failed < 5; ++failed)
    {
        reset_allocator(failed);
        CheckedSource x(xs, 3, {0, 1});
        CheckedSource y(ys, 3, {0, 1});
        DataSpline<4> spline(x, y);
        assert(spline.size() == 0);
        check_invalid(spline[0]);
        check_workspace(3);
        // Knot validation reads inputs before solver allocation; checked sources
        // still reject every out-of-bounds read.
    }
}

void check_uncovered_x_range()
{
    reset_allocator();
    const float values[] = {0, 0.25f};
    CheckedSource x(values, 2, {0, 1});
    CheckedSource y(values, 2, {0, 1});
    DataSpline<4, false> spline(x, y);
    check_workspace(2);
    // The declared range extends beyond the available knots. No bin exists
    // for normalized x = 2/3; do not read an extra knot or coefficient.
    check_invalid(spline[2]);
}

} // namespace

int main()
{
    check_linear<1>(2);
    check_linear<2>(3);
    check_linear<4>(5);
    check_linear<8>(5);
    check_linear<16>(3);
    check_curved();
    check_rejected<4>(0, 0);
    check_rejected<4>(0, 3);
    check_rejected<4>(3, 0);
    check_rejected<4>(1, 3);
    check_rejected<4>(3, 1);
    check_rejected<0>(2, 2);
    check_rejected<2>(4, 4);
    check_rejected<1>(5, 3);
    check_allocation_failures();
    check_uncovered_x_range();
    std::puts("Spline bounds, allocation-failure cleanup and interpolation checks passed.");
}
