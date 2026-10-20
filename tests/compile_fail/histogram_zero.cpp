#include "data/DataArray.h"
#include "data/DataHistogramXY.h"
DataArray<float> empty(nullptr, 0);
DataHistogramXY<0> invalid_histogram(empty);
